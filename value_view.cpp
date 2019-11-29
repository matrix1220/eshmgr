#include "value_view.h"
#include "ui_value_view.h"
#include "eshimapi.h"
#include <QMessageBox>

value_view::value_view(int st,int a_id,const QJsonObject &da,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::value_view)
{
    status = st;
    org_data = da;
    action_id = a_id;
    ui->setupUi(this);
    if(st!=2) sharedata(da);
    ui->lineEdit->setEnabled(false);
    ui->lineEdit_2->setEnabled(false);
    ui->lineEdit_3->setEnabled(false);
    handleStat(st);
}
void value_view::handleStat(int st){
    // 0 open
    // 1 edit
    // 2 add
    if(st==0) {
        ui->pushButton->setText("Edit");
        ui->textEdit->setEnabled(false);
        ui->pushButton_2->hide();
    } else if(st==1) {
        ui->pushButton->setText("Not edit");
        ui->textEdit->setEnabled(true);
        ui->pushButton_2->show();
    } else if(st==2) {
        ui->pushButton->hide();
        ui->textEdit->setEnabled(true);
        ui->pushButton_2->show();
    }
}
void value_view::sharedata(QJsonObject da){
    ui->lineEdit->setText(QString::number(da.value("id").toInt()));
    ui->lineEdit_2->setText(QString::number(da.value("type").toInt()));
    ui->lineEdit_3->setText(QString::number(da.value("user_id").toInt()));
    ui->textEdit->setText(da.value("value").toString());
}
QJsonObject value_view::gatherdata(){
    QJsonObject t;
    t.insert("id",ui->lineEdit->text().toInt());
    t.insert("type",ui->lineEdit_2->text().toInt());
    t.insert("user_id",ui->lineEdit_3->text().toInt());
    t.insert("value",ui->textEdit->toPlainText());
    return t;
}
value_view::~value_view()
{
    delete ui;
}

void value_view::on_pushButton_2_clicked()
{
    QJsonObject data = gatherdata();
    if(status==1) {
        eshimApi::updateActionValue(data.value("value").toString(),org_data.value("action_id").toInt(),org_data.value("id").toInt());
    } else if(status==2) {
        eshimApi::addActionValue(action_id,data.value("value").toString());
    }
    QMessageBox::information(this,"Done","Saved");
    this->close();
}

void value_view::on_pushButton_clicked()
{
    if(status==0) status=1;
    else if(status==1) status=0;
    handleStat(status);
}
