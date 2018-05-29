#include "insert_stu.h"
#include "ui_insert_stu.h"

Insert_Stu::Insert_Stu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Insert_Stu)
{
    ui->setupUi(this);
}

Insert_Stu::~Insert_Stu()
{
    delete ui;
}

void Insert_Stu::on_insert_or_not_accepted()
{
    QString Sno=ui->Sno->text();
    QString Sname=ui->Sname->text();
    QString sex=ui->comboBox->currentText();
    QString year=Sno.mid(0,4);
    QString passwd=Sno;
    int num=0;
    QSqlQuery sql_query(db);
    QString insert_sql="insert into Student values(?,?,?,?,?,?)";
    sql_query.prepare(insert_sql);
    sql_query.addBindValue(Sno);
    sql_query.addBindValue(passwd);
    sql_query.addBindValue(year);
    sql_query.addBindValue(Sname);
    sql_query.addBindValue(sex);
    sql_query.addBindValue(num);
    if(!sql_query.exec())
    {
        qDebug()<<sql_query.lastError();
    }
    else
    {
        qDebug()<<"insert_success";
        this->hide();
    }
}

void Insert_Stu::on_insert_or_not_rejected()
{
    ui->Sname->clear();
    ui->Sno->clear();
    ui->comboBox->setCurrentIndex(0);
    this->hide();
}

void Insert_Stu::receive_from_admin()
{
    this->show();
}
