#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include "mycoin.h"

class playScene : public QMainWindow
{
    Q_OBJECT
public:
    //explicit playScene(QWidget *parent = nullptr);
    playScene(int levelNum);

    //重写paintEvent事件
    void paintEvent(QPaintEvent *);

    int levelIndex;//记录所选关卡

    int getArray[4][4];//维护每个关卡的具体数据

    MyCoin * coinBtn[4][4];//维护每一个金币按钮

    //是否胜利的标识
    bool isWin;


signals:
    //自定义信号，发送返回chooseScene的信号
    void playSceneBack();

};

#endif // PLAYSCENE_H
