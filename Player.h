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
    void setlife();
    int getlife();
signals:

private:
    qreal m_rotation;
    int life=3;
};

#endif // PLAYER_H
