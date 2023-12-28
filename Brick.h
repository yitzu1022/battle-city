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

    void setWall();
    bool isProtect(){return protect;}

signals:

private:
    bool protect = false;
};

#endif // BRICK_H
