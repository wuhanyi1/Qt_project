#ifndef DB_CONNECTION_H
#define DB_CONNECTION_H

#include <QDebug>
#include <QSqlDatabase>
#include <QString>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QMessageBox>

static QSqlDatabase data_base;
static QSqlQuery *query=nullptr;
//创建一个默认的连接，即只有一个连接
void createConnection();
bool is_exist_account(QString &account,QString &password);
QSqlQuery& inquire_stu_info(QString &account);
QSqlQuery& inquire_stu_grade(QString &account);
QSqlQuery& inquire_all_course_info();//查找所有课程信息
QSqlQuery& inquire_special_course(QString &s1,QString &s2,QString &s3);//根据下拉栏信息检索查找符合要求课程
int inquire_remain_num(QString &course_id);
int inquire_course_score(QString &course_id);
int inquire_stu_credit(QString &account);
void update_course_num(QString &c_id,int num);
void update_stu_credit(QString &s_id,int num);
#endif // DB_CONNECTION_H
