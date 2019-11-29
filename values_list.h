#ifndef VALUES_LIST_H
#define VALUES_LIST_H

#include <QDialog>
#include <QListWidgetItem>

namespace Ui {
class values_list;
}

class values_list : public QDialog
{
    Q_OBJECT

public:
    explicit values_list(int action_id,QWidget *parent = nullptr);
    ~values_list();
    void refreshlist();
    int id;
    virtual void reject();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

    void on_pushButton_3_clicked();

private:
    Ui::values_list *ui;
};

#endif // VALUES_LIST_H
