#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private:
    QTableWidget *table;

    void loadContacts();

private slots:
    void addContact();
    void editContact();
    void deleteContact();
};

#endif