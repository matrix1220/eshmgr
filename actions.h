#ifndef ACTIONS_H
#define ACTIONS_H

#include <QObject>
#include <QJsonObject>

class Action : public QObject
{
    Q_OBJECT
public:
    Action(QJsonObject temp,QObject *parent = nullptr);
    int id;
    int user_id;
    int type;
    QString key;
};
#endif // ACTIONS_H
