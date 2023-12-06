#include "widget.h"
#include "ui_widget.h"
#include <QGraphicsPixmapItem>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget),scene(new Scene(this))
{
    ui->setupUi(this);
    scene->setSceneRect(-600,-300,1200,600);  //設置Scene的大小與座標，並要使原點在中間，前兩位為設置左上角的座標(y座標往上為負，往下為正)
    QGraphicsPixmapItem *pixItem=new QGraphicsPixmapItem(QPixmap(":/images/background.jpg"));//放置背景圖
    pixItem->setPos(-600,-300);
    scene->addItem(pixItem);
    //scene->addLine(-600,0,600,0,QPen(Qt::blue));
    //scene->addLine(0,-300,0,300,QPen(Qt::blue));
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setFixedSize(1200,600);
}

Widget::~Widget()
{
    delete ui;
}

