#include "Brick.h"
#include <QGraphicsPixmapItem>

Brick::Brick()
{
    setPixmap(QPixmap(":/images/brick.png"));
}

Brick::~Brick()
{

}
