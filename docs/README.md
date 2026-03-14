# Qt Address Book Application

## Overview

This project is a simple Address Book management application developed using Qt and C++. It allows users to store and manage contact information efficiently.

## Features

- View stored contacts
- Add new contacts
- Edit existing contacts
- Delete contacts
- SQLite database storage
- Email and mobile validation

## Contact Fields

- Name
- Mobile
- Email
- Birthday

## Build Instructions (Debian/Ubuntu)

Install dependencies:

sudo apt install qtbase5-dev qt5-qmake build-essential

Build project:

qmake addressbook.pro
make

Run application:

./addressbook

## Project Structure

src/
main.cpp
mainwindow.cpp
database.cpp
contact.cpp

tests/
Unit tests for contact model

docs/
Project documentation

## Author

Varshini Balaga
