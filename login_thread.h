#ifndef LOGIN_THREAD_H
#define LOGIN_THREAD_H
#include <QThread>
#include <QString>

class login_thread : public QThread
{
public:
    login_thread();
    void run();
private:
    QString token;
};

#endif // LOGIN_THREAD_H
