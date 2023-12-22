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
    void setnumber(int n);
    int getnumber();
signals:

private:
    qreal m_rotation;
    int life=3;
    int number; //註明是player1還是2
};

#endif // PLAYER_H
