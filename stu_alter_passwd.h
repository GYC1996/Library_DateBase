#ifndef STU_ALTER_PASSWD_H
#define STU_ALTER_PASSWD_H

#include <QWidget>
#include "global.h"

namespace Ui {
class Stu_Alter_Passwd;
}

class Stu_Alter_Passwd : public QWidget
{
    Q_OBJECT

public:
    explicit Stu_Alter_Passwd(QWidget *parent = 0);
    ~Stu_Alter_Passwd();

private:
    Ui::Stu_Alter_Passwd *ui;

private slots:
    void receive_from_stu();
    void on_alter_passwd_accepted();
    void on_alter_passwd_rejected();
};

#endif // STU_ALTER_PASSWD_H
