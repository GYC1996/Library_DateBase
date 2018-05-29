#ifndef ADMIN_SEARCH_H
#define ADMIN_SEARCH_H

#include <QWidget>
#include "global.h"

namespace Ui {
class Search_Book;
}

class Search_Book : public QWidget
{
    Q_OBJECT

public:
    explicit Search_Book(QWidget *parent = 0);
    ~Search_Book();

private:
    Ui::Search_Book *ui;

private slots:
    void receive_from_admin();
    void on_push_clicked();
};

#endif // ADMIN_SEARCH_H
