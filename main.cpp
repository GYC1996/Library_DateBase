#include "mainwindow.h"
#include "admin_main.h"
#include "add_book.h"
#include "delete_book.h"
#include "insert_stu.h"
#include "delete_stu.h"
#include "search_book.h"
#include "stu_main.h"
#include "stu_alter_passwd.h"
#include "borrow_book.h"
#include "return_book.h"
#include "login.h"
#include "global.h"
#include <QApplication>

bool connect_to_db()
{
    //qDebug()<<"hello\n";
    qDebug()<<QSqlDatabase::drivers()<<endl;
    db=QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setPort(3306);
    db.setDatabaseName("Library_system");
    db.setUserName("root");
    db.setPassword("guoyuechao");
    if (!db.open()) {
        qDebug()<<db.lastError();
        QMessageBox::critical(0, "Cannot open database1",
                              "Unable to establish a database connection.", QMessageBox::Cancel);
        return false;
    }
}

int main(int argc, char *argv[])
{ 

    connect_to_db();
    //qDebug()<<"hello2\n";
    QApplication a(argc, argv);
    MainWindow w;
    Admin_main A_m;
    Add_book A_b;
    Delete_Book D_b;
    Insert_Stu I_s;
    Delete_Stu D_s;
    Search_Book S_b;

    Stu_main S_m;
    Stu_Alter_Passwd S_A_p;
    Borrow_Book B_b;
    Return_Book R_b;
    Login L;
    L.show();
    QObject::connect(&L,SIGNAL(send_to_admin_main()),&A_m,SLOT(receive_from_login()));
    QObject::connect(&A_m,SIGNAL(send_to_addbook()),&A_b,SLOT(receive_from_admin()));
    QObject::connect(&A_m,SIGNAL(send_to_deletebook()),&D_b,SLOT(receive_from_admin()));
    QObject::connect(&A_m,SIGNAL(send_to_insertstu()),&I_s,SLOT(receive_from_admin()));
    QObject::connect(&A_m,SIGNAL(send_to_deletestu()),&D_s,SLOT(receive_from_admin()));
    QObject::connect(&A_m,SIGNAL(send_to_searchbook()),&S_b,SLOT(receive_from_admin()));

    QObject::connect(&L,SIGNAL(send_to_Stu_main()),&S_m,SLOT(receive_from_login()));
    QObject::connect(&S_m,SIGNAL(send_to_alter_passwd()),&S_A_p,SLOT(receive_from_stu()));
    QObject::connect(&S_m,SIGNAL(send_to_borrow()),&B_b,SLOT(receive_from_stu()));
    QObject::connect(&S_m,SIGNAL(send_to_return()),&R_b,SLOT(receive_from_stu()));
    //w.show();

    return a.exec();
}
