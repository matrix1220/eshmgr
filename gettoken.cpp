#include "gettoken.h"
#include "login.h"
#include "eshimapi.h"
#include <QJsonObject>
#include <QWidget>
#include <QEventLoop>
#include <QDebug>
#include <QApplication>
getToken::getToken(QObject *parent) : QObject(parent)
{
   token_file = new QFile("token.txt");
}

getToken::~getToken()
{
    delete token_file;
}
bool getToken::valid()
{
    return token_file->exists();
}
void getToken::make_invalid()
{
    token_file->remove();
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
void getToken::static_make_invalid() {
    getToken temp;
    temp.make_invalid();
}
void getToken::static_set(QString token)
{
    getToken temp;
    temp.set(token);
}
