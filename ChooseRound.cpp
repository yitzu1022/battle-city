#include "ChooseRound.h"
#include "ui_ChooseRound.h"
#include "QLabel"
#include <QGraphicsProxyWidget>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QPalette>
#include <QPushbutton>
#include <QDebug>

ChooseRound::ChooseRound(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChooseRound),scene(new ChooseScene(this))
{
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
    //scene->addPixmap(newpixmap);
    label->setPixmap(newpixmap);
    QGraphicsProxyWidget *bt = scene->addWidget(label);
    bt->setPos(-400,-300);

    //QLabel *label1 = new QLabel();
    QPixmap pixmap1(":/images/level1.png");
    QPixmap newpixmap1 = pixmap1.scaled(100,100,Qt::IgnoreAspectRatio);
    //scene->addPixmap(newpixmap);
    //label1->setPixmap(newpixmap1);
    QPushButton *btn = new QPushButton();
    btn->setIcon(newpixmap1);
    btn->setIconSize(newpixmap1.size());
    btn->setFixedSize(newpixmap1.size());
    QGraphicsProxyWidget *bt1 = scene->addWidget(btn);
    bt1->setPos(-400,100);
    connect(btn,&QPushButton::clicked,this,&ChooseRound::Close);
    w = new Widget();
}



void ChooseRound::Close()
{
    this->close();
    w->show();
}


ChooseRound::~ChooseRound()
{
    delete ui;
}
