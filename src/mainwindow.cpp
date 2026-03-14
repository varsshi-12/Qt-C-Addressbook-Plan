#include "mainwindow.h"

#include <QWidget>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QSqlQuery>
#include <QTableWidgetItem>
#include <QInputDialog>

#include <QRegularExpression>
#include <QMessageBox>
#include <QHeaderView>
#include <QAbstractItemView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Address Book Manager"); // add here
    resize(700, 450);

    QWidget *central = new QWidget(this);
    setCentralWidget(central);

    QVBoxLayout *layout = new QVBoxLayout;

    table = new QTableWidget;
    table->setColumnCount(4);
    table->setHorizontalHeaderLabels({"Name", "Mobile", "Email", "Birthday"});

    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->horizontalHeader()->setStretchLastSection(true);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setSelectionMode(QAbstractItemView::SingleSelection);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QPushButton *addBtn = new QPushButton("Add");
    QPushButton *editBtn = new QPushButton("Edit");
    QPushButton *deleteBtn = new QPushButton("Delete");

    layout->addWidget(table);
    layout->addWidget(addBtn);
    layout->addWidget(editBtn);
    layout->addWidget(deleteBtn);

    central->setLayout(layout);

    connect(addBtn, &QPushButton::clicked, this, &MainWindow::addContact);
    connect(editBtn, &QPushButton::clicked, this, &MainWindow::editContact);
    connect(deleteBtn, &QPushButton::clicked, this, &MainWindow::deleteContact);

    loadContacts();
}

void MainWindow::loadContacts()
{
    QSqlQuery query("SELECT name,mobile,email,birthday FROM contacts");

    table->setRowCount(0);

    while (query.next())
    {
        int row = table->rowCount();
        table->insertRow(row);

        table->setItem(row, 0, new QTableWidgetItem(query.value(0).toString()));
        table->setItem(row, 1, new QTableWidgetItem(query.value(1).toString()));
        table->setItem(row, 2, new QTableWidgetItem(query.value(2).toString()));
        table->setItem(row, 3, new QTableWidgetItem(query.value(3).toString()));
    }
}

void MainWindow::addContact()
{
    bool ok;

    QString name = QInputDialog::getText(this, "Add Contact", "Name:", QLineEdit::Normal, "", &ok);
    if (!ok || name.isEmpty())
        return;

    QString mobile = QInputDialog::getText(this, "Add Contact", "Mobile:", QLineEdit::Normal, "", &ok);
    if (!ok)
        return;

    // Mobile validation
    if (mobile.length() != 10)
    {
        QMessageBox::warning(this, "Error", "Mobile number must be 10 digits");
        return;
    }

    QString email = QInputDialog::getText(this, "Add Contact", "Email:", QLineEdit::Normal, "", &ok);
    if (!ok)
        return;

    // Email validation
    QRegularExpression emailRegex("^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,}$");

    if (!emailRegex.match(email).hasMatch())
    {
        QMessageBox::warning(this, "Error", "Invalid Email Address");
        return;
    }

    QString birthday = QInputDialog::getText(this, "Add Contact", "Birthday:", QLineEdit::Normal, "", &ok);
    if (!ok)
        return;

    QSqlQuery query;
    query.prepare("INSERT INTO contacts (name,mobile,email,birthday) VALUES (?,?,?,?)");

    query.addBindValue(name);
    query.addBindValue(mobile);
    query.addBindValue(email);
    query.addBindValue(birthday);

    query.exec();

    loadContacts();
}

void MainWindow::editContact()
{
    int row = table->currentRow();

    if (row < 0)
    {
        QMessageBox::warning(this, "Error", "Select a contact first");
        return;
    }

    QString name = table->item(row, 0)->text();
    QString mobile = table->item(row, 1)->text();
    QString email = table->item(row, 2)->text();
    QString birthday = table->item(row, 3)->text();

    bool ok;

    name = QInputDialog::getText(this, "Edit Contact", "Name:", QLineEdit::Normal, name, &ok);
    if (!ok)
        return;

    mobile = QInputDialog::getText(this, "Edit Contact", "Mobile:", QLineEdit::Normal, mobile, &ok);
    if (!ok)
        return;

    email = QInputDialog::getText(this, "Edit Contact", "Email:", QLineEdit::Normal, email, &ok);
    if (!ok)
        return;

    birthday = QInputDialog::getText(this, "Edit Contact", "Birthday:", QLineEdit::Normal, birthday, &ok);
    if (!ok)
        return;

    QSqlQuery query;
    query.prepare("UPDATE contacts SET mobile=?,email=?,birthday=? WHERE name=?");

    query.addBindValue(mobile);
    query.addBindValue(email);
    query.addBindValue(birthday);
    query.addBindValue(name);

    query.exec();

    loadContacts();
}

void MainWindow::deleteContact()
{
    int row = table->currentRow();

    if (row < 0)
    {
        QMessageBox::warning(this, "Error", "Select a contact first");
        return;
    }

    QString name = table->item(row, 0)->text();

    QSqlQuery query;
    query.prepare("DELETE FROM contacts WHERE name=?");
    query.addBindValue(name);
    query.exec();

    loadContacts();
}