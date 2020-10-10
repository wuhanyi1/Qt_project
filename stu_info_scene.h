#ifndef STU_INFO_SCENE_H
#define STU_INFO_SCENE_H

#include <QWidget>
#include <QPushButton>
#include <QPainter>
#include <QTimer>
#include <QDateTime>
#include <QDebug>
#include <QMessageBox>
#include <QTableWidget>
#include <QComboBox>
#include <QLabel>
#include <QStringList>
#include <QTableWidgetItem>

namespace Ui {
class stu_info_scene;
}

class stu_info_scene : public QWidget
{
    Q_OBJECT

public:
    explicit stu_info_scene(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);
    void set_bg(QString &account);
    QPushButton* set_button(int x,int y,QString words);

    ~stu_info_scene();

private:
    QString account;
    Ui::stu_info_scene *ui;
    QTableWidget *grade_inquire_TableWidget;
    QTableWidget *lesson_choice_TableWidget;
    QTableWidget *punish_award_TableWidget;

private slots:
    void grade_inquire();
    void elective_And_withdraw();
};

#endif // STU_INFO_SCENE_H
