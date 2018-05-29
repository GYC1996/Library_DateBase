#include "delete_stu.h"
#include "ui_delete_stu.h"

Delete_Stu::Delete_Stu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Delete_Stu)
{
    ui->setupUi(this);
}

Delete_Stu::~Delete_Stu()
{
    delete ui;
}

void Delete_Stu::receive_from_admin()
{
    this->show();
}

void Delete_Stu::on_search_clicked()
{
    QString Sno=ui->Sno->text();
    QSqlQuery sql_query(db);
    QString select_sql="select * from Student where Sno=?";
    sql_query.prepare(select_sql);
    sql_query.addBindValue(Sno);
    if(!sql_query.exec())
    {
        sql_query.lastError();
    }
    else
    {
        if(sql_query.first())
        {
            //qDebug()<<sql_query.value(0).toString();
            ui->Search_In->setRowCount(5);
            ui->Search_In->setColumnCount(2);
            ui->Search_In->verticalHeader()->setDefaultSectionSize(30);
            ui->Search_In->horizontalHeader()->setDefaultSectionSize(120);
            ui->Search_In->verticalHeader()->setVisible(false);
            ui->Search_In->horizontalHeader()->setVisible(false);
            ui->Search_In->setItem(0,0,new QTableWidgetItem("学号"));
            ui->Search_In->setItem(1,0,new QTableWidgetItem("姓名"));
            ui->Search_In->setItem(2,0,new QTableWidgetItem("入学年份"));
            ui->Search_In->setItem(3,0,new QTableWidgetItem("性别"));
            ui->Search_In->setItem(4,0,new QTableWidgetItem("借书量"));
            ui->Search_In->setItem(0,1,new QTableWidgetItem(sql_query.value(0).toString()));
            ui->Search_In->setItem(1,1,new QTableWidgetItem(sql_query.value(3).toString()));
            ui->Search_In->setItem(2,1,new QTableWidgetItem(sql_query.value(2).toString()));
            ui->Search_In->setItem(3,1,new QTableWidgetItem(sql_query.value(4).toString()));
            ui->Search_In->setItem(4,1,new QTableWidgetItem(sql_query.value(5).toString()));
            if(sql_query.value(5).toString().toInt())
            {
                ui->Search_In->item(4,1)->setBackgroundColor(Qt::red);
            }
        }
        qDebug()<<"find success";


    }
}

void Delete_Stu::on_buttonBox_accepted()
{
    QString delete_sql="delete from Student where Sno=?";
    QSqlQuery sql_query(db);
    sql_query.prepare(delete_sql);
    sql_query.addBindValue(ui->Sno->text());
    if(!sql_query.exec())
    {
        sql_query.lastError();
    }
    else
    {
        qDebug()<<"delete success";
        this->hide();
        ui->Sno->clear();
        ui->Search_In->clear();
    }
}

void Delete_Stu::on_buttonBox_rejected()
{
    this->hide();
    ui->Search_In->clear();
    ui->Sno->clear();
}
