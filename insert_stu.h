#ifndef INSERT_STU_H
#define INSERT_STU_H

#include <QWidget>
#include "global.h"

namespace Ui {
class Insert_Stu;
}

class Insert_Stu : public QWidget
{
    Q_OBJECT

public:
    explicit Insert_Stu(QWidget *parent = 0);
    ~Insert_Stu();

private slots:
    void on_insert_or_not_accepted();

    void on_insert_or_not_rejected();
    void receive_from_admin();

private:
    Ui::Insert_Stu *ui;
};

#endif // INSERT_STU_H
