#include "login.h"
#include <QApplication>
#include <QDebug>
#include <QJsonObject>
#include "gettoken.h"
#include "eshimapi.h"
#include "actions_list.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    getToken::init();
    //jsdhfakjhvb
    actions_list w;
    w.show();
    return a.exec();
}
