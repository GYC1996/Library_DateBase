#ifndef RETURN_BOOK_H
#define RETURN_BOOK_H

#include <QWidget>
#include "global.h"

namespace Ui {
class Return_Book;
}

class Return_Book : public QWidget
{
    Q_OBJECT

public:
    explicit Return_Book(QWidget *parent = 0);
    ~Return_Book();

private:
    Ui::Return_Book *ui;

private slots:
    void receive_from_stu();
    void on_return_book_clicked();
};

#endif // RETURN_BOOK_H
