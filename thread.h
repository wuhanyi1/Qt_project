#ifndef THREAD_H
#define THREAD_H

#include <QObject>
#include <QThread>
#include <QTcpSocket>
class Thread : public QThread
{
    Q_OBJECT
public:
    explicit Thread(int socketID,QObject *parent = nullptr);//创建一个线程时指定一个socketID

signals:

protected:
    void run();

private:
    int sockerDescriptor;
    QTcpSocket *socket;

private slots:
    void read();
    void disconnected();
};

#endif // THREAD_H
