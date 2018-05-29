#ifndef DELETE_STU_H
#define DELETE_STU_H

#include <QWidget>
#include "global.h"

namespace Ui {
class Delete_Stu;
}

class Delete_Stu : public QWidget
{
    Q_OBJECT

public:
    explicit Delete_Stu(QWidget *parent = 0);
    ~Delete_Stu();

private:
    Ui::Delete_Stu *ui;
private slots:
    void receive_from_admin();
    void on_search_clicked();
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
};

#endif // DELETE_STU_H
