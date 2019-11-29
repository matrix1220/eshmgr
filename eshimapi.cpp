#include "eshimapi.h"
#include <QEventLoop>
#include <QtNetwork>
#include <QtDebug>

QString eshimApi::token;
int eshimApi::user_type;

eshimApi::eshimApi()
{
}
bool eshimApi::initUser(QString t){
    QJsonObject temp;
    temp.insert("method","getMe");
    temp.insert("token",t);
    temp = strtoobj(makeRequest(objtostr(temp)));
    if(temp.value("ok").toBool()) {
        token = t;
        user_type = temp.value("type").toInt();
        return true;
    } else {
        return false;
    }
}

QJsonObject eshimApi::method(QString method, QJsonObject temp){
    temp.insert("method",method);
    temp.insert("token",eshimApi::token);
    return strtoobj(makeRequest(objtostr(temp)));
}

QJsonObject eshimApi::method(QString meth){
    QJsonObject temp;
    return method(meth,temp);
}
QString eshimApi::makeRequest(const QString &body) {
    QUrl url("http://localhost/api");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentLengthHeader, QByteArray::number(body.size()));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QEventLoop waitLoop;
    QNetworkAccessManager* connection = new QNetworkAccessManager;
    qDebug() << body;
    QNetworkReply* reply = connection->post(request,body.toUtf8());
    QObject::connect(reply, SIGNAL(finished()), &waitLoop, SLOT(quit()));
    waitLoop.exec();

    if (reply->error() != 0){
        // Show Error Message
    }
    QString response=reply->readAll();
    qDebug() << response;
    delete reply;
    delete connection;
    return response;
}
QJsonObject eshimApi::strtoobj(const QString &str){
    return QJsonDocument::fromJson(str.toUtf8()).object();
}
QString eshimApi::objtostr(const QJsonObject &obj){
    QJsonDocument temp(obj);
    QString t2 = temp.toJson(QJsonDocument::Compact);
    return t2;
}



bool eshimApi::deleteAction(int id)
{
    QJsonObject t;
    t.insert("action_id",id);
    return method("deleteAction",t).value("ok").toBool();
}

bool eshimApi::deleteActionValue(int action_id, int id)
{
    QJsonObject t;
    t.insert("action_id",action_id);
    t.insert("id",id);
    return method("deleteActionValue",t).value("ok").toBool();
}
bool eshimApi::updateAction(QString key,int id)
{
    QJsonObject t;
    t.insert("key",key);
    t.insert("action_id",id);
    return method("updateAction",t).value("ok").toBool();
}

bool eshimApi::updateActionValue(QString value,int action_id, int id)
{
    QJsonObject t;
    t.insert("value",value);
    t.insert("action_id",action_id);
    t.insert("id",id);
    return method("updateActionValue",t).value("ok").toBool();
}

QJsonArray eshimApi::getAllActionValues(int action_id)
{
    QJsonObject t;
    t.insert("action_id",action_id);
    return method("getAllActionValues",t).value("result").toArray();
}

void eshimApi::addAction(QString key)
{
    QJsonObject t;
    t.insert("key",key);
    method("addAction",t);
}

void eshimApi::addActionValue(int action_id, QString value)
{
    QJsonObject t;
    t.insert("action_id",action_id);
    t.insert("value",value);
    method("addActionValue",t);
}
