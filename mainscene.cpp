#include "mainscene.h"
#include "ui_mainscene.h"
#include <QPainter>
#include "mypushbutton.h"
#include <QTimer>
#include <QSoundEffect>

MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScene)
{
    ui->setupUi(this);

    //配置主场景

    //设置窗口大小
    this->setFixedSize(320,588);
    //设置窗口图标
    this->setWindowIcon(QIcon(":/new/prefix1/res/Coin0001.png"));
    //设置窗口标题
    this->setWindowTitle("翻金币");

    //实现菜单栏退出功能
    connect(ui->actionquit,&QAction::triggered,this,&QWidget::close);

    //设置start开始按钮
    MyPushButton * startBtn=new MyPushButton(":/new/prefix1/res/MenuSceneStartButton.png");
    startBtn->setParent(this);
    startBtn->move(this->width()*0.5-startBtn->width()*0.5,this->height()*0.7);

    //创建选择关卡场景
    chooseScene=new ChooseLevelScene;

    //监听chooseScene的返回信号
    connect(chooseScene,&ChooseLevelScene::chooseSceneBack,this,[=](){
        //隐藏chooseScene
        chooseScene->hide();
        //显示mainScene
        this->setGeometry(chooseScene->geometry());//保持场景切换一致性
        this->show();
    });

    //准备开始按钮的音效
    QSoundEffect * startSound = new QSoundEffect(this);
    startSound->setSource(QUrl::fromLocalFile(":/new/prefix1/res/TapButtonSound.wav"));


    //点击开始按钮
    connect(startBtn,&QPushButton::clicked,this,[=](){
        //播放开始音效资源
        startSound->play();

        //做按钮弹起特效
        startBtn->zoomDown();
        startBtn->zoomUp();

        //延时进入到选择关卡场景中,为了使按钮特效更加明显
        QTimer::singleShot(400,this,[=](){
            //隐藏自身，并显示选择关卡场景
            this->hide();
            chooseScene->setGeometry(this->geometry());//保持场景切换一致性
            chooseScene->show();
        });

    });


}

void MainScene::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/new/prefix1/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);//把图片拉伸成屏幕的宽高

    //画背景上的图标
    pix.load(":/new/prefix1/res/Title.png");
    pix=pix.scaled(pix.width()*0.5,pix.height()*0.5);
    painter.drawPixmap(10,30,pix);


}

MainScene::~MainScene()
{
    delete ui;
}

