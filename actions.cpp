#include "actions.h"

Action::Action(QJsonObject temp, QObject *parent) : QObject(parent)
{
    id=temp.value("id").toInt();
    type=temp.value("type").toInt();
    user_id=temp.value("user_id").toInt();
    key=temp.value("key").toString();
}
