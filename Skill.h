#ifndef SKILL_H
#define SKILL_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include "Player.h"

class Skill : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Skill();
    std::string getSkillType(){return skillType;}

private:
    std::string skillType;
};

#endif // SKILL_H
