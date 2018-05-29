#include "admin_main.h"
#include "ui_admin_main.h"

Admin_main::Admin_main(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Admin_main)
{
    ui->setupUi(this);
}

Admin_main::~Admin_main()
{
    delete ui;
}

void Admin_main::receive_from_login()
{
    this->show();
}

void Admin_main::on_add_book_clicked()
{
    send_to_addbook();
}

void Admin_main::on_delete_book_clicked()
{
    send_to_deletebook();
}

void Admin_main::on_insert_stu_clicked()
{
    send_to_insertstu();
}

void Admin_main::on_delete_stu_clicked()
{
    send_to_deletestu();
}

void Admin_main::on_search_book_clicked()
{
    send_to_searchbook();
}
