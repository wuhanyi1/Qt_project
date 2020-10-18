#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
class server : public QTcpServer //自己写的server
{
    Q_OBJECT
public:
    explicit server(QObject *parent = nullptr);

signals:

public slots:
    bool startServer(quint16 port = 8888);
    void stopServer();

   // void server_New_Connect();
    void incomingConnection(qintptr socketDiscriptor);//重写函数，根据套接字描述符在线程中创建新的socket
protected:

};

#endif // SERVER_H
