#ifndef MYCOIN_H
#define MYCOIN_H

#include <QPushButton>

class MyCoin : public QPushButton
{
    Q_OBJECT
public:
    //explicit MyCoin(QWidget *parent = nullptr);

    //btnImg 金币图片路径或银币图片路径
    MyCoin(QString btnImg);

    int posx;
    int posy;
    bool flag;

    //切换金银币的方法
    void changeFlag();

    QTimer * timer1;//金翻银
    QTimer * timer2;//银翻金

    int min=1;
    int max=8;

    //正在执行特效的标识
    bool isAnimation=false;

    //重写 按下
    void mousePressEvent(QMouseEvent *);


    //是否胜利的标识  胜利了就禁用按钮，不允许操作按钮
    bool isWin;


signals:

};

#endif // MYCOIN_H
