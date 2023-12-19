#include "PlayerLife.h"
#include "ui_PlayerLife.h"

PlayerLife::PlayerLife(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlayerLife)
{
    life = 3;
    ui->setupUi(this);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setFixedSize(100,600);
    ui->graphicsView->setAutoFillBackground(true);
    ui->graphicsView->setBackgroundBrush(QBrush(Qt::black));
}

PlayerLife::~PlayerLife()
{
    delete ui;
}

int PlayerLife::getlife()
{
    return life;
}

void PlayerLife::setlife(int x)
{
    life = x;
}
