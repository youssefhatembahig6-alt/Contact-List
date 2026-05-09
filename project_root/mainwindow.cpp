#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QFrame>
#include <QMessageBox>
#include <algorithm>
#include <cctype>

// ── Validation ────────────────────────────────────────────────────────────────

static bool isValidPhone(const std::string& phone) {
    if (phone.empty()) return false;
    int start = (phone[0] == '+') ? 1 : 0;
    if (start == (int)phone.size()) return false;
    for (int i = start; i < (int)phone.size(); i++)
        if (!isdigit(phone[i])) return false;
    return true;
}

// ── Avatar color based on name hash ──────────────────────────────────────────

static QString avatarColor(const std::string& name) {
    static const char* colors[] = {
        "#E57373","#F06292","#BA68C8","#7986CB",
        "#64B5F6","#4DB6AC","#81C784","#FFD54F","#FF8A65"
    };
    int idx = 0;
    for (char ch : name) idx = (idx * 31 + (unsigned char)ch) % 9;
    return colors[idx];
}

// ── Callback context passed to tree.getAll() ─────────────────────────────────

struct ListCtx {
    QListWidget* list;
    QString      filter;
    char         lastLetter;
};

// called once per contact during inorder traversal
static void addContactItem(const Contact& c, void* raw) {
    ListCtx* ctx = static_cast<ListCtx*>(raw);
    QString name = QString::fromStdString(c.name);

    // skip if doesn't match search filter
    if (!ctx->filter.isEmpty() && !name.contains(ctx->filter, Qt::CaseInsensitive))
        return;

    // alphabet section header (only when not searching)
    if (ctx->filter.isEmpty() && !c.name.empty()) {
        char letter = toupper(c.name[0]);
        if (letter != ctx->lastLetter) {
            ctx->lastLetter = letter;

            QListWidgetItem* hdr = new QListWidgetItem(ctx->list);
            hdr->setFlags(Qt::NoItemFlags);
            hdr->setSizeHint(QSize(0, 30));
            hdr->setData(Qt::UserRole, QString()); // empty = not a real contact

            QLabel* lbl = new QLabel(QString(QChar(letter)));
            lbl->setStyleSheet(
                "color:#888; font-size:12px; font-weight:bold;"
                "padding-left:18px; background:transparent;"
            );
            ctx->list->setItemWidget(hdr, lbl);
        }
    }

    // contact row
    QListWidgetItem* item = new QListWidgetItem(ctx->list);
    item->setSizeHint(QSize(0, 64));
    item->setData(Qt::UserRole, name); // stored so we can look it up on click

    QWidget* row = new QWidget();
    row->setAttribute(Qt::WA_TranslucentBackground);
    QHBoxLayout* lay = new QHBoxLayout(row);
    lay->setContentsMargins(14, 0, 14, 0);
    lay->setSpacing(14);

    // colored circle avatar
    QLabel* av = new QLabel(QString(QChar(toupper(c.name[0]))));
    av->setFixedSize(46, 46);
    av->setAlignment(Qt::AlignCenter);
    av->setStyleSheet(QString(
        "background:%1; border-radius:23px;"
        "color:white; font-size:18px; font-weight:bold;"
    ).arg(avatarColor(c.name)));

    QLabel* nameLbl = new QLabel(name);
    nameLbl->setStyleSheet("color:#f0f0f0; font-size:15px;");

    lay->addWidget(av);
    lay->addWidget(nameLbl);
    lay->addStretch();
    row->setStyleSheet("background:transparent;");

    ctx->list->setItemWidget(item, row);
}

// ── MainWindow ────────────────────────────────────────────────────────────────

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    setWindowTitle("Contacts");
    setMinimumSize(400, 580);
    resize(430, 680);
    applyStyle();

    connect(ui->searchBar,    &QLineEdit::textChanged,
            this, &MainWindow::onSearchChanged);
    connect(ui->btnAdd,       &QPushButton::clicked,
            this, &MainWindow::onAddClicked);
    connect(ui->contactList,  &QListWidget::itemClicked,
            this, &MainWindow::onContactClicked);

    refreshList();
}

MainWindow::~MainWindow() { delete ui; }

// ── Slots ─────────────────────────────────────────────────────────────────────

void MainWindow::onSearchChanged(const QString& text) {
    refreshList(text.trimmed());
}

void MainWindow::onAddClicked() {
    showAddDialog();
}

void MainWindow::onContactClicked(QListWidgetItem* item) {
    QString name = item->data(Qt::UserRole).toString();
    if (name.isEmpty()) return; // alphabet header — ignore
    Contact c = tree.SearchReq(name.toStdString());
    if (!c.name.empty()) showContactDialog(c);
}

