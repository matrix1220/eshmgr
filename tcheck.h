#ifndef TCHECK_H
#define TCHECK_H

#include <QObject>

class tcheck : public QObject
{
    Q_OBJECT
public:
    explicit tcheck(QObject *parent = nullptr);

signals:

public slots:
};

#endif // TCHECK_H
