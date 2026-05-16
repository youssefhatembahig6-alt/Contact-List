#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QListWidgetItem>
#include "AvlTree.h"
#include "Database.h"   // ← NEW

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onSearchChanged(const QString& text);
    void onAddClicked();
    void onContactClicked(QListWidgetItem* item);

private:
    Ui::MainWindow* ui;
    AvlTree         tree;
    Database        db;     // ← NEW: persists for the lifetime of the window

    void refreshList(const QString& filter = "");
    void showAddDialog(const Contact* prefill = nullptr);
    void showContactDialog(const Contact& c);
    void applyStyle();
};

#endif // MAINWINDOW_H