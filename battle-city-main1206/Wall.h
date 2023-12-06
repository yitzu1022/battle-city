#ifndef WALL_H
#define WALL_H

#include <QObject>
#include <QGraphicsPixmapItem>

class Wall :public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Wall();
    virtual ~Wall();

signals:

};

#endif // WALL_H
