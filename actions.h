#ifndef ACTIONS_H
#define ACTIONS_H

#include <QObject>

class actions : public QObject
{
    Q_OBJECT
public:
    explicit actions(QObject *parent = nullptr);

signals:

public slots:
};

#endif // ACTIONS_H
