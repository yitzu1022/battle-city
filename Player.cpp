#include "Player.h"

Player::Player(QObject *parent)
    : QObject{parent}
{
    setPixmap(QPixmap(":/images/tank.png"));


}

qreal Player::rotation() const
{
    return m_rotation;
}

//轉動player的方向
void Player::setRotation(qreal newRotation)
{
    m_rotation = newRotation;
    //以中心點進行旋轉
    QPointF c =boundingRect().center(); //取得圖片中心點
    QTransform t; //用Qtransform此object來進行旋轉
    t.translate(c.x(),c.y());
    t.rotate(newRotation); //rotate到這個newRotation角度
    t.translate(-c.x(),-c.y());
    setTransform(t); //apply 此 transformation
}

void Player::setlife()
{
    life--;
}

int Player::getlife()
{
    return life;
}

void Player::setnumber(int n)
{
    number=n;
}

int Player::getnumber()
{
    return number;
}