// ── Refresh list ──────────────────────────────────────────────────────────────

void MainWindow::refreshList(const QString& filter) {
    ui->contactList->clear();

    ListCtx ctx;
    ctx.list        = ui->contactList;
    ctx.filter      = filter;
    ctx.lastLetter  = 0;
    tree.getAll(addContactItem, &ctx);

    // empty state
    if (ui->contactList->count() == 0) {
        QListWidgetItem* emp = new QListWidgetItem(ui->contactList);
        emp->setFlags(Qt::NoItemFlags);
        emp->setSizeHint(QSize(0, 100));
        QLabel* lbl = new QLabel(filter.isEmpty()
            ? "No contacts yet.\nTap + to add one."
            : "No results found.");
        lbl->setAlignment(Qt::AlignCenter);
        lbl->setStyleSheet("color:#555; font-size:14px;");
        ui->contactList->setItemWidget(emp, lbl);
    }
}

// ── Add / Edit dialog ─────────────────────────────────────────────────────────

void MainWindow::showAddDialog(const Contact* prefill) {
    QDialog dlg(this);
    dlg.setWindowTitle(prefill ? "Edit Contact" : "New Contact");
    dlg.setMinimumWidth(340);
    dlg.setStyleSheet(
        "QDialog{background:#1e1e1e;}"
        "QLabel{color:#aaa;font-size:12px;}"
        "QLineEdit{background:#2a2a2a;border:none;border-bottom:1px solid #444;"
                  "color:white;font-size:15px;padding:6px 2px;}"
        "QLineEdit:focus{border-bottom:1px solid #64B5F6;}"
        "QPushButton{border-radius:6px;padding:10px;font-size:14px;font-weight:bold;}"
    );

    QVBoxLayout* vl = new QVBoxLayout(&dlg);
    vl->setSpacing(14);
    vl->setContentsMargins(24, 24, 24, 24);

    // helper to add a labelled field
    auto field = [&](const QString& label, const QString& val) -> QLineEdit* {
        vl->addWidget(new QLabel(label));
        QLineEdit* e = new QLineEdit(val);
        vl->addWidget(e);
        return e;
    };

    QLineEdit* eName    = field("NAME",    prefill ? QString::fromStdString(prefill->name)    : "");
    QLineEdit* ePhone   = field("PHONE",   prefill ? QString::fromStdString(prefill->phone)   : "");
    QLineEdit* eEmail   = field("EMAIL",   prefill ? QString::fromStdString(prefill->email)   : "");
    QLineEdit* eAddress = field("ADDRESS", prefill ? QString::fromStdString(prefill->address) : "");

    QLabel* errLbl = new QLabel("");
    errLbl->setStyleSheet("color:#E57373;font-size:12px;");
    vl->addWidget(errLbl);

    QPushButton* btnSave = new QPushButton(prefill ? "Save Changes" : "Add Contact");
    btnSave->setStyleSheet("background:#64B5F6;color:#111;");
    vl->addWidget(btnSave);

    // keep a copy of the original name for update (remove + re-insert)
    std::string oldName = prefill ? prefill->name : "";

    connect(btnSave, &QPushButton::clicked, [&]() {
        Contact c;
        std::string n = eName->text().trimmed().toStdString();
        std::transform(n.begin(), n.end(), n.begin(), ::tolower);
        c.name    = n;
        c.phone   = ePhone->text().trimmed().toStdString();
        c.email   = eEmail->text().trimmed().toStdString();
        c.address = eAddress->text().trimmed().toStdString();

        if (c.name.empty())         { errLbl->setText("Name cannot be empty.");   return; }
        if (!isValidPhone(c.phone)) { errLbl->setText("Invalid phone number.");   return; }

        if (prefill) tree.RemoveContact(oldName); // remove old before re-inserting

        if (!tree.AddContact(c)) {
            if (prefill) tree.AddContact(*prefill); // restore if duplicate phone
            errLbl->setText("Phone number already exists.");
            return;
        }
        dlg.accept();
    });

    if (dlg.exec() == QDialog::Accepted)
        refreshList(ui->searchBar->text().trimmed());
}

// ── Contact detail dialog ─────────────────────────────────────────────────────

