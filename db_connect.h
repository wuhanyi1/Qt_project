#ifndef DB_CONNECTION_H
#define DB_CONNECTION_H

#include <QDebug>
#include <QSqlDatabase>
#include <QString>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QMessageBox>

static QSqlDatabase data_base;
//创建一个默认的连接，即只有一个连接
void createConnection();
bool is_exist_account(QString &account,QString &password);

#endif // DB_CONNECTION_H
