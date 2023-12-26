#ifndef RIVER_H
#define RIVER_H

#include <QObject>
#include <QGraphicsPixmapItem>

class River : public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit River();
    virtual ~River();

signals:

};

#endif // RIVER_H
