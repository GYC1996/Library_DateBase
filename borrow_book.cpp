#include "borrow_book.h"
#include "ui_borrow_book.h"
#include <QRadioButton>
#include <QDate>

Borrow_Book::Borrow_Book(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Borrow_Book)
{
    ui->setupUi(this);
}

Borrow_Book::~Borrow_Book()
{
    delete ui;
}

void Borrow_Book::receive_from_stu()
{
    this->show();
    connect(ui->Search_In,SIGNAL(cellChanged(int,int)),this,SLOT(set_buttom(int,int)));
    //信号槽机制可进行参数传递
}

void Borrow_Book::on_Search_clicked()
{
    //qDebug()<<ui->Search_In->rowCount();
    int row=ui->Search_In->rowCount();
    int j;
    for(j=0;j<row;j++)
    {
        ui->Search_In->removeRow(0);
    }
    //qDebug()<<ui->Search_In->rowCount()<<j;
    QString book=ui->Book_name->text();
    QSqlQuery sql_query(db);
    QString select_sql="select * from Book where Bname like ?";
    QString search_name="%"+book+"%";
    qDebug()<<search_name;
    sql_query.prepare(select_sql);
    sql_query.addBindValue(search_name);
    if(!sql_query.exec())
    {
        qDebug()<<sql_query.lastError();
    }
    else
    {
        ui->Search_In->verticalHeader()->setDefaultSectionSize(30);
        ui->Search_In->setColumnCount(9);
        QStringList header;
        header<<tr("书名")<<tr("书号")<<tr("类别")<<tr("作者")<<tr("出版日期")<<tr("出版社")<<tr("库存量")<<tr("可借量")<<tr("选择");
        ui->Search_In->setHorizontalHeaderLabels(header);
        int i;
        while(sql_query.next())
        {
            i=ui->Search_In->rowCount();
            ui->Search_In->insertRow(i);
            ui->Search_In->setItem(i,0,new QTableWidgetItem(sql_query.value(1).toString()));
            ui->Search_In->setItem(i,1,new QTableWidgetItem(sql_query.value(0).toString()));
            ui->Search_In->setItem(i,2,new QTableWidgetItem(sql_query.value(2).toString()));
            ui->Search_In->setItem(i,3,new QTableWidgetItem(sql_query.value(4).toString()));
            ui->Search_In->setItem(i,4,new QTableWidgetItem(sql_query.value(3).toString()));
            ui->Search_In->setItem(i,5,new QTableWidgetItem(sql_query.value(6).toString()));
            ui->Search_In->setItem(i,6,new QTableWidgetItem(sql_query.value(5).toString()));
            ui->Search_In->setItem(i,7,new QTableWidgetItem(sql_query.value(7).toString()));
            QTableWidgetItem *check=new QTableWidgetItem;
            if(sql_query.value(7).toString()!="0")
            {
                check->setCheckState (Qt::Unchecked);
            }
            ui->Search_In->setItem(i,8,check);

            //QList<QRadioButton*> rad = widget->findChildren<QRadioButton *>();
            //ui->Search_In->setItem(i,7,new QTableWidgetItem(new QRadioButtom("select",this)));
            //qDebug()<<"i="<<i;
        }
    }
}

void Borrow_Book::set_buttom(int row,int col)
{
    qDebug()<<"huhfdv"<<row<<" "<<col;
    if(ui->Search_In->item(row, col)->checkState() == Qt::Checked)
    {
        for(int i=0;i<ui->Search_In->rowCount();i++)
        {
            if(i!=row && ui->Search_In->item(i,7)->text()!="0")
            {
                ui->Search_In->item(i,col)->setCheckState(Qt::Unchecked);

            }
        }
        ui->borrow->setEnabled(true);
    }
    else
    {
        ui->borrow->setEnabled(false);
    }
}

void Borrow_Book::on_borrow_clicked()
{
    int row=ui->Search_In->rowCount();
    for(int i=0;i<row;i++)
    {
        if(ui->Search_In->item(i,8)->checkState()==Qt::Checked)
        {
            QString select_sql="select No,Stu_no from record where Book_id=? order by No asc";
            QSqlQuery sql_query(db);
            sql_query.prepare(select_sql);
            sql_query.addBindValue(ui->Search_In->item(i,1)->text());
            int number=1;
            bool borrow_enable=true;
            if(!sql_query.exec())
            {
                qDebug()<<sql_query.lastError();
            }
            else
            {
                while(sql_query.next())
                {
                    qDebug()<<sql_query.value(0).toString();
                    if(sql_query.value(0)!=number)
                        break;
                    number++;
                }
                sql_query.seek(0);
                if(sql_query.value(1)!=usename_global)
                {
                    qDebug()<<sql_query.value(0).toString();
                    while(sql_query.next())
                    {
                        qDebug()<<sql_query.value(0).toString();
                        if(sql_query.value(1)==usename_global)
                        {
                           borrow_enable=false;
                           break;
                        }
                    }
                }
                else
                {
                    qDebug()<<sql_query.value(0).toString();
                    borrow_enable=false;
                }
            }

            if(borrow_enable)
            {
                QString insert_sql="insert into record values(?,?,?,?,?)";
                sql_query.prepare(insert_sql);
                sql_query.addBindValue(ui->Search_In->item(i,1)->text());
                sql_query.addBindValue(number);
                sql_query.addBindValue(usename_global);
                QDate date = QDate::currentDate();
                qDebug()<<date.toString("yyyy-MM-dd");
                sql_query.addBindValue(date.toString("yyyy-MM-dd"));
                QDate return_day=date.addMonths(1);
                sql_query.addBindValue(return_day.toString("yyyy-MM-dd"));
                if(!sql_query.exec())
                {
                    qDebug()<<sql_query.lastError();
                }
                else
                {
                    qDebug()<<"借书成功 update record";
                }

                QString update_sql="update Book set lend_able=lend_able-1 where Bid=?";
                sql_query.prepare(update_sql);
                sql_query.addBindValue(ui->Search_In->item(i,1)->text());
                if(!sql_query.exec())
                {
                    qDebug()<<sql_query.lastError();
                }
                else
                {
                    qDebug()<<"借书成功 update book";
                }

                update_sql="update Student set B_num=B_num+1 where Sno=?";
                sql_query.prepare(update_sql);
                sql_query.addBindValue(usename_global);
                if(!sql_query.exec())
                {
                    qDebug()<<sql_query.lastError();
                }
                else
                {
                    qDebug()<<"借书成功 update student";
                }
            }
            else
            {
                qDebug()<<"不可借同一本书";
            }
        }
    }
}
