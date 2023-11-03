#ifndef CHOOSELEVELSCENE_H
#define CHOOSELEVELSCENE_H

#include <QMainWindow>
#include "playscene.h"

class ChooseLevelScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooseLevelScene(QWidget *parent = nullptr);

    //重写paintEvent事件 画背景图
    void paintEvent(QPaintEvent *);

    playScene * pScene=nullptr;

signals:
    //自定义信号，告诉mainScene 点击了返回
    void chooseSceneBack();

};

#endif // CHOOSELEVELSCENE_H
