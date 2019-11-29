#include "action_view.h"
#include "ui_action_view.h"
#include "eshimapi.h"
#include <QMessageBox>
#include "values_list.h"

action_view::action_view(int st,const QJsonObject &da, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::action_view)
{
    status = st;
    org_data = da;
    ui->setupUi(this);
    if(st!=2) sharedata(da);
    ui->lineEdit->setEnabled(false);
    ui->lineEdit_2->setEnabled(false);
    ui->lineEdit_3->setEnabled(false);
    handleStat(st);
}
void action_view::handleStat(int st){
    // 0 open
    // 1 edit
    // 2 add
    if(st==0) {
        ui->pushButton->setText("Edit");
        //ui->lineEdit->setEnabled(false);
        //ui->lineEdit_2->setEnabled(false);
        //ui->lineEdit_3->setEnabled(false);
        ui->textEdit->setEnabled(false);
        ui->pushButton_2->hide();
    } else if(st==1) {
        ui->pushButton->setText("Not edit");
        //ui->lineEdit->setEnabled(true);
        //ui->lineEdit_2->setEnabled(true);
        //ui->lineEdit_3->setEnabled(true);
        ui->textEdit->setEnabled(true);
        ui->pushButton_2->show();
    } else if(st==2) {
        ui->pushButton->hide();
        ui->textEdit->setEnabled(true);
        ui->pushButton_2->show();
    }
}
void action_view::sharedata(QJsonObject da){
    ui->lineEdit->setText(QString::number(da.value("id").toInt()));
    ui->lineEdit_2->setText(QString::number(da.value("type").toInt()));
    ui->lineEdit_3->setText(QString::number(da.value("user_id").toInt()));
    ui->textEdit->setText(da.value("key").toString());
}
QJsonObject action_view::gatherdata(){
    QJsonObject t;
    t.insert("id",ui->lineEdit->text().toInt());
    t.insert("type",ui->lineEdit_2->text().toInt());
    t.insert("user_id",ui->lineEdit_3->text().toInt());
    t.insert("key",ui->textEdit->toPlainText());
    return t;
}
action_view::~action_view()
{
    delete ui;
}

void action_view::on_pushButton_clicked()
{
    if(status==0) status=1;
    else if(status==1) status=0;
    handleStat(status);

}

void action_view::on_pushButton_2_clicked()
{
    QJsonObject data = gatherdata();
    if(status==1) {
        eshimApi::updateAction(data.value("key").toString(),data.value("id").toInt());
    } else if(status==2) {
        eshimApi::addAction(data.value("key").toString());
    }
    QMessageBox::information(this,"Done","Saved");
    this->close();
}

void action_view::on_pushButton_3_clicked()
{
    QJsonObject data = gatherdata();
    //this->hide();
    values_list w(data.value("id").toInt(),this);
    w.setModal(true);
    w.exec();
    this->show();
}
void action_view::reject() {
    QDialog::reject();
}
