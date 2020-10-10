#ifndef LOGIN_SCENE_H
#define LOGIN_SCENE_H

#include <QWidget>
#include <QPushButton>
#include <QPainter>
#include <QTimer>
#include <QDateTime>
#include <QDebug>
#include <QMessageBox>
#include <QObject>


namespace Ui {
class Login_scene;
}

class Login_scene : public QWidget
{
    Q_OBJECT

public:
    explicit Login_scene(QWidget *parent = nullptr);
    void set_bg();//登陆页面的背景设置,如时间刷新频率，验证码字符部分生成
    void paintEvent(QPaintEvent *);//重写画画事务，系统自动调
    QString getRamdom();//返回随机字符串的函数
    Qt::GlobalColor* getColors();//返回4个随机颜色数组的第一个元素的指针
    void mousePressEvent(QMouseEvent *);//重写鼠标单击事务
    //int get_radio_choice();


    ~Login_scene();

private:
    QString account;
    QTimer *my_timer;//设置页面时间刷新频率和颜色刷新频率的计时器
    Qt::GlobalColor *m_color;//记录验证码每个字符的颜色
    QString VerificationCode;//记录产生的验证码
    Ui::Login_scene *ui;

    //bool radio_check[3]={false,false,false};


signals:


private slots:
    void slottimedone();
    void on_pushButton_clicked();

};

#endif // LOGIN_SCENE_H
