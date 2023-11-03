#include "chooselevelscene.h"
#include <QMenuBar>
#include <QPainter>
#include "mypushbutton.h"
#include <QTimer>
#include <QLabel>
#include <QSoundEffect>

ChooseLevelScene::ChooseLevelScene(QWidget *parent)
    : QMainWindow{parent}
{
    //配置关卡场景
    this->setFixedSize(320,588);

    //设置窗口图标
    this->setWindowIcon(QIcon(":/new/prefix1/res/Coin0001.png"));
    //设置窗口标题
    this->setWindowTitle("选择关卡");

    //设置菜单栏
    QMenuBar * bar=menuBar();
    this->setMenuBar(bar);
    //创建开始菜单
    QMenu * startMenu = bar->addMenu("开始");
    //创建退出菜单项
    QAction * quitAction=startMenu->addAction("退出");

    //点击退出，关闭该窗口
    connect(quitAction,&QAction::triggered,this,&QWidget::close);


    //设置返回按钮
    MyPushButton * backBtn=new MyPushButton(":/new/prefix1/res/BackButton.png",":/new/prefix1/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width()-backBtn->width(),this->height()-backBtn->height());

    //准备返回按钮的音效
    QSoundEffect * backSound = new QSoundEffect(this);
    backSound->setSource(QUrl::fromLocalFile(":/new/prefix1/res/BackButtonSound.wav"));


    //点击返回按钮，返回到mainScene
    connect(backBtn,&QPushButton::clicked,this,[=](){
        //播放返回按钮的音效资源
        backSound->play();

        //向mainScene发送延时返回信号
        QTimer::singleShot(100,this,[=](){
            emit this->chooseSceneBack();
        });
    });

    //准备选择关卡按钮的音效
    QSoundEffect * chooseSound = new QSoundEffect(this);
    chooseSound->setSource(QUrl::fromLocalFile(":/new/prefix1/res/TapButtonSound.wav"));


    //创建选择关卡的按钮
    for(int i=0;i<20;i++){
        MyPushButton * levelBtn=new MyPushButton(":/new/prefix1/res/LevelIcon.png");
        levelBtn->setParent(this);
        levelBtn->move(25+i%4*70,130+i/4*70);


        //监听每个按钮的点击事件
        connect(levelBtn,&QPushButton::clicked,this,[=](){
            //播放选择关卡按钮音效资源
            chooseSound->play();

            //跳转到对应关卡
            this->hide();
            pScene=new playScene(i+1);
            pScene->setGeometry(this->geometry());//保持切换场景的一致性
            pScene->show();


            //监听playScene的返回信号
            connect(pScene,&playScene::playSceneBack,this,[=](){
                //显示chooseScene
                this->setGeometry(pScene->geometry());//保持切换场景的一致性
                this->show();
                //释放playScene
                delete pScene;
                pScene=nullptr;
            });

        });

        //设置按钮上的文字
        QLabel * label=new QLabel(this);
        label->setFixedSize(levelBtn->width(),levelBtn->height());
        label->move(25+i%4*70,130+i/4*70);
        label->setText(QString::number(i+1));
        //设置文字水平居中和垂直居中
        label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

        //设置鼠标穿透，否则点到的是label 而不是button
        label->setAttribute(Qt::WA_TransparentForMouseEvents);
    }

}

void ChooseLevelScene::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/new/prefix1/res/OtherSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);//把图片拉伸成屏幕的宽高

    //画背景上的图标
    pix.load(":/new/prefix1/res/Title.png");
    painter.drawPixmap((this->width()-pix.width())*0.5,30,pix.width(),pix.height(),pix);

}



