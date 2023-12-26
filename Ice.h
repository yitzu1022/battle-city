#ifndef ICE_H
#define ICE_H

#include <QObject>
#include <QGraphicsPixmapItem>

class Ice : public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Ice();
    virtual ~Ice();

signals:

};

#endif // Ice_H
