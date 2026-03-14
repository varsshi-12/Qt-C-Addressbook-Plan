QT += core gui widgets sql

CONFIG += c++17

TEMPLATE = app
TARGET = addressbook

SOURCES += \
    src/main.cpp \
    src/mainwindow.cpp \
    src/contact.cpp \
    src/database.cpp \
    src/contactdialog.cpp

HEADERS += \
    src/mainwindow.h \
    src/contact.h \
    src/database.h \
    src/contactdialog.h