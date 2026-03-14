#include "contact.h"

Contact::Contact() {}

Contact::Contact(int id, QString name, QString mobile, QString email, QDate birthday)
{
    this->id = id;
    this->name = name;
    this->mobile = mobile;
    this->email = email;
    this->birthday = birthday;
}