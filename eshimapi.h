#ifndef ESHIMAPI_H
#define ESHIMAPI_H
#include <QException>
#include <QJsonDocument>

class eshimApi
{
public:
    eshimApi();
    static QJsonObject method(QString,QJsonObject);
    static QJsonObject string_to_object(const QString &);
    static QString object_to_string(const QJsonObject &);
    static QString makeRequest(const QString &);
    static void initUser();
    static bool checkUser(QString);
    static void showMessage(QJsonObject response);
    static bool showMessageHelper(QJsonObject response);

    static bool deleteAction(int id);
    static bool deleteActionValue(int action_id, int id);
    static bool createAction(QString key);
    static bool createActionValue(int action_id, QString value);
    static bool updateAction(QString key,int id);
    static bool updateActionValue(QString value,int action_id,int id);
    static QJsonArray getAllActionsValues(int action_id,int page);
    static QJsonArray getAllActions(int page);
    //static void getAction(QString key);
    //static void getActionValue(QString key);

    static int user_type;

private:
    static QString token;
};

//class eshimException : public QException
//{
//public:
//    eshimException(int code,QString message);
//    void raise() const;
//    eshimException *clone() const;
//    int code;
//    QString message;
//};


#endif // ESHIMAPI_H
