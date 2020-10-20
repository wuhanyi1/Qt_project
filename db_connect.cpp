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
    ::query=new QSqlQuery;

}

bool is_exist_account(QString &account,QString &password){
    //QSqlQuery query;
    QString str = QString("select passwd from login_info where id = '%1'").arg(account);
   // qDebug()<<str;
    query->exec(str);


    if(!query->next()){
        QMessageBox::information(nullptr, "Wrong!", "无此用户!",  \
                                 QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    }
    else if(query->value(0).toString() != password){
        QMessageBox::information(nullptr, "Wrong!", "密码错误!",  \
                                 QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    }
    else return true;
    return false;
}

bool is_exist_course(QString &c_id){
    QString str=QString("select * from select_table where c_id='%1'").arg(c_id);
    query->exec(str);
    if(query->size()) return true;
    else return false;
}

QSqlQuery& inquire_stu_info(QString &account){
    //QSqlQuery *query=new QSqlQuery;
    QString str=QString("select * from stu_info where id = '%1'").arg(account);
    query->exec(str);

    return *query;
}

QSqlQuery& inquire_stu_grade(QString &account){
   // QSqlQuery *query = new QSqlQuery;
    QString str=QString("select * from grade_info where s_id = '%1'").arg(account);
    query->exec(str);

    return *query;
}

QSqlQuery& inquire_all_course_info(){
    //QSqlQuery *query=new QSqlQuery;
    QString str=QString("select * from course_info");
    query->exec(str);

    return *query;
}

QSqlQuery* inquire_stu_choosed_course(QString &c_id){
    QString str=QString("select * from course_info where c_id ='%1'").arg(c_id);
    query->exec(str);
    return query;
}

QSqlQuery& inquire_special_course(QString &s1,QString &s2,QString &s3){
   // QSqlQuery *query=new QSqlQuery;
    QString str=QString("select * from course_info where (department_id='%1' and c_level ='%2' and c_teach_pos ='%3')").arg(s1).arg(s2).arg(s3);
    qDebug()<<str;
    query->exec(str);

    return *query;
}

int inquire_remain_num(QString &course_id){
    QString str=QString("select c_remain from course_info where c_id ='%1'").arg(course_id);
    query->exec(str);
    query->first();
    return query->value(0).toInt();
}

int inquire_course_score(QString &c_id){
    QString str=QString("select c_score from course_info where c_id ='%1'").arg(c_id);
    query->exec(str);
    query->first();
    return query->value(0).toInt();
}

int inquire_stu_credit(QString &account){
    QString str=QString("select s_credit from stu_info where id='%1'").arg(account);
    query->exec(str);
    query->first();
    return query->value(0).toInt();
}

void update_course_num(QString &id,int num){
    QString str=QString("update course_info set c_remain ='%2' where c_id ='%1'").arg(id).arg(num);
    query->exec(str);
}

void update_stu_credit(QString &s_id,int num){
    QString str=QString("update stu_info set s_credit ='%2' where id ='%1'").arg(s_id).arg(num);
    query->exec(str);
}

void insert_select_info(QString &s_id,QString &c_id){//
    QString str=QString("insert into select_table (s_id,c_id) values ('%1','%2')").arg(s_id).arg(c_id);
    query->exec(str);
}

QList<QString> inquire_stu_select_info(QString &account){
    QString str=QString("select c_id from select_table where s_id='%1'").arg(account);
    query->exec(str);
    QList<QString> list;
    while (query->next()) {
        list.push_back(query->value(0).toString());
    }
    return list;
}

void delete_select_record(QString &c_id){
    QString str=QString("delete from select_table where c_id ='%1'").arg(c_id);
    query->exec(str);
}
