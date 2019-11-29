#include "login.h"
#include "ui_login.h"
#include "actions_list.h"
#include <QFile>
#include <QTextStream>
#include <eshimapi.h>
#include <QCloseEvent>

login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
}

login::~login()
{
    delete ui;
}

void login::on_pushButton_clicked()
{
    ui->label->setText("Wrong token");
    QString token = ui->lineEdit->text();
    emit giveToken(token);
}
void login::gotFail()
{
    ui->label->setText("Wrong token");
}
void login::reject()
{
    exit(EXIT_SUCCESS);
}
