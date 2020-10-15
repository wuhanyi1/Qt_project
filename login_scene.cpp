#include "login_scene.h"
#include "ui_login_scene.h"
#include "db_connect.h"
#include "stu_info_scene.h"


Login_scene::Login_scene(QWidget *parent) :
    QWidget(parent),my_timer(nullptr),VerificationCode(""),
    ui(new Ui::Login_scene)
{
    ui->setupUi(this);
}

Login_scene::~Login_scene()
{
    delete ui;
}

void Login_scene::set_bg(){
    this->setWindowIcon(QIcon(":/Image/Image/ustc.jpg"));//设置Widget左上角图片
    this->setFixedSize(620,488);//设置登录界面固定大小

    ui->radioButton->setChecked(true);//设置登录选项的默认值，默认是是radioButton

    this->my_timer=new QTimer(this);//在当前对象(Dialog)上创建一个定时器,为主页面时间刷新做的定时器
    QObject::connect(my_timer,SIGNAL(timeout()),this,SLOT(slottimedone()));//定时器的到点信号和我们创建的槽函数链接
    my_timer->start(1000);//开启定时器，1S调用一次slottimedone函数



    VerificationCode=getRamdom();
    m_color=getColors();
}

void Login_scene::slottimedone(){
    m_color=getColors();//更新颜色
    QDateTime *cur_time=new QDateTime;
    *cur_time = QDateTime::currentDateTime();//拷贝赋值函数
    ui->label_5->setText(cur_time->toString());
    repaint();
}

QString Login_scene::getRamdom()//返回一串4个随机字符的字符串
{
    QString ret = "";
    qsrand(QTime::currentTime().msec());
    for(int i=0; i<4; i++)
    {

        int c = (qrand() % 2) ? 'a' : 'A';

        ret += static_cast<QChar>(c + qrand() % 26);
    }
    return ret;
}

Qt::GlobalColor* Login_scene::getColors()
{
    static Qt::GlobalColor colors[4];
    for(int i=0; i<4; i++)
    {
        colors[i] = static_cast<Qt::GlobalColor>(2 + qrand() % 16);
    }
    return colors;
}

void Login_scene::paintEvent(QPaintEvent *){//这个事件是系统自动调的，不是手动调
    QPainter painter(this);//声明painter，向当前窗口画
    QPen m_pen=painter.pen();

    QBrush   brush( Qt::white );//设置画刷为白色
    painter.setBrush(brush); //画家拿起这种属性的画刷

    painter.drawRect( QRect(365,188,80,21)); //


    for(int i=0;i<4;i++){
        m_pen.setColor(m_color[i]);
        painter.setPen(m_pen);
        painter.drawText(QRect(370 + 20 * i,188,80,21),static_cast<QChar>(VerificationCode[i]));//每次画出一个验证码
    }

   // update();
}

void Login_scene::mousePressEvent(QMouseEvent *){
    VerificationCode=getRamdom();
    m_color=getColors();
    repaint();//单击一下，直接调用paint_Event()再画一遍
}

void Login_scene::on_pushButton_clicked()
{
    account=ui->lineEdit->text();//获得输入框的账号文本
    QString passwd=ui->lineEdit_2->text();//获得密码文本
    QString line_edit=ui->lineEdit_3->text();
    bool succ_login=false;
    if(VerificationCode.toLower() != line_edit.toLower()){
        QMessageBox::critical(this,"错误","验证码错误!");//Message对话框输出错误信息
    }
    else {
        succ_login = is_exist_account(account,passwd);
    }
    if(!succ_login)
        VerificationCode=getRamdom();//再次切换验证码
    else {
        if(ui->radioButton->isChecked()){//学生页面登录
            stu_info_scene *stu=new stu_info_scene;

            stu->set_bg(account);
            stu->show();
        }
        this->close();//关闭本界面
    }
}

/*int Login_scene::get_radio_choice(){
    if(radio_check[0]) return 0;
    else if(radio_check[1]) return 1;
    else return 2;
}*/
