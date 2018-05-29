#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <global.h>

namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();

private slots:
    void on_login_clicked();

signals:
    void send_to_admin_main();
    void send_to_Stu_main();

private:
    Ui::Login *ui;
};

#endif // LOGIN_REGISTER_H
