#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    //explicit MyPushButton(QWidget *parent = nullptr);

    //构造函数  参数1 正常显示的图片的路径  参数2 按下按钮后显示的图片的路径
    MyPushButton(QString normalImg,QString pressImg="");

    void zoomDown();//向下跳
    void zoomUp();//向上跳

    //重写鼠标按下释放事件
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);

    //保存用户传入的默认显示路径以及按下后显示的图片路径
    QString normalImgPath;
    QString pressImgPath;

signals:

};

#endif // MYPUSHBUTTON_H
