#include "Start.h"
#include "ui_Start.h"
#include <QPalette>
#include <QPushbutton>
#include <QDebug>
#include <QGraphicsProxyWidget>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QLabel>

Start::Start(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Start),scene(new StartScene(this))
{
    ui->setupUi(this);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setFixedSize(1200,600);
    ui->graphicsView->setAutoFillBackground(true);
    ui->graphicsView->setBackgroundBrush(QBrush(Qt::black));
    QLabel *label = new QLabel();
    QPixmap pixmap(":/images/btcity.png");
    QPixmap newpixmap = pixmap.scaled(800,350,Qt::IgnoreAspectRatio);
    //scene->addPixmap(newpixmap);
    label->setPixmap(newpixmap);
    QGraphicsProxyWidget *bt = scene->addWidget(label);
    bt->setPos(0,-800);
    QPushButton *btn1 = new QPushButton("one player",this);
    QPushButton *btn2 = new QPushButton("two players",this);
    QPushButton *btn3 = new QPushButton("classification",this);
    QPushButton *btn4 = new QPushButton("configuration",this);
    btn1->setFixedSize(this->width()/5,this->height()/12);
    btn1->move(500,360);
    btn2->setFixedSize(this->width()/5,this->height()/12);
    btn2->move(500,420);
    btn3->setFixedSize(this->width()/5,this->height()/12);
    btn3->move(500,480);
    btn4->setFixedSize(this->width()/5,this->height()/12);
    btn4->move(500,540);
    btn1->setStyleSheet("font-size:35px ; background-color:black ; color : white");
    btn2->setStyleSheet("font-size:35px ; background-color:black ; color : white");
    btn3->setStyleSheet("font-size:35px ; background-color:black ; color : white");
    btn4->setStyleSheet("font-size:35px ; background-color:black ; color : white");
    QGraphicsProxyWidget button1 = scene->addWidget(btn1);
    QGraphicsProxyWidget button2 = scene->addWidget(btn2);
    QGraphicsProxyWidget button3 = scene->addWidget(btn3);
    QGraphicsProxyWidget button4 = scene->addWidget(btn4);

    // new a button of one player and two player and set up their pos
    connect(btn1,&QPushButton::clicked,this,&Start::Close);
    connect(btn2,&QPushButton::clicked,this,&Start::Close2);

}

void Start::Close()
{
    // new a choose round window with two player
    c = new ChooseRound(1);
    c->show();
    this->close();
}

void Start::Close2()
{
    // new a choose round window with two player
    c = new ChooseRound(2);
    c->show();
    this->close();
}

Start::~Start()
{
    delete ui;
}
