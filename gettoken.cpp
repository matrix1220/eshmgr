#include "gettoken.h"
#include "login.h"
#include "eshimapi.h"
#include <QJsonObject>
#include <QWidget>
#include <QEventLoop>
#include <QDebug>
getToken::getToken(QObject *parent) : QObject(parent)
{
   token_file = new QFile("token.txt");
}
void getToken::init(){
    getToken t;
    if(t.valid()) {
        if(!check(t.get())) {
            t.show();
        }
    } else {
        t.show();
    }
}
void getToken::show() {
    login w;
    QWidget::connect(&w,SIGNAL(giveToken(QString)),this,SLOT(tokenpassed(QString)));
    QWidget::connect(this,SIGNAL(tokenfail()),&w,SLOT(gotFail()));
    w.show();
    QEventLoop waitLoop;
    QObject::connect(this,SIGNAL(tokensuccess()), &waitLoop, SLOT(quit()));
    waitLoop.exec();
}
void getToken::tokenpassed(QString t){
    //qDebug() << check(token);
    if(check(t)){
        this->set(t);
        emit tokensuccess();
    } else {
        emit tokenfail();
    }
}
bool getToken::check(QString token) {
    return eshimApi::initUser(token);
}
getToken::~getToken()
{
    delete token_file;
}
bool getToken::valid()
{
    return token_file->exists();
}

QString getToken::get()
{
    token_file->open(QFile::ReadOnly | QFile::Text);
    QTextStream tin(token_file);
    QString token = tin.readAll();
    token_file->close();
    return token;

}
void getToken::set(QString token)
{
    token_file->open(QFile::WriteOnly | QFile::Text);
    QTextStream tout(token_file);
    tout << token;
    token_file->close();
}
