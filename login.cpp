#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
}

Login::~Login()
{
    delete ui;
}

void Login::on_login_clicked()
{
    QSqlQuery sql_query(db);
    QString usename=ui->use_name->text();
    QString password=ui->password->text();
    if(usename.mid(0,5)=="admin")
    {//管理员
        QString select_sql="select * from admin where Ano=?";
        sql_query.prepare(select_sql);
        sql_query.addBindValue(usename);
        if(!sql_query.exec())
        {
            qDebug()<<sql_query.lastError();
        }
        else
        {
            if(sql_query.first())
            {
                if(sql_query.value(1)==password)
                {
                    qDebug()<<"登录成功";
                    usename_global=usename;
                    send_to_admin_main();
                    this->hide();
                }
            }
        }

    }
    else
    {//学生
        QString select_sql="select * from Student where Sno=?";
        sql_query.prepare(select_sql);
        sql_query.addBindValue(usename);
        if(!sql_query.exec())
        {
            qDebug()<<sql_query.lastError();
        }
        else
        {
            if(sql_query.next())
            {
                if(sql_query.value(1)==password)
                {
                    qDebug()<<"登录成功";
                    usename_global=usename;
                    send_to_Stu_main();
                    this->hide();
                }
            }
        }
    }
    //qDebug()<<usename;
}
