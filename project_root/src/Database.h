#ifndef DATABASE_H
#define DATABASE_H



#include "Contact.h"
#include <mysql/mysql.h>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

// ─────────────────────────────────────────────────────────────────────────────
//  Database
//  Wraps every MySQL operation the app needs.
//  One instance lives inside MainWindow and is used by all slots.
// ─────────────────────────────────────────────────────────────────────────────
class Database {
public:
    // ── Change these to match your MySQL setup ────────────────────────────
#include "db_config.h"

    static constexpr const char* HOST   = DB_HOST;
    static constexpr const char* USER   = DB_USER;
    static constexpr const char* PASS   = DB_PASS;
    static constexpr const char* DBNAME = DB_NAME;
    static constexpr unsigned    PORT   = DB_PORT;
    // ─────────────────────────────────────────────────────────────────────

    Database();
    ~Database();

    bool isConnected() const { return conn != nullptr; }

    // CRUD ─────────────────────────────────────────────────────────────────
    bool              insertContact(const Contact& c);
    bool              deleteContact(const string& name);
    bool              updateContact(const string& oldName, const Contact& updated);
    vector<Contact>   loadAll();

private:
    MYSQL* conn;

    // Escape a string so it is safe to embed in SQL
    string escape(const string& raw);
};

#endif // DATABASE_H