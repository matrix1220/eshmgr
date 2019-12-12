#include "eshimapi.h"
#include "gettoken.h"
#include "login.h"
#include <QEventLoop>
#include <QtNetwork>
#include <QtDebug>
#include <QApplication>
#include <QMessageBox>

QString eshimApi::token;
int eshimApi::user_type;
eshimApi::eshimApi()
{
}
void eshimApi::initUser() {
    QApplication::setOverrideCursor(Qt::WaitCursor);
    getToken temp;
    if(temp.valid()) {
        if(checkUser(temp.get())) {
            QApplication::restoreOverrideCursor();
        } else {
            login w;
            w.exec();
        }
    } else {
        login w;
        w.exec();
    }
}
bool eshimApi::checkUser(QString t) {
    QJsonObject temp;
    temp.insert("method","getMe");
    temp.insert("token",t);
    temp = string_to_object(makeRequest(object_to_string(temp)));
    if(temp.value("ok").toBool()) {
        token = t;
        user_type = temp.value("type").toInt();
        getToken::static_set(token);
        return true;
    } else {
        return false;
    }
}

QJsonObject eshimApi::method(QString method, QJsonObject temp){
    temp.insert("method",method);
    temp.insert("token",eshimApi::token);
    temp = string_to_object(makeRequest(object_to_string(temp)));
    if(!temp.value("ok").toBool()) showMessage(temp);
//    {
//        eshimException ex(temp.value("err_code").toInt(),temp.value("err_str").toString());
//        ex.raise();
//    }
    return temp;
}
void eshimApi::showMessage(QJsonObject response){
    QMessageBox temp;
    if(response.value("ok").toBool()) {
        temp.setIcon(QMessageBox::Information);
        temp.setText("Done");
    } else {
        temp.setIcon(QMessageBox::Warning);
        temp.setText("Error message: " + response.value("err_str").toString());
    }
    temp.exec();
}

bool eshimApi::showMessageHelper(QJsonObject response) {
    bool temp = response.value("ok").toBool();
    if(temp) showMessage(response);
    return temp;
}
QString eshimApi::makeRequest(const QString &body) {
    QApplication::setOverrideCursor(Qt::WaitCursor);
    // http://matrix1220.uz/0wrM49mLns/asfjrvbajvvbalskdjnaksjvkjdfhbd
    // http://localhost:80/api
    QUrl url("http://matrix1220.uz/0wrM49mLns/asfjrvbajvvbalskdjnaksjvkjdfhbd");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentLengthHeader, QByteArray::number(body.size()));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QEventLoop waitLoop;
    QNetworkAccessManager* connection = new QNetworkAccessManager;
    qDebug() << body;
    QNetworkReply* reply = connection->post(request,body.toUtf8());
    QObject::connect(reply, SIGNAL(finished()), &waitLoop, SLOT(quit()));
    waitLoop.exec();

    QString response;
    if (reply->error() != 0){
        response="{\"ok\":false,\"err_str\":\"Connection Problem\"}";
    } else {
        response=reply->readAll();
    }
    qDebug() << response;
    delete reply;
    delete connection;
    QApplication::restoreOverrideCursor();
    return response;
}
QJsonObject eshimApi::string_to_object(const QString &str){
    return QJsonDocument::fromJson(str.toUtf8()).object();
}
QString eshimApi::object_to_string(const QJsonObject &obj){
    QJsonDocument temp(obj);
    QString t2 = temp.toJson(QJsonDocument::Compact);
    return t2;
}



bool eshimApi::deleteAction(int id)
{
    QJsonObject temp;
    temp.insert("action_id",id);
    temp = method("deleteAction",temp);
    return showMessageHelper(temp);
}

bool eshimApi::deleteActionValue(int action_id, int id)
{
    QJsonObject temp;
    temp.insert("action_id",action_id);
    temp.insert("id",id);
    temp = method("deleteActionValue",temp);
    return showMessageHelper(temp);
}
bool eshimApi::updateAction(QString key,int id)
{
    QJsonObject temp;
    temp.insert("key",key);
    temp.insert("action_id",id);
    temp = method("updateAction",temp);
    return showMessageHelper(temp);
}

bool eshimApi::updateActionValue(QString value,int action_id, int id)
{
    QJsonObject temp;
    temp.insert("value",value);
    temp.insert("action_id",action_id);
    temp.insert("id",id);
    temp = method("updateActionValue",temp);
    return showMessageHelper(temp);
}

bool eshimApi::createAction(QString key)
{
    QJsonObject temp;
    temp.insert("key",key);
    temp = method("createAction",temp);
    return showMessageHelper(temp);
}

bool eshimApi::createActionValue(int action_id, QString value)
{
    QJsonObject temp;
    temp.insert("action_id",action_id);
    temp.insert("value",value);
    temp = method("createActionValue",temp);
    return showMessageHelper(temp);
}

QJsonArray eshimApi::getAllActionsValues(int action_id,int page)
{
    QJsonObject temp;
    temp.insert("action_id",action_id);
    temp.insert("page",page);
    return method("getAllActionsValues",temp).value("result").toArray();
}

QJsonArray eshimApi::getAllActions(int page)
{
    QJsonObject temp;
    temp.insert("page",page);
    return method("getAllActions",temp).value("result").toArray();
}
//eshimException::eshimException(int code, QString message)
//{
//    this->code = code;
//    this->message = message;
//}

//void eshimException::raise() const { throw *this; }

//eshimException *eshimException::clone() const { return new eshimException(*this); }
