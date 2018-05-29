#ifndef ADD_BOOK_H
#define ADD_BOOK_H

#include <QWidget>
#include "global.h"

namespace Ui {
class Add_book;
}

class Add_book : public QWidget
{
    Q_OBJECT

public:
    explicit Add_book(QWidget *parent = 0);
    //bool selected(QString c);
    ~Add_book();

private:
    Ui::Add_book *ui;

private slots:
    void receive_from_admin();
    void on_add_or_not_accepted();
    void on_add_or_not_rejected();
};

#endif // ADD_BOOK_H
