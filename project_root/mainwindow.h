#pragma once
#include <QMainWindow>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include "src/AvlTree.h"

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
    void onContactClicked(QListWidgetItem* item);
    void onAddClicked();

private:
    Ui::MainWindow *ui;
    AvlTree tree;

    void refreshList(const QString& filter = "");
    void showAddDialog(const Contact* prefill = nullptr);
    void showContactDialog(const Contact& c);
    void applyStyle();
};