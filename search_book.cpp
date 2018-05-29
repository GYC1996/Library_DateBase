#include "search_book.h"
#include "ui_search_book.h"

Search_Book::Search_Book(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Search_Book)
{
    ui->setupUi(this);
}

Search_Book::~Search_Book()
{
    delete ui;
}

void Search_Book::receive_from_admin()
{
    this->show();
}

void Search_Book::on_push_clicked()
{
    QString book_id=ui->book_id->text();
    QSqlQuery sql_query(db);
    QString select_sql="select Bname,Stu_no,Sname,No,borrow_day,return_day,total,lend_able from Book,"
                       "record,Student where Book.bid=? and Book.Bid=record.Book_id and record.Stu_no=Student.Sno";
    sql_query.prepare(select_sql);
    sql_query.addBindValue(book_id);
    int count=ui->search_In->rowCount();
    //qDebug()<<count<<" count";
    for(int i=0;i<count;i++)
    {
        ui->search_In->removeRow(0);
    }
    if(!sql_query.exec())
    {
        sql_query.lastError();
    }
    else
    {
        ui->search_In->setColumnCount(5);
        QStringList header;
        header<<tr("学号")<<tr("姓名")<<tr("副本号")<<tr("借书日期")<<tr("应还日期");
        ui->search_In->setHorizontalHeaderLabels(header);
        while(sql_query.next())
        {

            int i=ui->search_In->rowCount();
            //qDebug()<<i<<" i";
            ui->search_In->insertRow(i);
            ui->search_In->setItem(i,0,new QTableWidgetItem(sql_query.value(1).toString()));
            ui->search_In->setItem(i,1,new QTableWidgetItem(sql_query.value(2).toString()));
            ui->search_In->setItem(i,2,new QTableWidgetItem(sql_query.value(3).toString()));
            ui->search_In->setItem(i,3,new QTableWidgetItem(sql_query.value(4).toString()));
            ui->search_In->setItem(i,4,new QTableWidgetItem(sql_query.value(5).toString()));
        }
        if(sql_query.first())
        {//有借书记录
            qDebug()<<"have";
            ui->Bname->setText(sql_query.value(0).toString());
            ui->Btotal->setText(sql_query.value(6).toString());
            ui->Bleft->setText(sql_query.value(7).toString());
        }
        else
        {//暂无借书记录
            qDebug()<<"haven't";
            select_sql="select Bname,total,lend_able from Book where Bid=?";
            sql_query.prepare(select_sql);
            sql_query.addBindValue(ui->book_id->text());
            if(!sql_query.exec())
            {
                sql_query.lastError();
            }
            else
            {
                if(sql_query.first())
                {
                    ui->Bname->setText(sql_query.value(0).toString());
                    ui->Btotal->setText(sql_query.value(1).toString());
                    ui->Bleft->setText(sql_query.value(2).toString());
                }
            }
        }
    }
}
