#ifndef VALUE_VIEW_H
#define VALUE_VIEW_H

#include <QDialog>
#include <QJsonObject>

namespace Ui {
class value_view;
}

class value_view : public QDialog
{
    Q_OBJECT

public:
    explicit value_view(int st,int,const QJsonObject &da,QWidget *parent = nullptr);
    ~value_view();
    int status;
    void handleStat(int);
    QJsonObject org_data;
    void sharedata(QJsonObject);
    QJsonObject gatherdata();
    int action_id;

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::value_view *ui;
};

#endif // VALUE_VIEW_H
