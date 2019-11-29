#include "login_thread.h"
#include "login.h"
#include <QApplication>

login_thread::login_thread()
{

}
void login_thread::run() {
    login w;
    w.show();
}
