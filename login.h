#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QFile>

namespace Ui {
class login;
}

class login : public QDialog
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();
    virtual void reject();

signals:
private slots:
    void on_pushButton_clicked();

private:
    Ui::login *ui;
};

#endif // LOGIN_H
