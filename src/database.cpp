#include "database.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

void Database::initialize()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("contacts.db");

    if (!db.open())
    {
        qDebug() << "Database error:" << db.lastError();
        return;
    }

    QSqlQuery query;

    query.exec(
        "CREATE TABLE IF NOT EXISTS contacts ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "name TEXT,"
        "mobile TEXT,"
        "email TEXT,"
        "birthday TEXT)");
}