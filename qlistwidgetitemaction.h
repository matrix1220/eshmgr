#ifndef QLISTWIDGETITEMACTION_H
#define QLISTWIDGETITEMACTION_H
#include <QListWidgetItem>

#include <QObject>

class QListWidgetItemAction : public QListWidgetItem
{
public:
    QListWidgetItemAction();
    int id;
    int type;
    int user_id;
    QString key;
};

#endif // QLISTWIDGETITEMACTION_H
