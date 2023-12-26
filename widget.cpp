#include "widget.h"
#include "ui_widget.h"
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QPushButton>
#include <QGraphicsProxyWidget>
#include <QMessageBox>


Widget::Widget(QWidget *parent, int Round, int number)
    : QWidget(parent)
    , ui(new Ui::Widget), Round(Round)
{
    score = new Score();
    scene =new Scene(this,score,Round,number);

    ui->setupUi(this);
    scene->setSceneRect(-600,-300,1200,600);  //設置Scene的大小與座標，並要使原點在中間，前兩位為設置左上角的座標(y座標往上為負，往下為正)
    QPixmap pixmap(":/images/background.jpg");
    QGraphicsPixmapItem *pixItem=new QGraphicsPixmapItem(pixmap);//放置背景圖
    pixItem->setPos(-600,-300);
    QPainter painter(&pixmap);
    painter.setPen(Qt::black);
    painter.setBrush(Qt::black);
    painter.drawRect(0,0,150,600);
    painter.drawRect(1050,0,150,600);
    pixItem->setPixmap(pixmap);
    scene->addItem(pixItem);
    //scene->addLine(-600,0,600,0,QPen(Qt::blue));
    //scene->addLine(0,-300,0,300,QPen(Qt::blue));
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setFixedSize(1200,600);
    QPushButton *btnX = new QPushButton("X");
    btnX->setFixedSize(30,30);
    btnX->setStyleSheet("font-size:20px ; background-color:Dark ; color:black");
    QGraphicsProxyWidget *buttonX =scene->addWidget(btnX);
    buttonX->setPos(540,-280);
    buttonX->setZValue(5);
    connect(btnX,&QPushButton::clicked,[&](){
        int reply ;
        reply = QMessageBox::question(this,"Confirmation","Do you really want to quit?",
                                      QMessageBox::Yes | QMessageBox::No);
        if (reply==QMessageBox::Yes){
            this->close();
        }else{

        }
    });
    connect(scene,&Scene::gameover,[&]{
        score->setup();
        score->show();
        this->close();
        qDebug() << "gameover";
    });
}

void Widget::Close()
{
    score->setup();
    this->close();
    score->show();
}



Widget::~Widget()
{
    delete ui;
}



