#include "course_op_scene.h"
#include "ui_course_op_scene.h"
#include "db_connect.h"

course_op_scene::course_op_scene(QWidget *parent) :
    QWidget(parent),account(""),
    ui(new Ui::course_op_scene)
{
    ui->setupUi(this);
}

course_op_scene::~course_op_scene()
{
    delete ui;
}

void course_op_scene::set_bg(QString &account){
    this->account=account;//每个界面都要把用户的账号记下来
    this->setWindowIcon(QIcon(":/Image/Image/ustc.jpg"));//设置Widget左上角图片
    this->setFixedSize(1020,888);//设置登录界面固定大小


    QStringList strList1,strList2,strList3;
    strList1<<"001:数学科学院"<<"002:化学物理系"<<"003:计算机科学与技术系"<<"A13:软件学院合肥";
    strList2<<"本科"<<"研究生";
    strList3<<"东区"<<"西区"<<"南区"<<"中区"<<"先研院";
    ui->label->setText("开课单位");
    ui->label_2->setText("学历层次");
    ui->label_3->setText("校区");
    ui->label->move(10,20);
    ui->label_2->move(260,20);
    ui->label_3->move(510,20);
    ui->label->resize(100,40);
    ui->label_2->resize(100,40);
    ui->label_3->resize(100,40);

    ui->comboBox->move(10,60);
    ui->comboBox_2->move(260,60);
    ui->comboBox_3->move(510,60);
    ui->comboBox->resize(190,45);
    ui->comboBox_2->resize(190,45);
    ui->comboBox_3->resize(190,45);
    ui->comboBox->addItems(strList1);
    ui->comboBox_2->addItems(strList2);
    ui->comboBox_3->addItems(strList3);

    ui->pushButton->move(750,60);
    ui->pushButton->resize(180,45);
    ui->pushButton->setStyleSheet("QPushButton{font-family:'楷体';font-size:32px;color:rgb(0,0,0,255);} \
    QPushButton{background-color:rgb(170,200,50)} QPushButton:hover{background-color:rgb(50, 170, 200)}");
    ui->pushButton_2->move(730,150);
    ui->pushButton_3->move(730,220);
    ui->pushButton_4->move(730,290);
   // ui->pushButton_5->move(730,360);

    ui->pushButton_2->resize(150,30);
    ui->pushButton_3->resize(150,30);
    ui->pushButton_4->resize(150,30);
    //ui->pushButton_5->resize(150,30);

    QTableWidget *table1=new QTableWidget(this);
    this->table1=table1;
    table1->move(10,120);
    table1->resize(690,350);
    QTableWidget *table2=new QTableWidget(this);
    this->table2=table2;
    table2->move(10,520);
    table2->resize(690,350);
    ui->label_4->move(10,480);
    ui->label_4->resize(120,40);

    //ui->label_5->move(730,500);
    //ui->label_5->resize(150,40);

    ui->lineEdit->move(730,550);
    ui->lineEdit->resize(150,40);


    show_choosed_info();
}

void course_op_scene::on_pushButton_2_clicked()
{

    QSqlQuery query=inquire_all_course_info();
    set_widget_table(query);
}

void course_op_scene::on_pushButton_clicked()
{
    QString choice1=ui->comboBox->currentText().mid(0,3);
    QString choice2=ui->comboBox_2->currentText();
    QString choice3=ui->comboBox_3->currentText();
    QSqlQuery query=inquire_special_course(choice1,choice2,choice3);
    set_widget_table(query);

}

void course_op_scene::set_widget_table(QSqlQuery &query){
    table1->clearContents();
    query.first();
    int row=query.size(),cow=query.record().count() - 1;
    table1->setRowCount(row);
    table1->setColumnCount(cow);
    QStringList header1={"课程编号","课程名","任课老师","学分","校区","所属院系","层次","剩余人数"};
    table1->setHorizontalHeaderLabels(header1);
    for(int i=0; i < row; i++){
        table1->setItem(i,0,new QTableWidgetItem(query.value(0).toString()));
        table1->setItem(i,1,new QTableWidgetItem(query.value(1).toString()));
        table1->setItem(i,2,new QTableWidgetItem(query.value(2).toString()));
        table1->setItem(i,3,new QTableWidgetItem(query.value(3).toString()));
        table1->setItem(i,4,new QTableWidgetItem(query.value(4).toString()));
        table1->setItem(i,5,new QTableWidgetItem(query.value(5).toString()));
        table1->setItem(i,6,new QTableWidgetItem(query.value(7).toString()));
        table1->setItem(i,7,new QTableWidgetItem(query.value(8).toString()));
        query.next();
    }
}

void course_op_scene::on_pushButton_3_clicked()
{

    int row=table1->currentRow();
    if(row != -1){
    QString c_id=table1->item(row,0)->text();
    if(!is_exist_course(c_id)){
    int remain=inquire_remain_num(c_id);//课程剩余数类
    int c_score=inquire_course_score(c_id);//获得该课程学分
    int s_credit=inquire_stu_credit(this->account);//获得学士现在的学分
    if(!remain) QMessageBox::critical(this,"错误","课程人数已满!");
    update_course_num(c_id,remain-1);//修改课程表该课程的剩余人数
    set_widget_table(inquire_all_course_info());//刷新表显示，唉，边学边写的，之前没设计好，这里有点孬了

    s_credit+=c_score;
    if(s_credit > 18) QMessageBox::critical(this,"错误","学分超过18分!");
    else {
        update_stu_credit(this->account,s_credit);
        insert_select_info(account,c_id);
        show_choosed_info();
        };
    }
    else QMessageBox::critical(this,"错误","重复选课!");
    }

}

void course_op_scene::show_choosed_info(){
    QList<QString> list= inquire_stu_select_info(account);
    table2->setRowCount(list.size());
    table2->setColumnCount(8);
    QStringList header2={"课程编号","课程名","任课老师","学分","校区","所属院系","层次"};
    table2->setHorizontalHeaderLabels(header2);
    for(int i=0;i<list.size();i++){
        QSqlQuery *query=inquire_stu_choosed_course(list[i]);
        query->first();
        table2->setItem(i,0,new QTableWidgetItem(query->value(0).toString()));
        table2->setItem(i,1,new QTableWidgetItem(query->value(1).toString()));
        table2->setItem(i,2,new QTableWidgetItem(query->value(2).toString()));
        table2->setItem(i,3,new QTableWidgetItem(query->value(3).toString()));
        table2->setItem(i,4,new QTableWidgetItem(query->value(4).toString()));
        table2->setItem(i,5,new QTableWidgetItem(query->value(5).toString()));
        table2->setItem(i,6,new QTableWidgetItem(query->value(7).toString()));
        table2->setItem(i,7,new QTableWidgetItem(query->value(8).toString()));
    }
    ui->lineEdit->setText(QString::number(inquire_stu_credit(account)));
}

void course_op_scene::on_pushButton_4_clicked()
{
    int row=table2->currentRow();
    if(row != -1){
        QString c_id=table2->item(row,0)->text();
        int c_score=table2->item(row,3)->text().toInt();
        int c_num=inquire_remain_num(c_id);
        int s_credit=inquire_stu_credit(account);
        delete_select_record(c_id);//删除选课表记录
        update_stu_credit(account,s_credit-c_score);//更新学生学分
        update_course_num(c_id,c_num-1);//更新课程数量
        show_choosed_info();//显示

    }
}

