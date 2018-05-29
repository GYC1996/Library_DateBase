#include "return_book.h"
#include "ui_return_book.h"

Return_Book::Return_Book(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Return_Book)
{
    ui->setupUi(this);
}

Return_Book::~Return_Book()
{
    delete ui;
}

void Return_Book::receive_from_stu()
{
    this->show();
}

void Return_Book::on_return_book_clicked()
{
    QSqlQuery sql_query(db);

    QString select_sql="select * from record where Book_id=? and Stu_no=?";
    sql_query.prepare(select_sql);
    sql_query.addBindValue(ui->book_id->text());
    sql_query.addBindValue(usename_global);
    if(!sql_query.exec())
    {
        qDebug()<<sql_query.lastError();
    }
    else
    {
        if(sql_query.first())
        {
            QString delete_sql="delete from record where Book_id=? and Stu_no=?";
            sql_query.prepare(delete_sql);
            sql_query.addBindValue(ui->book_id->text());
            sql_query.addBindValue(usename_global);
            if(!sql_query.exec())
            {
                qDebug()<<sql_query.lastError();
            }
            else
            {
                qDebug()<<"还书成功 update record";
            }

            QString update_sql="update Book set lend_able=lend_able+1 where Bid=?";
            sql_query.prepare(update_sql);
            sql_query.addBindValue(ui->book_id->text());
            if(!sql_query.exec())
            {
                qDebug()<<sql_query.lastError();
            }
            else
            {
                qDebug()<<"还书成功 update book";
            }

            update_sql="update Student set B_num=B_num-1 where Sno=?";
            sql_query.prepare(update_sql);
            sql_query.addBindValue(usename_global);
            if(!sql_query.exec())
            {
                qDebug()<<sql_query.lastError();
            }
            else
            {
                qDebug()<<"还书成功 update student";
            }
        }
        else
            qDebug()<<"记录不存在";
    }
}
