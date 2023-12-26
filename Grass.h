#ifndef GRASS_H
#define GRASS_H

#include <QObject>
#include <QGraphicsPixmapItem>

class Grass : public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Grass();
    virtual ~Grass();

signals:

};

#endif // GRASS_H
