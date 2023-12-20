#include "Score.h"
#include "ui_Score.h"
#include <QGraphicsTextItem>
#include <QLabel>
#include <QFont>
#include <QGraphicsProxyWidget>
#include <QPushButton>
Score::Score(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Score),scene(new ScoreScene(this))
{
    scene->setSceneRect(-600,-300,1200,600);
    ui->setupUi(this);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setFixedSize(1200,600);
    ui->graphicsView->setAutoFillBackground(true);
    ui->graphicsView->setBackgroundBrush(QBrush(Qt::black));

}

void Score::setup()
{

    int m;
    m = getscore();
    qDebug() << "getscore" << getscore();
    text = new QGraphicsTextItem("Total score : " + QString::number(m));
    QFont font("Arial",32);
    text->setFont(font);
    text->setDefaultTextColor(Qt::white);
    text->setPos(-300,-200);
    text->setZValue(5);
    scene->addItem(text);
    QGraphicsTextItem *text1 = new QGraphicsTextItem("level 1");
    QFont font1("Arial",32);
    text1->setFont(font1);
    text1->setDefaultTextColor(Qt::white);
    text1->setPos(-300,-150);
    text1->setZValue(5);
    scene->addItem(text1);
    QGraphicsTextItem *text2 = new QGraphicsTextItem(QString::number(m) +"  pts   "
                                                     + QString::number(m/100));
    QFont font2("Arial",32);
    text2->setFont(font2);
    text2->setDefaultTextColor(Qt::white);
    text2->setPos(-300,-50);
    text2->setZValue(5);
    scene->addItem(text2);
    QLabel *label = new QLabel();
    QPixmap pixmap(":/images/tank.png");
    QPixmap newpixmap = pixmap.scaled(30,30,Qt::IgnoreAspectRatio);
    //scene->addPixmap(newpixmap);
    label->setPixmap(newpixmap);
    QGraphicsProxyWidget *bt = scene->addWidget(label);
    bt->setPos(-100,-30);

}

int Score::getscore()
{
    return score;
}

void Score::setscore(int x)
{
    score = x;
}

Score::~Score()
{
    delete ui;
}
