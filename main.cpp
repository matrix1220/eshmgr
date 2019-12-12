#include <QApplication>
#include <QDebug>
#include "eshimapi.h"
#include "mainmenu.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    eshimApi::initUser();
    mainMenu main;
    main.show();
    //ewrjlsskhm
    //actions_list w;
    //w.show();
    return a.exec();
}
