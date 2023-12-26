#include "Secondwidget.h"
#include "ui_Secondwidget.h"
#include <QGraphicsPixmapItem>

SecondWidget::SecondWidget(int number) :
    ui(new Ui::SecondWidget),scene(new SecondScene())
{
    ui->setupUi(this);
    scene->setSceneRect(-600,-300,1200,600);
    QGraphicsPixmapItem *pixItem=new QGraphicsPixmapItem(QPixmap(":/images/background.jpg"));
    pixItem->setPos(-600,-300);
    scene->addItem(pixItem);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setFixedSize(1200,600);

}

SecondWidget::~SecondWidget()
{
    delete ui;
}
