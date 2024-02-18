#include "Ice.h"
#include <QGraphicsPixmapItem>

Ice::Ice()
{
    setPixmap(QPixmap(":/images/Ice.png").scaled(21,21,Qt::KeepAspectRatio));
}

Ice::~Ice()
{

}
