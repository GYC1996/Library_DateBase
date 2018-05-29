#include "stu_main.h"
#include "ui_stu_main.h"

Stu_main::Stu_main(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Stu_main)
{
    ui->setupUi(this);
}

Stu_main::~Stu_main()
{
    delete ui;
}

void Stu_main::receive_from_login()
{
    this->show();
}

void Stu_main::on_alter_passwd_clicked()
{
    send_to_alter_passwd();
}

void Stu_main::on_borrow_book_clicked()
{
    send_to_borrow();
}

void Stu_main::on_pushButton_3_clicked()
{
    send_to_return();
}
