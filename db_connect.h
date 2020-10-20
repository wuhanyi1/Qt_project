#ifndef DB_CONNECTION_H
#define DB_CONNECTION_H

#include <QDebug>
#include <QSqlDatabase>
#include <QString>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QMessageBox>

static QSqlDatabase data_base;
static QSqlQuery *query;
//创建一个默认的连接，即只有一个连接
void createConnection();
bool is_exist_account(QString &account,QString &password);//判断账户是否存在
bool is_exist_course(QString &c_id);//用户是否选了此课程
QSqlQuery& inquire_stu_info(QString &account);//查看学生的所有信息
QList<QString> inquire_stu_select_info(QString &account);//获取该学生选课的c_id列表
QSqlQuery& inquire_stu_grade(QString &account);//查看学生成绩
QSqlQuery& inquire_all_course_info();//查找所有课程信息
QSqlQuery* inquire_stu_choosed_course(QString &c_id);//查看学生已选课的信息
QSqlQuery& inquire_special_course(QString &s1,QString &s2,QString &s3);//根据下拉栏信息检索查找符合要求课程
int inquire_remain_num(QString &course_id);//查找课程剩余数量
int inquire_course_score(QString &course_id);//查看课程学分
int inquire_stu_credit(QString &account);//查看学生学分
void update_course_num(QString &c_id,int num);//更新课程数量
void update_stu_credit(QString &s_id,int num);//更新学生学分
void insert_select_info(QString &s_id,QString &c_id);//插入选课记录
void delete_select_record(QString &c_id);//删除选课记录

#endif // DB_CONNECTION_H
