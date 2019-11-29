#ifndef ACTIONS_LIST_H
#define ACTIONS_LIST_H

#include <QDialog>
#include <QListWidgetItem>

namespace Ui {
class actions_list;
}

class actions_list : public QDialog
{
    Q_OBJECT

public:
    explicit actions_list(QWidget *parent = nullptr);
    ~actions_list();

private slots:
    void on_pushButton_3_clicked();

    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::actions_list *ui;
    void refreshlist();
};

#endif // ACTIONS_LIST_H
