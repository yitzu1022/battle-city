#include "Brick.h"
#include <QGraphicsPixmapItem>
#include <Qtimer>

Brick::Brick()
{
    setPixmap(QPixmap(":/images/brick.png"));
}

Brick::~Brick()
{

}

void Brick::setWall()
{
    setPixmap(QPixmap(":/images/wall.jpg"));
    protect = true;
    QTimer::singleShot(21000, [=]() {
        setPixmap(QPixmap(":/images/brick.png"));
        protect = false;
    });
}

