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
    explicit value_view(int,const QJsonObject &,QWidget *parent = nullptr);
    ~value_view();
    int status;
    void handle_status();
    QJsonObject orginal_data;
    QJsonObject current_data;
    void share_data();
    void gather_data();
    int action_id;

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_textEdit_textChanged();

private:
    Ui::value_view *ui;
};

#endif // VALUE_VIEW_H
