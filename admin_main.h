#ifndef ADMIN_MAIN_H
#define ADMIN_MAIN_H

#include <QWidget>
#include <global.h>

namespace Ui {
class Admin_main;
}

class Admin_main : public QWidget
{
    Q_OBJECT

public:
    explicit Admin_main(QWidget *parent = 0);
    ~Admin_main();

private slots:
    void receive_from_login();

    void on_add_book_clicked();

    void on_delete_book_clicked();

    void on_insert_stu_clicked();

    void on_delete_stu_clicked();

    void on_search_book_clicked();

private:
    Ui::Admin_main *ui;

signals:
    void send_to_addbook();
    void send_to_deletebook();
    void send_to_insertstu();
    void send_to_deletestu();
    void send_to_searchstu();
    void send_to_searchbook();
};

#endif // ADMIN_MAIN_H
