#include "Skill.h"
#include "Scene.h"

Skill::Skill()
{
    setPixmap(QPixmap(":/images/heartbeat.png").scaled(30, 30, Qt::KeepAspectRatio));
    skillType = "add_life";
}
