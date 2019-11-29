#include "values_list.h"
#include "ui_values_list.h"
#include "eshimapi.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QMessageBox>
#include "value_view.h"

values_list::values_list(int action_id,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::values_list)
{
    ui->setupUi(this);
    id = action_id;
    refreshlist();
}

values_list::~values_list()
{
    delete ui;
}

void values_list::refreshlist()
{
    ui->listWidget->clear();
    foreach (const QJsonValue & t, eshimApi::getAllActionValues(id)){
        QListWidgetItem * t2 = new QListWidgetItem(ui->listWidget);
        QJsonObject t1 = t.toObject();
        t1.insert("action_id",id);
        t2->setData(100,t.toObject());
        t2->setText(t.toObject().value("value").toString());
        ui->listWidget->addItem(t2);
    }
}

void values_list::on_pushButton_2_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Delete", "do you want to delete " +
     ui->listWidget->currentItem()->data(100).toJsonObject().value("value").toString() +"?",
     QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        eshimApi::deleteActionValue(id,ui->listWidget->currentItem()->data(100).toJsonObject().value("key").toInt());
        QMessageBox::information(this,"Done","Deleted");
    }
    refreshlist();
}

void values_list::on_pushButton_clicked()
{
    //this->hide();
    value_view w(2,id,QJsonObject(),this);
    w.setModal(true);
    w.exec();
    refreshlist();
    //this->show();
}

void values_list::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    //this->hide();
    value_view w(0,id,item->data(100).toJsonObject(),this);
    w.setModal(true);
    w.exec();
    refreshlist();
    //this->show();
}

void values_list::on_pushButton_3_clicked()
{
    refreshlist();
}
void values_list::reject() {
    QDialog::reject();
}
