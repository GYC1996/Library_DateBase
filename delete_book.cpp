#include "delete_book.h"
#include "ui_delete_book.h"

Delete_Book::Delete_Book(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Delete_Book)
{
    ui->setupUi(this);
}

Delete_Book::~Delete_Book()
{
    delete ui;
}

void Delete_Book::receive_from_admin()
{
    this->show();
}

void Delete_Book::update_view()
{
    QString Stotal=ui->total->text();
    int total=Stotal.toInt();
    total=total-1;
    QString Sable=ui->delete_avai->text();
    int able=Sable.toInt();
    able=able-1;
    ui->total->setText(QString::number(total));
    ui->delete_avai->setText(QString::number(able));
    if(able==0)
    {
        ui->delete_book->setEnabled(false);
    }
}

void Delete_Book::on_search_clicked()
{
    QSqlQuery sql_query(db);
    QString select_sql="select Bname,total,lend_able from Book where Bid=?";
    sql_query.prepare(select_sql);
    sql_query.addBindValue(ui->bookid->text());
    if(!sql_query.exec())
    {
        qDebug()<<sql_query.lastError();
    }
    else
    {
        if(sql_query.first())
        {
            ui->Bname->setText(sql_query.value(0).toString());
            ui->total->setText(sql_query.value(1).toString());
            ui->delete_avai->setText(sql_query.value(2).toString());
            if(sql_query.value(2)==0)
            {
                ui->delete_book->setEnabled(false);
            }
            else
            {
                ui->delete_book->setEnabled(true);
            }
        }
        else
        {
            qDebug()<<"没有这本书";
        }
    }
}


void Delete_Book::on_delete_book_clicked()
{
    QSqlQuery sql_query(db);
    QString update_sql="update Book set total=total-1,lend_able=lend_able-1 where Bid=?";
    sql_query.prepare(update_sql);
    sql_query.addBindValue(ui->bookid->text());
    if(!sql_query.exec())
    {
        sql_query.lastError();
    }
    else
    {
        update_view();
        qDebug()<<"删除成功";
    }
}
