#ifndef BRICK_H
#define BRICK_H

#include <QObject>
#include <QGraphicsPixmapItem>

class Brick : public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Brick();
    virtual ~Brick();

signals:

};

#endif // BRICK_H
