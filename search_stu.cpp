#include "search_stu.h"
#include "ui_search_stu.h"

Search_Stu::Search_Stu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Search_Stu)
{
    ui->setupUi(this);
}

Search_Stu::~Search_Stu()
{
    delete ui;
}

void Search_Stu::receive_from_admin()
{
    this->show();
}
