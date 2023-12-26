#include "Skill.h"
#include <QRandomGenerator>
#include <QTimer>

Skill::Skill()
{
    //grenade, helmet, shovel, star, tank, timer
    int randomNumber = QRandomGenerator::global()->bounded(1, 6);
    if(randomNumber == 1){  //grenade
        setPixmap(QPixmap(":/images/grenade.png").scaled(30, 30, Qt::KeepAspectRatio));
        skillType = "grenade";
    }else if(randomNumber == 2){ //helmet
        setPixmap(QPixmap(":/images/helmet.png").scaled(30, 30, Qt::KeepAspectRatio));
        skillType = "helmet";
    }else if(randomNumber == 3){ //shovel
        setPixmap(QPixmap(":/images/shovel.png").scaled(30, 30, Qt::KeepAspectRatio));
        skillType = "shovel";
    }else if(randomNumber == 4){ //star
        setPixmap(QPixmap(":/images/star.png").scaled(30, 30, Qt::KeepAspectRatio));
        skillType = "star";
    }else if(randomNumber == 5){ //tank
        setPixmap(QPixmap(":/images/tank.png").scaled(30, 30, Qt::KeepAspectRatio));
        skillType = "tank";
    }else if(randomNumber == 6){
        setPixmap(QPixmap(":/images/timer.png").scaled(30, 30, Qt::KeepAspectRatio));
        skillType = "timer";
    }

}
