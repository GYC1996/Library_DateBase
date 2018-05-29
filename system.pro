#-------------------------------------------------
#
# Project created by QtCreator 2018-05-25T18:48:26
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = system
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    global.cpp \
    login.cpp \
    admin_main.cpp \
    add_book.cpp \
    delete_book.cpp \
    insert_stu.cpp \
    delete_stu.cpp \
    search_book.cpp \
    stu_main.cpp \
    stu_alter_passwd.cpp \
    borrow_book.cpp \
    return_book.cpp

HEADERS  += mainwindow.h \
    global.h \
    login.h \
    admin_main.h \
    add_book.h \
    delete_book.h \
    insert_stu.h \
    delete_stu.h \
    search_book.h \
    stu_main.h \
    stu_alter_passwd.h \
    borrow_book.h \
    return_book.h

FORMS    += mainwindow.ui \
    login.ui \
    admin_main.ui \
    add_book.ui \
    delete_book.ui \
    insert_stu.ui \
    delete_stu.ui \
    search_book.ui \
    stu_main.ui \
    stu_alter_passwd.ui \
    borrow_book.ui \
    return_book.ui
