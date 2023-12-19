#ifndef SCORE_H
#define SCORE_H

#include <QWidget>
#include "ScoreScene.h"
namespace Ui {
class Score;
}

class Score : public QWidget
{
    Q_OBJECT

public:
    explicit Score(QWidget *parent = nullptr);
    void setup();
    int getscore();
    void setscore(int x);
    ~Score();

private:
    Ui::Score *ui;
    int score=0;
    ScoreScene *scene;
    QGraphicsTextItem *text;
};

#endif // SCORE_H
