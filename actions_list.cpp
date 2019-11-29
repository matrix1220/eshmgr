#include "actions_list.h"
#include "ui_actions_list.h"
#include "eshimapi.h"
#include <QJsonObject>
#include <QJsonArray>
#include "action_view.h"
#include <QMessageBox>
actions_list::actions_list(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::actions_list)
{
    ui->setupUi(this);
    refreshlist();
}
void actions_list::refreshlist(){
    ui->listWidget->clear();
    foreach (const QJsonValue & t, eshimApi::method("getAllActions").value("result").toArray()){
        QListWidgetItem * t2 = new QListWidgetItem(ui->listWidget);
        t2->setData(100,t.toObject());
        t2->setText(t.toObject().value("key").toString());
        ui->listWidget->addItem(t2);
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
    this->hide();
    action_view w(0,item->data(100).toJsonObject(),this);
    w.setModal(true);
    w.exec();
    this->show();
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
        eshimApi::deleteAction(ui->listWidget->currentItem()->data(100).toJsonObject().value("key").toInt());
        QMessageBox::information(this,"Done","Deleted");
    }
    refreshlist();
}

void actions_list::on_pushButton_clicked()
{
    this->hide();
    action_view w(2,QJsonObject(),this);
    w.setModal(true);
    w.exec();
    refreshlist();
    this->show();
}
