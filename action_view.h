#ifndef ACTION_VIEW_H
#define ACTION_VIEW_H

#include <QDialog>
#include <QJsonObject>

namespace Ui {
class action_view;
}

class action_view : public QDialog
{
    Q_OBJECT

public:
    explicit action_view(int,const QJsonObject&,QWidget *parent = nullptr);
    //action_view(int,QJsonObject,QWidget *parent = nullptr);
    ~action_view();
    int status;
    void handleStat(int);
    QJsonObject org_data;
    void sharedata(QJsonObject);
    QJsonObject gatherdata();
    virtual void reject();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::action_view *ui;
};

#endif // ACTION_VIEW_H
