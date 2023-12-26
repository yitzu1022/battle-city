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
    Widget(int number=1);
    void Close();
    ~Widget();

private:
    Ui::Widget *ui;
    Scene *scene;
    Score *score;
};
#endif // WIDGET_H
