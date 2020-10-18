#include "widget.h"
#include <QApplication>
#include "server.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    server s;
    s.startServer(8765);

    return a.exec();
}
