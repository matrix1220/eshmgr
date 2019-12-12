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
    QString get();
    void set(QString);
    bool valid();
    void make_invalid();

    static QString static_get();
    static void static_set(QString);
    static bool static_valid();
    static void static_make_invalid();
private:
    QFile * token_file;
};
#endif // GETTOKEN_H
