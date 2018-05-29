#ifndef STU_MAIN_H
#define STU_MAIN_H

#include <QWidget>
#include "global.h"

namespace Ui {
class Stu_main;
}

class Stu_main : public QWidget
{
    Q_OBJECT

public:
    explicit Stu_main(QWidget *parent = 0);
    ~Stu_main();

private:
    Ui::Stu_main *ui;

signals:
    void send_to_alter_passwd();
    void send_to_borrow();
    void send_to_return();

private slots:
    void receive_from_login();
    void on_alter_passwd_clicked();
    void on_borrow_book_clicked();
    void on_pushButton_3_clicked();
};

#endif // STU_MAIN_H
