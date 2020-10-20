#ifndef COURSE_OP_SCENE_H
#define COURSE_OP_SCENE_H

#include <QWidget>
#include <QString>
#include <QIcon>
#include <QComboBox>
#include <QPushButton>
#include <QTableWidget>
#include <QSqlQuery>
#include <QMessageBox>

namespace Ui {
class course_op_scene;
}

class course_op_scene : public QWidget
{
    Q_OBJECT

public:
    explicit course_op_scene(QWidget *parent = nullptr);
    void set_bg(QString &account);
    void set_widget_table(QSqlQuery &query);
    void show_choosed_info();//显示学生已选课程信息
    ~course_op_scene();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    QTableWidget *table1;
    QTableWidget *table2;
    QString account;
    Ui::course_op_scene *ui;
};

#endif // COURSE_OP_SCENE_H
