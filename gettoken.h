#ifndef GETTOKEN_H
#define GETTOKEN_H
#include <QString>
#include <QFile>
#include <QTextStream>

class getToken : public QObject
{
    Q_OBJECT
public:
    explicit getToken(QObject *parent = nullptr);
    ~getToken();
    static void init();
signals:
    void tokenfail();
    void tokensuccess();
private slots:
    void tokenpassed(QString);
private:
    QFile * token_file;
    QString get();
    void set(QString);
    bool valid();
    static bool check(QString);
    void show();
};
#endif // GETTOKEN_H
