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
    qDebug() << "new score";
    scene =new Scene(this,score,Round,number);
    qDebug() << "new scene";
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

    // create close the game button
    QPushButton *btnX = new QPushButton("X");
    btnX->setFixedSize(30,30);
    btnX->setStyleSheet("font-size:20px ; background-color:Dark ; color:black");
    QGraphicsProxyWidget *buttonX =scene->addWidget(btnX);
    qDebug() << "buttonX create" ;
    buttonX->setPos(540,-280);
    buttonX->setZValue(5);

    connect(btnX,&QPushButton::clicked,[&](){
        qDebug() << "buttonX";
        QMessageBox msg;
        msg.setText("Do you want to quit?");
        qDebug() << "messagebox create";
        QPushButton *button1 = msg.addButton("quit and save", QMessageBox::YesRole);
        QPushButton *button2 = msg.addButton("quit and dont't save ", QMessageBox::NoRole);
        QPushButton *button3 = msg.addButton("No", QMessageBox::RejectRole);

        QGraphicsProxyWidget *btn1 = scene->addWidget(button1);
        QGraphicsProxyWidget *btn2 = scene->addWidget(button2);
        QGraphicsProxyWidget *btn3 = scene->addWidget(button3);
        connect(button1,&QPushButton::clicked,[&]{
            this->close();
            scene->saveNowData(Round);
            qDebug() << "button1 quit and save";
            scene->clear();
            delete score;
        });
        connect(button2,&QPushButton::clicked,[&]{
            this->close();
            qDebug() << "button2 quit";
            scene->clear();
            delete score;
        });
        connect(button3,&QPushButton::clicked,[&]{
            msg.done(QMessageBox::Close);
            qDebug() << "button3 message box close";
        });
        msg.exec();

    });
    connect(scene,&Scene::gameover,[&]{
        score->setup(Round);
        score->show();
        this->close();
        qDebug() << "gameover";
    });
}

Widget::~Widget()
{
    delete ui;
}



