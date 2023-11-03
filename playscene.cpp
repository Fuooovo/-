#include "playscene.h"
#include <QMenuBar>
#include <QPainter>
#include "mypushbutton.h"
#include <QTimer>
#include <QLabel>
#include <QPropertyAnimation>
#include <QSoundEffect>
#include "mycoin.h"
#include "dataconfig.h"

//playScene::playScene(QWidget *parent)
//    : QMainWindow{parent}
//{

//}


playScene::playScene(int levelNum){
    this->levelIndex=levelNum;

    //初始化游戏场景
    this->setFixedSize(320,588);
    //设置图标
    this->setWindowIcon(QIcon(":/new/prefix1/res/Coin0001.png"));
    //设置窗口标题
    QString str=QString("第%1关").arg(levelNum);
    this->setWindowTitle(str);


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
    //准备翻金币的音效
    QSoundEffect * flipSound = new QSoundEffect(this);
    flipSound->setSource(QUrl::fromLocalFile(":/new/prefix1/res/ConFlipSound.wav"));
    //准备胜利音效
    QSoundEffect * winSound = new QSoundEffect(this);
    winSound->setSource(QUrl::fromLocalFile(":/new/prefix1/res/LevelWinSound.wav"));

    //点击返回按钮，返回到chooseScene
    connect(backBtn,&QPushButton::clicked,this,[=](){
        //播放返回按钮的音效资源
        backSound->play();

        //向mainScene发送延时返回信号
        QTimer::singleShot(100,this,[=](){
            emit this->playSceneBack();
        });
    });


    //左下角显示当前选择第几关
    QLabel * label=new QLabel(this);
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(20);
    label->setFont(font);
    label->setStyleSheet("color:cyan");
    QString str2=QString("level:%1").arg(levelNum);
    label->setText(str2);
    label->setGeometry(30,this->height()-50,120,50);//前两个参数是位置，后两个参数是大小


    //初始化每个关卡的二维数组
    dataConfig config;
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            this->getArray[i][j]=config.mData[this->levelIndex][i][j];

        }
    }

    //设置胜利图片，暂时将它放在屏幕上方，胜利后落下
    QLabel * winLabel=new QLabel;
    QPixmap tmpPix;
    tmpPix.load(":/new/prefix1/res/LevelCompletedDialogBg.png");
    winLabel->setGeometry(0,0,tmpPix.width(),tmpPix.height());
    winLabel->setPixmap(tmpPix);
    winLabel->setParent(this);
    winLabel->move((this->width()-tmpPix.width())*0.5,-tmpPix.height());


    //绘制金币
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            //绘制金币背景图案
            QLabel * label=new QLabel;
            label->setParent(this);
            QPixmap pix=QPixmap(":/new/prefix1/res/BoardNode(1).png");
            label->setGeometry(0,0,pix.width(),pix.height());
            label->setPixmap(pix);
            label->move(57+i*50,200+j*50);


            //绘制金币图案
            QString str;
            if(this->getArray[i][j]==1) str=QString(":/new/prefix1/res/Coin0001.png");
            else str=QString(":/new/prefix1/res/Coin0008.png");

            MyCoin * coin=new MyCoin(str);
            coin->setParent(this);
            coin->move(59+i*50,204+j*50);

            //给金币属性复制
            coin->posx=i;
            coin->posy=j;
            coin->flag=this->getArray[i][j]==1;//1金 0银


            //将金币放入二维数组中，以便于后期的维护
            this->coinBtn[i][j]=coin;


            //点击金币，翻转金币
            connect(coin,&QPushButton::clicked,this,[=](){
                //播放翻金币音效
                flipSound->play();

                //点击按钮设为胜利状态，禁用按钮，防止手快的玩家结束游戏后仍能翻金币
                for(int i=0;i<4;i++){
                    for(int j=0;j<4;j++){
                        this->coinBtn[i][j]->isWin=true;
                    }
                }


                coin->changeFlag();
                this->getArray[i][j]=this->getArray[i][j]==0?1:0;


                //翻转周围金币,延时翻转
                QTimer::singleShot(300,this,[=](){
                    //翻右侧金币
                    if(coin->posx+1<=3){
                        this->coinBtn[coin->posx+1][coin->posy]->changeFlag();
                        this->getArray[coin->posx+1][coin->posy]=this->getArray[coin->posx+1][coin->posy]==0?1:0;
                    }
                    //翻左侧金币
                    if(coin->posx-1>=0){
                        this->coinBtn[coin->posx-1][coin->posy]->changeFlag();
                        this->getArray[coin->posx-1][coin->posy]=this->getArray[coin->posx-1][coin->posy]==0?1:0;
                    }
                    //翻上侧金币
                    if(coin->posy-1>=0){
                        this->coinBtn[coin->posx][coin->posy-1]->changeFlag();
                        this->getArray[coin->posx][coin->posy-1]=this->getArray[coin->posx][coin->posy-1]==0?1:0;
                    }
                    //翻下侧金币
                    if(coin->posy+1<=3){
                        this->coinBtn[coin->posx][coin->posy+1]->changeFlag();
                        this->getArray[coin->posx][coin->posy+1]=this->getArray[coin->posx][coin->posy+1]==0?1:0;
                    }


                    //翻完金币后恢复按钮状态
                    for(int i=0;i<4;i++){
                        for(int j=0;j<4;j++){
                            this->coinBtn[i][j]->isWin=false;
                        }
                    }


                    //翻完一次金币后判断游戏是否胜利
                    this->isWin=true;
                    for(int i=0;i<4;i++){
                        for(int j=0;j<4;j++){
                            if(this->coinBtn[i][j]->flag==false){
                                this->isWin=false;
                                break;
                            }
                        }
                    }
                    if(this->isWin==true){
                        //将所有按钮的isWin改为true
                        for(int i=0;i<4;i++){
                            for(int j=0;j<4;j++){
                                coinBtn[i][j]->isWin=true;
                            }
                        }
                        //播放胜利音效资源
                        winSound->play();

                        //把胜利图片落下来
                        QPropertyAnimation * animation=new QPropertyAnimation(winLabel,"geometry");
                        animation->setDuration(1000);
                        animation->setStartValue(QRect(winLabel->x(),winLabel->y(),winLabel->width(),winLabel->height()));
                        animation->setEndValue(QRect(winLabel->x(),winLabel->y()+144,winLabel->width(),winLabel->height()));
                        animation->setEasingCurve(QEasingCurve::OutBounce);
                        animation->start();
                    }


                });


            });

        }
    }




}



void playScene::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/new/prefix1/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);//把图片拉伸成屏幕的宽高

    //画背景上的图标
    pix.load(":/new/prefix1/res/Title.png");
    pix=pix.scaled(pix.width()*0.5,pix.height()*0.5);
    painter.drawPixmap(10,30,pix);
}
