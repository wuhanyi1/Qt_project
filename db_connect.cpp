#include "db_connect.h"


void createConnection()
{


    //打开MySQL
    data_base = QSqlDatabase::addDatabase("QMYSQL");
    data_base.setHostName("127.0.0.1");  //设置主机地址
    data_base.setPort(3306);  //设置端口
    data_base.setDatabaseName("manage_sys");  //设置数据库名称
    data_base.setUserName("root");  //设置用户名
    data_base.setPassword("19970813");  //设置密码
    if(!data_base.open())
        qDebug()<<"failed to connect to mysql";

}

bool is_exist_account(QString &account,QString &password){
    QSqlQuery query;
    QString str = QString("select passwd from login_info where id = '%1'").arg(account);
    qDebug()<<str;
    query.exec(str);


    if(!query.next()){
        QMessageBox::information(nullptr, "Wrong!", "无此用户!",  \
                                 QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    }
    else if(query.value(0).toString() != password){
        QMessageBox::information(nullptr, "Wrong!", "密码错误!",  \
                                 QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    }
    return true;
}
