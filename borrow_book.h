#ifndef BORROW_BOOK_H
#define BORROW_BOOK_H

#include <QWidget>
#include "global.h"

namespace Ui {
class Borrow_Book;
}

class Borrow_Book : public QWidget
{
    Q_OBJECT

public:
    explicit Borrow_Book(QWidget *parent = 0);
    ~Borrow_Book();

private:
    Ui::Borrow_Book *ui;

private slots:
    void receive_from_stu();
    void on_Search_clicked();
    void on_borrow_clicked();
    void set_buttom(int ,int);
};

#endif // BORROW_BOOK_H
