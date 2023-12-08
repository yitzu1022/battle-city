#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>
#include <QObject>



class Player : public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Player(QObject *parent = nullptr);
    qreal rotation() const;
    void setRotation(qreal newRotation);

signals:

private:
<<<<<<< HEAD
    qreal m_rotation;
=======

>>>>>>> ca69e8e2c571cfcdcb483cf913a4679b793fcf82
};

#endif // PLAYER_H
