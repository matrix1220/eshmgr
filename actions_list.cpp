#include "actions_list.h"
#include "ui_actions_list.h"
#include "eshimapi.h"
#include "gettoken.h"
#include "action_view.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QMessageBox>

actions_list::actions_list(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::actions_list)
{
    ui->setupUi(this);
    refreshlist();
}
void actions_list::refreshlist(){
    int page = ui->spinBox->value();
    ui->listWidget->clear();
    foreach (const QJsonValue & item, eshimApi::getAllActions(page)){
        QListWidgetItem * widget_item = new QListWidgetItem(ui->listWidget);
        widget_item->setData(100,QVariant(item));
        widget_item->setText(item.toObject().value("key").toString());
        ui->listWidget->addItem(widget_item);
    }
}

actions_list::~actions_list()
{
    delete ui;
}

void actions_list::on_pushButton_3_clicked()
{
    refreshlist();
}

void actions_list::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    action_view actionview(0,item->data(100).toJsonObject(),this);
    actionview.setModal(true);
    actionview.exec();
    refreshlist();
}

void actions_list::on_pushButton_2_clicked()
{
    QMessageBox::StandardButton reply;
    //ui->listWidget->currentItem()->data(100).toJsonObject().value("key").toInt()
    reply = QMessageBox::question(this, "Delete", "do you want to delete " +
     ui->listWidget->currentItem()->data(100).toJsonObject().value("key").toString() +"?",
     QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        eshimApi::deleteAction(ui->listWidget->currentItem()->data(100).toJsonObject().value("id").toInt());
    }
    refreshlist();
}

void actions_list::on_pushButton_clicked()
{
    action_view w(2,QJsonObject(),this);
    w.setModal(true);
    w.exec();
    refreshlist();
}

void actions_list::on_pushButton_5_clicked()
{
    ui->spinBox->setValue(ui->spinBox->value()+1);
    refreshlist();
}

void actions_list::on_pushButton_4_clicked()
{
    if(ui->spinBox->value()>1){
        ui->spinBox->setValue(ui->spinBox->value()-1);
        refreshlist();
    }
}

void actions_list::on_spinBox_editingFinished()
{
    refreshlist();
}

void actions_list::on_pushButton_6_clicked()
{
    getToken::static_make_invalid();
    hide();
    eshimApi::initUser();
}
