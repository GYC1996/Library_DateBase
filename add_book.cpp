#include "add_book.h"
#include "ui_add_book.h"

Add_book::Add_book(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Add_book)
{
    ui->setupUi(this);
}

Add_book::~Add_book()
{
    delete ui;
}
void Add_book::receive_from_admin()
{
    this->show();
}

QString selected(QString select_sql,QSqlQuery sql_query)
{
    sql_query.prepare(select_sql);
    if(!sql_query.exec())
    {
        qDebug()<<sql_query.lastError();
        return NULL;
    }
    else
    {
        if(sql_query.first())
        {
            bool ok;
            QString str_bid=sql_query.value(0).toString();
            int num=str_bid.mid(3,5).toInt(&ok,10);
            num=num+1;
            QString str_num=QString::number(num,10);
            str_bid.replace(8-str_num.length(),str_num.length(),str_num);
            qDebug()<<str_bid;
            return str_bid;
            //qDebug()<<sql_query.value(0).toString();
        }
        else
        {
            int position=select_sql.indexOf('%');
            QString str=select_sql.mid(position-3,3);
            str=str+"00000";
            return str;
        }
    }
}

void Add_book::on_add_or_not_accepted()
{//insert into Book values("MW_00006","四海为诗","文学名著",2014,"米家路",3,"北岳文艺出版社",3);
    QString B_name=ui->B_name->text();
    int catagory=ui->catagory->currentIndex();
    QString str_catagory=ui->catagory->currentText();
    QString date=ui->date->date().toString("yyyy-MM-dd").mid(0,4);
    QString author=ui->author->text();
    QString publish=ui->publisher->text();
    int total=ui->total->value();
    //QString date2=date.toString("yyyy-MM-dd");
    qDebug()<<B_name<<str_catagory<<date<<author<<publish<<total;
    QSqlQuery sql_query(db);
    //查询该书是否已在数据库中
    QString select_sql="select * from Book where Bname=? and author=? and Publish=?";
    sql_query.prepare(select_sql);
    sql_query.addBindValue(B_name);
    sql_query.addBindValue(author);
    sql_query.addBindValue(publish);
    if(!sql_query.exec())
    {
        qDebug()<<sql_query.lastError();
    }
    else
    {
        if(sql_query.first())
        {//该书已在数据库中，只需更改数量
            QString Bid_exist=sql_query.value(0).toString();
            QString update_sql="update Book set total=total+?,lend_able=lend_able+? where Bid=?";
            sql_query.prepare(update_sql);
            sql_query.addBindValue(total);
            sql_query.addBindValue(total);
            sql_query.addBindValue(Bid_exist);
            if(!sql_query.exec())
            {
                qDebug()<<"更新失败";
            }
            else
            {
                qDebug()<<"更新成功";
            }
        }
        else
        {//该书不在数据库中，需要新建Bid
            QString Bid;
            switch(catagory)
            {//生成Bid号
                case 0:Bid=selected("select Bid from Book where Bid like 'CS_%' order by Bid desc",sql_query);break;
                case 1:Bid=selected("select Bid from Book where Bid like 'WM_%' order by Bid desc",sql_query);break;
                case 2:Bid=selected("select Bid from Book where Bid like 'PS_%' order by Bid desc",sql_query);break;
                case 3:Bid=selected("select Bid from Book where Bid like 'MA_%' order by Bid desc",sql_query);break;
                case 4:Bid=selected("select Bid from Book where Bid like 'EM_%' order by Bid desc",sql_query);break;
                case 5:Bid=selected("select Bid from Book where Bid like 'HI_%' order by Bid desc",sql_query);break;
                default:break;
            }
            QString insert_sql="insert into Book values(?,?,?,?,?,?,?,?)";
            sql_query.prepare(insert_sql);
            sql_query.addBindValue(Bid);
            sql_query.addBindValue(B_name);
            sql_query.addBindValue(str_catagory);
            sql_query.addBindValue(date);
            sql_query.addBindValue(author);
            sql_query.addBindValue(total);
            sql_query.addBindValue(publish);
            sql_query.addBindValue(total);
            if(!sql_query.exec())
            {
                qDebug()<<sql_query.lastError();
            }
            else
            {
                qDebug()<<"insert success";
                this->hide();
            }
        }
    }

}

void Add_book::on_add_or_not_rejected()
{
    this->hide();
    ui->B_name->clear();
    ui->author->clear();
    ui->catagory->setCurrentIndex(0);
    QString date="2000-01-01";
    ui->date->setDate(QDate::fromString(date,"yyyy-MM-dd"));
    ui->publisher->clear();
    ui->total->setValue(0);
}
