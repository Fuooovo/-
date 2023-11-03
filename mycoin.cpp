#include "mycoin.h"
#include <QDebug>
#include <QTimer>

//MyCoin::MyCoin(QWidget *parent)
//    : QPushButton{parent}
//{

//}

MyCoin::MyCoin(QString btnImg){
    QPixmap pix;
    bool ret = pix.load(btnImg);
    if(ret==false){
        QString str=QString("图片%1加载失败").arg(btnImg);
        qDebug()<<str;
    }

    this->setFixedSize(pix.width(),pix.height());
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(),pix.height()));

    //创建两个定时器
    timer1=new QTimer(this);
    timer2=new QTimer(this);

    //监听金币翻转银币转信号，并翻转
    connect(timer1,&QTimer::timeout,this,[=](){
        QPixmap pix;
        QString str=QString(":/new/prefix1/res/Coin000%1").arg(this->min++);
        pix.load(str);

        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));
        //翻完之后重置min
        if(this->min>this->max){
            this->min=1;
            timer1->stop();
            isAnimation=false;//动画结束
        }
    });

    //监听银币翻转金币信号，并翻转
    connect(timer2,&QTimer::timeout,this,[=](){
        QPixmap pix;
        QString str=QString(":/new/prefix1/res/Coin000%8").arg(this->max--);
        pix.load(str);

        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));
        //翻完之后重置max
        if(this->max<this->min){
            this->max=8;
            timer2->stop();
            isAnimation=false;//动画结束
        }
    });
}


void MyCoin::changeFlag(){
    if(this->flag){
        timer1->start(30);
        this->flag=false;
        isAnimation=true;//开始做动画
    }
    else{
        timer2->start(30);
        this->flag=true;
        isAnimation=true;//开始做动画
    }
}


//可以让金币翻转的不那么快，一个动画做完之后再做另一个动画
void MyCoin::mousePressEvent(QMouseEvent * e){
    //播放翻金币动画 和 胜利时 和 点击按钮时 禁用按钮
    if(isAnimation || isWin){
        return;
    }
    else{
        return QPushButton::mousePressEvent(e);
    }

}




