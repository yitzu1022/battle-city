#ifndef WIDGET_H
#define WIDGET_H

#include "Scene.h"
#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include "Score.h"
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr, int Round=0, int number=1);
    ~Widget();

private:
    Ui::Widget *ui;
    Scene *scene;
    Score *score;
    int Round;
};
#endif // WIDGET_H
