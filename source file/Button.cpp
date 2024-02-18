#include "Button.h"
#include "Startscene.h"
Button::Button(QGraphicsItem *parent):
    QGraphicsProxyWidget(parent)
{
    QPushButton *btn1 = new QPushButton("one player");
    setWidget(btn1);
    QPushButton *btn2 = new QPushButton("two players");
    setWidget(btn2);
}
