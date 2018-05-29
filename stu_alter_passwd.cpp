#include "stu_alter_passwd.h"
#include "ui_stu_alter_passwd.h"

Stu_Alter_Passwd::Stu_Alter_Passwd(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Stu_Alter_Passwd)
{
    ui->setupUi(this);
}

Stu_Alter_Passwd::~Stu_Alter_Passwd()
{
    delete ui;
}

void Stu_Alter_Passwd::receive_from_stu()
{
    this->show();
}

void Stu_Alter_Passwd::on_alter_passwd_accepted()
{
    QString origin=ui->origin->text();
    QString select_sql="select passwd from Student where Sno=?";
    QSqlQuery sql_query(db);
    sql_query.prepare(select_sql);
    sql_query.addBindValue(usename_global);
    if(!sql_query.exec())
    {
        sql_query.lastError();
    }
    else
    {
        if(sql_query.first())
        {
            if(origin==sql_query.value(0))
            {
                if(ui->new_2->text()==ui->renew->text())
                {
                    QString update_sql="update Student set passwd=? where Sno=?";
                    sql_query.prepare(update_sql);
                    sql_query.addBindValue(ui->new_2->text());
                    sql_query.addBindValue(usename_global);
                    if(!sql_query.exec())
                    {
                        qDebug()<<sql_query.lastError();
                    }
                    else
                    {
                        qDebug()<<"更改成功";
                        this->hide();
                        ui->origin->clear();
                        ui->new_2->clear();
                        ui->renew->clear();
                    }
                }
                else
                {
                    qDebug()<<"两个密码不一致";
                }
            }
            else
            {
                qDebug()<<"密码输入错误";
            }
        }
    }
}

void Stu_Alter_Passwd::on_alter_passwd_rejected()
{
    this->hide();
    ui->origin->clear();
    ui->new_2->clear();
    ui->renew->clear();
}
