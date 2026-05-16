#include "Database.h"

// ── Constructor: open the connection ─────────────────────────────────────────
Database::Database() : conn(nullptr) {
    conn = mysql_init(nullptr);
    if (!conn) {
        cerr << "[DB] mysql_init failed\n";
        return;
    }

    if (!mysql_real_connect(conn, HOST, USER, PASS, DBNAME, PORT, nullptr, 0)) {
        cerr << "[DB] Connection failed: " << mysql_error(conn) << "\n";
        mysql_close(conn);
        conn = nullptr;
        return;
    }

    // UTF-8 everywhere
    mysql_set_character_set(conn, "utf8mb4");
    cout << "[DB] Connected to MySQL database \"" << DBNAME << "\"\n";
}

// ── Destructor: close the connection ─────────────────────────────────────────
Database::~Database() {
    if (conn) {
        mysql_close(conn);
        conn = nullptr;
    }
}

// ── Escape helper ─────────────────────────────────────────────────────────────
string Database::escape(const string& raw) {
    if (!conn) return raw;
    // mysql_real_escape_string needs a buffer of at most 2*len+1
    vector<char> buf(raw.size() * 2 + 1);
    mysql_real_escape_string(conn, buf.data(), raw.c_str(), (unsigned long)raw.size());
    return string(buf.data());
}

// ── INSERT ────────────────────────────────────────────────────────────────────
bool Database::insertContact(const Contact& c) {
    if (!conn) return false;

    string sql =
        "INSERT INTO contacts (name, phone, email, address) VALUES ('"
        + escape(c.name)    + "','"
        + escape(c.phone)   + "','"
        + escape(c.email)   + "','"
        + escape(c.address) + "')";

    if (mysql_query(conn, sql.c_str())) {
        cerr << "[DB] INSERT failed: " << mysql_error(conn) << "\n";
        return false;
    }
    return true;
}

// ── DELETE ────────────────────────────────────────────────────────────────────
bool Database::deleteContact(const string& name) {
    if (!conn) return false;

    string sql = "DELETE FROM contacts WHERE name='" + escape(name) + "'";

    if (mysql_query(conn, sql.c_str())) {
        cerr << "[DB] DELETE failed: " << mysql_error(conn) << "\n";
        return false;
    }
    return true;
}

// ── UPDATE ────────────────────────────────────────────────────────────────────
// We match on the OLD name, then overwrite every field.
bool Database::updateContact(const string& oldName, const Contact& updated) {
    if (!conn) return false;

    string sql =
        "UPDATE contacts SET "
        "name='"    + escape(updated.name)    + "',"
        "phone='"   + escape(updated.phone)   + "',"
        "email='"   + escape(updated.email)   + "',"
        "address='" + escape(updated.address) + "' "
        "WHERE name='" + escape(oldName) + "'";

    if (mysql_query(conn, sql.c_str())) {
        cerr << "[DB] UPDATE failed: " << mysql_error(conn) << "\n";
        return false;
    }
    return true;
}

// ── LOAD ALL ──────────────────────────────────────────────────────────────────
// Called once at startup to populate the AVL tree from the DB.
vector<Contact> Database::loadAll() {
    vector<Contact> contacts;
    if (!conn) return contacts;

    if (mysql_query(conn, "SELECT name, phone, email, address FROM contacts ORDER BY name ASC")) {
        cerr << "[DB] SELECT failed: " << mysql_error(conn) << "\n";
        return contacts;
    }

    MYSQL_RES* result = mysql_store_result(conn);
    if (!result) {
        cerr << "[DB] mysql_store_result failed: " << mysql_error(conn) << "\n";
        return contacts;
    }

    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result))) {
        Contact c;
        c.name    = row[0] ? row[0] : "";
        c.phone   = row[1] ? row[1] : "";
        c.email   = row[2] ? row[2] : "";
        c.address = row[3] ? row[3] : "";
        contacts.push_back(c);
    }

    mysql_free_result(result);
    cout << "[DB] Loaded " << contacts.size() << " contact(s) from database.\n";
    return contacts;
}