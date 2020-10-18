#include "thread.h"
#include <QDebug>
//QThread中有个run虚函数，我们可以在子类重写，run接受一个函数，去创建一个线程运行这个函数
Thread::Thread(int socketID,QObject *parent) : QThread(parent),sockerDescriptor(socketID)
{
    qDebug()<<socketID;
}

void Thread::run(){
    socket =new QTcpSocket();
    if(socket->setSocketDescriptor(this->sockerDescriptor) == false){//给新创建的socket设置标识符
        qDebug()<<"set socketDescription failed!";
        //delete socket;
        return;
    }
    connect(socket,SIGNAL(readyRead()),this,SLOT(read()),Qt::DirectConnection);//该参数直接在信号函数所在线程中调用槽函数
    connect(socket,SIGNAL(disconnected()),this,SLOT(disconnected()),Qt::DirectConnection);//对方断开连接，我也要断开
    this->exec();//this是server对象指针，他需要持续监听
}

void Thread::read(){
    QByteArray buff=this->socket->readAll();
    qDebug()<<"send to kehu";
    this->socket->write(buff);
}

void Thread::disconnected(){
    this->socket->disconnectFromHost(); //关闭主机
    this->socket->close();              //关闭这个类
    this->socket->deleteLater();        //释放这个类
    this->exit();                       //退出线程
}
