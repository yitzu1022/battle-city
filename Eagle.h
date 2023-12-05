#ifndef EAGLE_H
#define EAGLE_H

#include <QObject>
#include <QGraphicsPixmapItem>

class Eagle : public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Eagle();
    virtual ~Eagle();

signals:

};

#endif // EAGLE_H
