#ifndef SEARCH_STU_H
#define SEARCH_STU_H

#include <QWidget>
#include "search_stu.h"

namespace Ui {
class Search_Stu;
}

class Search_Stu : public QWidget
{
    Q_OBJECT

public:
    explicit Search_Stu(QWidget *parent = 0);
    ~Search_Stu();

private:
    Ui::Search_Stu *ui;

private slots:
    void receive_from_admin();

};

#endif // SEARCH_STU_H
