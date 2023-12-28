#include "ChooseRound.h"
#include "ui_ChooseRound.h"
#include "QLabel"
#include <QGraphicsProxyWidget>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QPalette>
#include <QPushbutton>
#include <QDebug>
#include "Scene.h"

ChooseRound::ChooseRound(int number) :
    ui(new Ui::ChooseRound),scene(new ChooseScene(this))
{
    //this class is used for the game round selection
    playernumber = number;
    // select one or two player
    ui->setupUi(this);
    scene->setSceneRect(-600,-300,1200,600);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setFixedSize(1200,600);
    ui->graphicsView->setAutoFillBackground(true);
    ui->graphicsView->setBackgroundBrush(QBrush(Qt::black));
    QLabel *label = new QLabel();
    QPixmap pixmap(":/images/btcity.png");
    QPixmap newpixmap = pixmap.scaled(800,350,Qt::IgnoreAspectRatio);
    label->setPixmap(newpixmap);
    QGraphicsProxyWidget *bt = scene->addWidget(label);
    bt->setPos(-400,-300);

    // set up the image of battle city on the top of the screen

    QPixmap pixmapR1(":/images/level1.png");
    QPixmap newpixmapR1 = pixmapR1.scaled(100,100,Qt::IgnoreAspectRatio);
    QPushButton *btn = new QPushButton();
    btn->setIcon(newpixmapR1);
    btn->setIconSize(newpixmapR1.size());
    btn->setFixedSize(newpixmapR1.size());
    QGraphicsProxyWidget *btR1 = scene->addWidget(btn);
    btR1->setPos(-400,100);
    connect(btn,&QPushButton::clicked,this,&ChooseRound::OpenRound1);//click 1
    // set up the icon as a button to enter a game(round1)

    QPixmap pixmapR2(":/images/level1.png");
    QPixmap newpixmapR2= pixmapR2.scaled(100,100,Qt::IgnoreAspectRatio);
    QPushButton *btn2 = new QPushButton();
    btn2->setIcon(newpixmapR2);
    btn2->setIconSize(newpixmapR2.size());
    btn2->setFixedSize(newpixmapR2.size());
    QGraphicsProxyWidget *bt2 = scene->addWidget(btn2);
    bt2->setPos(-250,100);
    connect(btn2,&QPushButton::clicked,this,&ChooseRound::OpenRound2);//click 1
    // set up the icon as a button to enter a game(round1)
}



void ChooseRound::OpenRound1()
{
    qDebug() << "open round1";
    w = new Widget(nullptr,1,playernumber); // (parent, round, playernumber)
    w->show();
    //new round1
}

void ChooseRound::OpenRound2()
{
    qDebug() << "open round2";
    w = new Widget(nullptr,2,playernumber);
    w->show();
    // new round2
}


ChooseRound::~ChooseRound()
{
    delete ui;
}