void MainWindow::showContactDialog(const Contact& c) {
    QDialog dlg(this);
    dlg.setWindowTitle("Contact");
    dlg.setMinimumWidth(320);
    dlg.setStyleSheet(
        "QDialog{background:#1e1e1e;}"
        "QLabel{color:#f0f0f0;}"
        "QPushButton{border-radius:6px;padding:10px;font-size:14px;font-weight:bold;}"
    );

    QVBoxLayout* vl = new QVBoxLayout(&dlg);
    vl->setSpacing(10);
    vl->setContentsMargins(24, 28, 24, 24);

    // large avatar
    QLabel* av = new QLabel(QString(QChar(toupper(c.name[0]))));
    av->setFixedSize(80, 80);
    av->setAlignment(Qt::AlignCenter);
    av->setStyleSheet(QString(
        "background:%1;border-radius:40px;color:white;font-size:32px;font-weight:bold;"
    ).arg(avatarColor(c.name)));
    QHBoxLayout* avRow = new QHBoxLayout();
    avRow->addStretch(); avRow->addWidget(av); avRow->addStretch();
    vl->addLayout(avRow);

    // name
    QLabel* nameLbl = new QLabel(QString::fromStdString(c.name));
    nameLbl->setAlignment(Qt::AlignCenter);
    nameLbl->setStyleSheet("font-size:20px;font-weight:bold;color:white;");
    vl->addWidget(nameLbl);

    // divider
    QFrame* line = new QFrame();
    line->setFrameShape(QFrame::HLine);
    line->setStyleSheet("color:#333;");
    vl->addWidget(line);

    // info rows
    auto addInfo = [&](const QString& icon, const QString& label, const QString& val) {
        if (val.isEmpty()) return;
        QLabel* lbl = new QLabel(icon + "  " + label);
        lbl->setStyleSheet("color:#888;font-size:11px;margin-top:8px;");
        QLabel* val_lbl = new QLabel(val);
        val_lbl->setStyleSheet("color:#f0f0f0;font-size:14px;padding-left:22px;");
        vl->addWidget(lbl);
        vl->addWidget(val_lbl);
    };
    addInfo("📞", "Phone",   QString::fromStdString(c.phone));
    addInfo("✉",  "Email",   QString::fromStdString(c.email));
    addInfo("📍", "Address", QString::fromStdString(c.address));

    vl->addSpacing(8);

    // edit / delete buttons
    QHBoxLayout* btnRow = new QHBoxLayout();
    QPushButton* btnEdit = new QPushButton("Edit");
    QPushButton* btnDel  = new QPushButton("Delete");
    btnEdit->setStyleSheet("background:#2a2a2a;color:#64B5F6;");
    btnDel->setStyleSheet ("background:#2a2a2a;color:#E57373;");
    btnRow->addWidget(btnEdit);
    btnRow->addWidget(btnDel);
    vl->addLayout(btnRow);

    // capture c by value so it stays valid after dlg closes
    Contact copy = c;

    connect(btnEdit, &QPushButton::clicked, [&]() {
        dlg.accept();
        showAddDialog(&copy);
    });

    connect(btnDel, &QPushButton::clicked, [&]() {
        auto ans = QMessageBox::question(&dlg, "Delete",
            "Delete " + QString::fromStdString(copy.name) + "?");
        if (ans == QMessageBox::Yes) {
            tree.RemoveContact(copy.name);
            dlg.accept();
            refreshList(ui->searchBar->text().trimmed());
        }
    });

    dlg.exec();
}

// ── Dark stylesheet ───────────────────────────────────────────────────────────

void MainWindow::applyStyle() {
    setStyleSheet(
        "QMainWindow,QWidget#centralwidget{background:#121212;}"

        "QWidget#header{background:#121212;}"

        "QLabel#titleLabel{color:white;font-size:26px;font-weight:bold;}"

        "QPushButton#btnAdd{"
        "  background:transparent;color:white;font-size:30px;"
        "  border:none;padding:0 6px;}"
        "QPushButton#btnAdd:hover{color:#64B5F6;}"

        "QLineEdit#searchBar{"
        "  background:#2a2a2a;border-radius:20px;"
        "  color:white;font-size:14px;"
        "  padding:8px 16px;border:none;"
        "  margin:4px 12px 8px 12px;}"

        "QListWidget#contactList{"
        "  background:#121212;border:none;outline:none;}"
        "QListWidget#contactList::item:selected{background:#2a2a2a;}"
        "QListWidget#contactList::item:hover{background:#1a1a1a;}"

        "QScrollBar:vertical{background:#121212;width:4px;}"
        "QScrollBar::handle:vertical{background:#333;border-radius:2px;}"
        "QScrollBar::add-line:vertical,QScrollBar::sub-line:vertical{height:0;}"
    );
}