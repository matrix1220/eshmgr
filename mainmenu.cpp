#include "mainmenu.h"
#include "ui_mainmenu.h"
#include "actions_list.h"

mainMenu::mainMenu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mainMenu)
{
    ui->setupUi(this);
}

mainMenu::~mainMenu()
{
    delete ui;
}

void mainMenu::on_pushButton_clicked()
{
    this->hide();
    actions_list * al = new actions_list;
    al->exec();
    delete al;
    this->show();
}

void mainMenu::on_pushButton_2_clicked()
{

}
