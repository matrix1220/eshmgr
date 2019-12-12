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
    void handle_status();
    QJsonObject orginal_data;
    QJsonObject current_data;
    void share_data();
    void gather_data();
    virtual void reject();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_textEdit_textChanged();

private:
    Ui::action_view *ui;
};

#endif // ACTION_VIEW_H
