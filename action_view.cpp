#include "action_view.h"
#include "ui_action_view.h"
#include "eshimapi.h"
#include <QMessageBox>
#include "values_list.h"

action_view::action_view(int status,const QJsonObject &data, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::action_view)
{
    this->status = status;
    this->orginal_data = data;
    this->current_data = data;
    ui->setupUi(this);
    this->handle_status();
}
void action_view::handle_status(){
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
        ui->pushButton_3->setEnabled(false);
        ui->pushButton_2->show();
    }
}
void action_view::share_data(){
    this->current_data = this->orginal_data;
    ui->lineEdit->setText(QString::number(this->current_data.value("id").toInt()));
    ui->lineEdit_2->setText(QString::number(this->current_data.value("type").toInt()));
    ui->lineEdit_3->setText(QString::number(this->current_data.value("user_id").toInt()));
    ui->textEdit->setText(this->current_data.value("key").toString());
}
void action_view::gather_data(){
    QJsonObject data;
    data.insert("id",ui->lineEdit->text().toInt());
    data.insert("type",ui->lineEdit_2->text().toInt());
    data.insert("user_id",ui->lineEdit_3->text().toInt());
    data.insert("key",ui->textEdit->toPlainText());
    this->current_data = data;
}
action_view::~action_view()
{
    delete ui;
}

void action_view::on_pushButton_clicked()
{
    if(status==0) status=1;
    else if(status==1) status=0;
    handle_status();

}

void action_view::on_pushButton_2_clicked()
{
    if(status==1) {
        eshimApi::updateAction(this->current_data.value("key").toString(),this->current_data.value("id").toInt());
    } else if(status==2) {
        eshimApi::createAction(this->current_data.value("key").toString());
    }
    this->close();
}

void action_view::on_pushButton_3_clicked()
{
    //this->hide();
    values_list w(current_data.value("id").toInt(),this);
    w.setModal(true);
    w.exec();
    this->show();
}
void action_view::reject() {
    QDialog::reject();
}

void action_view::on_textEdit_textChanged()
{
    gather_data();
    if(status==1) {
        if(current_data == orginal_data) ui->pushButton_2->setEnabled(false);
        else ui->pushButton_2->setEnabled(true);
    }
}
