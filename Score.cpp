#include "Score.h"
#include "ui_Score.h"
#include <QGraphicsTextItem>
#include <QLabel>
#include <QFont>
#include <QGraphicsProxyWidget>
#include <QPushButton>
#include <QTextStream>
#include <QDir>
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

void Score::setup(int Round)
{
    //this class is used to display the score and highest score in history
    int m;
    m = getscore();
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
    //display the current score

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
    connect(btn,&QPushButton::clicked,[=]{
        this->close();
    });

    // create a button to retry the game
    QString desktopPath = QDir::homePath() + "/Desktop/";
    QFile fileHighestR1(desktopPath+"highestRound1.txt");
    QFile fileHighestR2(desktopPath+"highestRound2.txt");
    QString line;
    if(Round==1){
        if (fileHighestR1.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&fileHighestR1);

            while (!in.atEnd()) {
                line = in.readLine();
                qDebug() <<"current highest score : " << line; // Output the content of the file line by line
            }
            highestR1 = line.toInt();
            fileHighestR1.close();
        } else {
            qDebug() << "Failed to open the file for reading.";
        }
        if( score >= highestR1){
            highestR1 = score ;
            QString highestScore = QString::number(highestR1);
            if (fileHighestR1.open(QIODevice::ReadWrite | QIODevice::Text)) {
                QTextStream stream(&fileHighestR1);
                QString content = stream.readAll();

                // Overlay the new value at the specified position
                content.replace(0, highestScore.length(), highestScore);

                // Move the file pointer to the beginning and truncate the file
                fileHighestR1.resize(0);
                fileHighestR1.seek(0);

                // Write the updated content back to the file
                stream << content;
                fileHighestR1.close();

                qDebug() << "Value overlayed successfully.";
            } else {
                qDebug() << "Failed to open the file.";
            }
        }
    }else{
        if (fileHighestR2.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&fileHighestR2);

            while (!in.atEnd()) {
                line = in.readLine();
                qDebug() <<"current highest score : " << line; // Output the content of the file line by line
            }
            highestR2 = line.toInt();
            fileHighestR2.close();
        } else {
            qDebug() << "Failed to open the file for reading.";
        }
        if( score >= highestR2){
            highestR2 = score ;
            QString highestScore = QString::number(highestR2);
            if (fileHighestR2.open(QIODevice::ReadWrite | QIODevice::Text)) {
                QTextStream stream(&fileHighestR2);
                QString content = stream.readAll();

                // Overlay the new value at the specified position
                content.replace(0, highestScore.length(), highestScore);

                // Move the file pointer to the beginning and truncate the file
                fileHighestR2.resize(0);
                fileHighestR2.seek(0);

                // Write the updated content back to the file
                stream << content;
                fileHighestR2.close();

                qDebug() << "Value overlayed successfully.";
            } else {
                qDebug() << "Failed to open the file.";
            }
        }
    }
    QGraphicsTextItem *highestScore;
    qDebug() << "getscore" << getscore();
    //determine the current round
    if(Round==1){
        highestScore = new QGraphicsTextItem("Highest score:" + QString::number(highestR1));
    }else{
        highestScore = new QGraphicsTextItem("Highest score:" + QString::number(highestR2));
    }

    QFont fonthighest("Arial",32);
    highestScore->setFont(fonthighest);
    highestScore->setDefaultTextColor(Qt::white);
    highestScore->setPos(-300,-300);
    highestScore->setZValue(5);
    scene->addItem(highestScore);
    //display the highest score


}

int Score::getscore()
{
    return score;
}

void Score::setscore(int x)
{
    score = x;
}

Score::~Score()
{
    delete ui;
}
