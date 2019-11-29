#ifndef ESHIMAPI_H
#define ESHIMAPI_H
#include <QJsonDocument>

class eshimApi
{
public:
    eshimApi();
    static QJsonObject method(QString,QJsonObject);
    static QJsonObject method(QString);
    static QJsonObject strtoobj(const QString &);
    static QString objtostr(const QJsonObject &);
    static QString makeRequest(const QString &);
    static bool initUser(QString);

    static bool deleteAction(int id);
    static bool deleteActionValue(int action_id, int id);
    static void addAction(QString key);
    static void addActionValue(int action_id, QString value);
    static bool updateAction(QString key,int id);
    static bool updateActionValue(QString value,int action_id,int id);
    static QJsonArray getAllActionValues(int action_id);
    //static void getAction(QString key);
    //static void getActionValue(QString key);

    static int user_type;
private:
    static QString token;
};

#endif // ESHIMAPI_H
