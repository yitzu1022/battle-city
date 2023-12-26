#include "Score.h"
#include "ui_Score.h"
#include <QGraphicsTextItem>
#include <QLabel>
#include <QFont>
#include <QGraphicsProxyWidget>
#include <QPushButton>
#include <QTextStream>

Score::Score(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Score),scene(new ScoreScene(this))
{
    scene->setSceneRect(-600,-300,1200,600);
    ui->setupUi(this);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setFixedSize(1200,600);
    ui->graphicsView->setAutoFillBackground(true);
    ui->graphicsView->setBackgroundBrush(QBrush(Qt::black));

}

void Score::setup()
{
    int m;
    m = getscore();
    qDebug() << "getscore" << getscore();
    QGraphicsTextItem *highestScore = new QGraphicsTextItem("Highest score:" + QString::number(highest));
    QFont fonthighest("Arial",32);
    highestScore->setFont(fonthighest);
    highestScore->setDefaultTextColor(Qt::white);
    highestScore->setPos(-300,-300);
    highestScore->setZValue(5);
    scene->addItem(highestScore);
    text = new QGraphicsTextItem("Total score : " + QString::number(m));
    QFont font("Arial",32);
    text->setFont(font);
    text->setDefaultTextColor(Qt::white);
    text->setPos(-300,-200);
    text->setZValue(5);
    scene->addItem(text);
    QGraphicsTextItem *text1 = new QGraphicsTextItem("level 1");
    QFont font1("Arial",32);
    text1->setFont(font1);
    text1->setDefaultTextColor(Qt::white);
    text1->setPos(-300,-150);
    text1->setZValue(5);
    scene->addItem(text1);
    QGraphicsTextItem *text2 = new QGraphicsTextItem(QString::number(m) +"  pts   "
                                                     + QString::number(m/100));
    QFont font2("Arial",32);
    text2->setFont(font2);
    text2->setDefaultTextColor(Qt::white);
    text2->setPos(-300,-50);
    text2->setZValue(5);
    scene->addItem(text2);
    //score

    QLabel *label = new QLabel();
    QPixmap pixmap(":/images/player.png");
    QPixmap newpixmap = pixmap.scaled(50,50,Qt::IgnoreAspectRatio);
    label->setPixmap(newpixmap);
    QGraphicsProxyWidget *bt = scene->addWidget(label);
    bt->setPos(-100,-30);

    //player image

    QPixmap pixmap1(":/images/retry.png");
    QPixmap newpixmap1 = pixmap1.scaled(50,50,Qt::IgnoreAspectRatio);
    QPushButton *btn = new QPushButton();
    btn->setIcon(newpixmap1);
    btn->setIconSize(newpixmap1.size());
    btn->setFixedSize(newpixmap1.size());
    QGraphicsProxyWidget *bt1 = scene->addWidget(btn);
    bt1->setPos(500,200);
    connect(btn,&QPushButton::clicked,[&]{
        this->close();
    });

}

int Score::getscore()
{
    return score;
}

void Score::setscore(int x)
{
    QFile fileHighest(filehighest);
    score = x;
    QString line;
    if(fileHighest.exists()){
        if (fileHighest.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&fileHighest);

            while (!in.atEnd()) {
                line = in.readLine();
                qDebug() <<"current highest score : " << line; // Output the content of the file line by line
            }
            highest = line.toInt();
            fileHighest.close();
        } else {
            qDebug() << "Failed to open the file for reading.";
        }
    }

    if( x>= highest){
        highest = x ;
        QString highestScore = QString::number(highest);
        if (fileHighest.open(QIODevice::ReadWrite | QIODevice::Text)) {
            QTextStream stream(&fileHighest);
            QString content = stream.readAll();

            // Overlay the new value at the specified position
            content.replace(0, highestScore.length(), highestScore);

            // Move the file pointer to the beginning and truncate the file
            fileHighest.resize(0);
            fileHighest.seek(0);

            // Write the updated content back to the file
            stream << content;
            fileHighest.close();

            qDebug() << "Value overlayed successfully.";
        } else {
            qDebug() << "Failed to open the file.";
        }
    }


}

Score::~Score()
{
    delete ui;
}
