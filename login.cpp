#include "login.h"
#include "ui_login.h"
#include "actions_list.h"
#include <QFile>
#include <QTextStream>
#include "eshimapi.h"
#include <QCloseEvent>

login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    QApplication::restoreOverrideCursor();
}

login::~login()
{
    delete ui;
}

void login::on_pushButton_clicked()
{
    ui->label->setText("Token");
    QString token = ui->lineEdit->text();
    if(eshimApi::checkUser(token)) {
        this->hide();
    } else {
        ui->label->setText("Wrong token");
    }
}
void login::reject()
{
    //QApplication::quit();
    exit(EXIT_SUCCESS);
}
