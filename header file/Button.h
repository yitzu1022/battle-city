#ifndef BUTTON_H
#define BUTTON_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QGraphicsItem>
#include <QGraphicsProxyWidget>
#include "Startscene.h"

class Button : public QGraphicsProxyWidget
{
    Q_OBJECT
public:
    Button(QGraphicsItem *parent = nullptr);
};

#endif // BUTTON_H
