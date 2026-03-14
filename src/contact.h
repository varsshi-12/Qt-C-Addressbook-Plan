#ifndef CONTACT_H
#define CONTACT_H

#include <QString>
#include <QDate>

class Contact
{
public:
    int id;
    QString name;
    QString mobile;
    QString email;
    QDate birthday;

    Contact();
    Contact(int id, QString name, QString mobile, QString email, QDate birthday);
};

#endif