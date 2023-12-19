#include "EnemyLife.h"
#include "ui_EnemyLife.h"
#include <QFont>

EnemyLife::EnemyLife(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EnemyLife)
{
    life = 20 ;
    ui->setupUi(this);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setFixedSize(100,600);
    ui->graphicsView->setAutoFillBackground(true);
    ui->graphicsView->setBackgroundBrush(QBrush(Qt::black));
}

EnemyLife::~EnemyLife()
{
    delete ui;
}

int EnemyLife::getlife()
{
    return life;
}

void EnemyLife::setlife(int x)
{
    life = x;
}

void EnemyLife::time()
{

}
