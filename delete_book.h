#ifndef DELETE_BOOK_H
#define DELETE_BOOK_H

#include <QWidget>
#include "global.h"

namespace Ui {
class Delete_Book;
}

class Delete_Book : public QWidget
{
    Q_OBJECT

public:
    explicit Delete_Book(QWidget *parent = 0);
    void update_view();
    ~Delete_Book();

private:
    Ui::Delete_Book *ui;

private slots:
    void receive_from_admin();
    void on_search_clicked();
    void on_delete_book_clicked();
};

#endif // DELETE_BOOK_H
