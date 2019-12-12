#include "value_view.h"
#include "ui_value_view.h"
#include "eshimapi.h"
#include <QMessageBox>

value_view::value_view(int status,const QJsonObject &data,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::value_view)
{
    this->status = status;
    this->orginal_data = data;
    ui->setupUi(this);
    handle_status();
}
void value_view::handle_status(){
    if(this->status==0) { // open
        share_data();
        ui->pushButton->setText("Edit");
        ui->textEdit->setEnabled(false);
        ui->pushButton_2->hide();
    } else if(this->status==1) { // edit
        share_data();
        ui->pushButton->setText("Not edit");
        ui->textEdit->setEnabled(true);
        ui->pushButton_2->show();
    } else if(this->status==2) { //add
        ui->pushButton->hide();
        ui->textEdit->setEnabled(true);
        ui->pushButton_2->show();
    }
}
void value_view::share_data(){
    current_data = orginal_data;
    ui->lineEdit->setText(QString::number(current_data.value("id").toInt()));
    ui->lineEdit_2->setText(QString::number(current_data.value("type").toInt()));
    ui->lineEdit_3->setText(QString::number(current_data.value("user_id").toInt()));
    ui->textEdit->setText(current_data.value("value").toString());
}
void value_view::gather_data(){
    QJsonObject data;
    data.insert("action_id",orginal_data.value("action_id").toInt());
    data.insert("id",ui->lineEdit->text().toInt());
    data.insert("type",ui->lineEdit_2->text().toInt());
    data.insert("user_id",ui->lineEdit_3->text().toInt());
    data.insert("value",ui->textEdit->toPlainText());
    current_data = data;
}
value_view::~value_view()
{
    delete ui;
}

void value_view::on_pushButton_2_clicked()
{
    if(status==1) {
        eshimApi::updateActionValue(current_data.value("value").toString(),orginal_data.value("action_id").toInt(),orginal_data.value("id").toInt());
    } else if(status==2) {
        eshimApi::createActionValue(orginal_data.value("action_id").toInt(),current_data.value("value").toString());
    }
    this->close();
}

void value_view::on_pushButton_clicked()
{
    if(status==0) status=1;
    else if(status==1) status=0;
    handle_status();
}

void value_view::on_textEdit_textChanged()
{
    gather_data();
    if(status==1) {
        if(current_data == orginal_data) ui->pushButton_2->setEnabled(false);
        else ui->pushButton_2->setEnabled(true);
    }
}
