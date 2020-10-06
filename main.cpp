#include "login_scene.h"
#include <QApplication>
#include "db_connect.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Login_scene w;
    w.set_bg();
    w.show();

    createConnection();
    return a.exec();
}
