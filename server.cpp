#include "server.h"
#include <QDebug>
#include "thread.h"
server::server(QObject *parent) : QTcpServer(parent)
{

}

bool server::startServer(quint16 port){
    if(this->isListening()){//检查服务器是不是本来就运行了
        qDebug()<<"server is running";
    }
    else{
        if(this->listen(QHostAddress::AnyIPv4,port)){////启动服务器监听端口
            qDebug()<<"开始监听";
            return true;//成功启动
        }
        else {
            qDebug()<<"connect failed";
        };
    }
    return true;
}

void server::stopServer(){
    this->close();
}

void server::incomingConnection(qintptr socketDiscriptor){//
    Thread *h=new Thread(socketDiscriptor);
    qDebug()<<"听到连接请求，创建线程";
    connect(h,SIGNAL(finished()),h,SLOT(deleteLater()));//线程结束，释放内存
    h->start();
}
