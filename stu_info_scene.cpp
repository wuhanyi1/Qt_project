#include "stu_info_scene.h"
#include "ui_stu_info_scene.h"
#include "db_connect.h"

stu_info_scene::stu_info_scene(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::stu_info_scene)
{
    ui->setupUi(this);
}

stu_info_scene::~stu_info_scene()
{
    delete ui;
}

void stu_info_scene::set_bg(QString &account){
    this->account=account;
    this->setWindowIcon(QIcon(":/Image/Image/ustc.jpg"));//设置Widget左上角图片
    this->setFixedSize(920,688);//设置登录界面固定大小

    QPushButton* bt1 = set_button(250,0,"成绩查询");
    QPushButton* bt2 = set_button(450,0,"选课系统");
    QPushButton* bt3 = set_button(650,0,"奖惩查询");
    //connect(bt1,SIGNAL(click()),this,SLOT(grade_inquire()));
    QObject::connect(bt1,SIGNAL(clicked()),this,SLOT(grade_inquire()));
    QObject::connect(bt2,SIGNAL(clicked()),this,SLOT(elective_And_withdraw()));


    QSqlQuery &query=inquire_stu_info(account);
    query.first();
    QString str=query.value(1).toString()+" 同学你好，欢迎您！";


    ui->label->setText(str);
    ui->label->move(20,80);
    ui->label->resize(300,40);

   /* QComboBox *com=new QComboBox(this);
    com->setGeometry(100,100,100,20);
    com->show();*/

   /* QTableWidget* table = new QTableWidget(this); //创建一个表格
    table->setRowCount(3);    //设置行数
    table->setColumnCount(2); //设置列数
    table->setHorizontalHeaderLabels(QStringList()<<"column1"<<"column2"); //设置行头
    table->setItem(0,0,new QTableWidgetItem("item1")); //设置表格内容*/
}

QPushButton* stu_info_scene::set_button(int x, int y, QString words){
    QPushButton *bt=new QPushButton(this);
    bt->move(x,y);
    bt->setText(words);
    bt->setStyleSheet("QPushButton{font-family:'楷体';font-size:32px;color:rgb(0,0,0,255);} \
    QPushButton{background-color:rgb(170,200,50)} QPushButton:hover{background-color:rgb(50, 170, 200)}");
    bt->resize(150,60);
    bt->show();
    return bt;
}

void stu_info_scene::grade_inquire(){
    grade_inquire_TableWidget=new QTableWidget(this);
    grade_inquire_TableWidget->move(20,130);
    grade_inquire_TableWidget->show();
    grade_inquire_TableWidget->setFixedSize(700,500);

    QSqlQuery query=inquire_stu_grade(this->account);//查询成绩
    query.first();
    int row=query.size(),cow=query.record().count();

    grade_inquire_TableWidget->setRowCount(row);//设置行数
    grade_inquire_TableWidget->setColumnCount(cow);//设置列数
    QStringList header={"成绩编号","姓名","课程名","成绩","学号"};
    grade_inquire_TableWidget->setHorizontalHeaderLabels(header);

    for(int i=0 ;i < row; i++) {
        for(int j=0; j<cow ;j++){
            grade_inquire_TableWidget->setItem(i,j,new QTableWidgetItem(query.value(j).toString()));
        }
        query.next();
    }


}

void stu_info_scene::elective_And_withdraw(){

}

void stu_info_scene::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPixmap pix;
    pix.load(":Image/Image/stu_intro.jpg");
    painter.drawPixmap(0,0,200,60,pix);
}
