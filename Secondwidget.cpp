#include "Secondwidget.h"
#include "ui_Secondwidget.h"

SecondWidget::SecondWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SecondWidget),scene(new SecondScene())
{
    ui->setupUi(this);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setFixedSize(1200,600);
}

SecondWidget::~SecondWidget()
{
    delete ui;
}
