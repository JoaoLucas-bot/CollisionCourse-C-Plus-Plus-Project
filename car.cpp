#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QRandomGenerator>
#include <QList>
#include <QtMultimedia>
#include "car.h"
#include "trafficlightlanes.h"


Car::Car(QList<double> startCoordinates, int carOrientation, QGraphicsItem *parent)
    : QObject(), QGraphicsPixmapItem(parent)
{
    // set random timer
    int randomNumber = (QRandomGenerator::global()->generate() % 28) + 1;
    originalTimer = randomNumber;
    timer = new QTimer(this);

    // retrive car starting position from constructor parameters
    // we will save the start position within this class
    startPosition.append(startCoordinates[0]); //append x coordinate
    startPosition.append(startCoordinates[1]); //append y coordinate

    // send signal to move() everytime timer ends.
    // the faster the timer, the faster the car will move
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(randomNumber);

    // set car picture and starting position

    if(originalTimer == 1){
        setPixmap(QPixmap(":/images/resources/images/f1_black_01_resized.png"));
    }
    else if(originalTimer >= 2 && randomNumber < 10){
        setPixmap(QPixmap(":/images/resources/images/f1_white_01_resized.png"));
    }
    else if(originalTimer >= 10 && randomNumber < 22){
        setPixmap(QPixmap(":/images/resources/images/sport_red_01_resized.png"));
    }
    else if(originalTimer >= 22 && randomNumber <= 28){
        setPixmap(QPixmap(":/images/resources/images/sedan_yellow_01_resized.png"));
    }

    setPos(startPosition[0], startPosition[1]);
    setTransformOriginPoint(pixmap().width()/2, pixmap().height()/2);

    //set car orientation based on start position
    if(carOrientation == 0){
        setRotation(90);
    }
    else if(carOrientation == 1){
        setRotation(270);
    }
    else if(carOrientation == 2){
        setRotation(180);
    }
}

QList<double> Car::getStartPosition()
{
    return startPosition;
}

int Car::getOriginalTimer()
{
    return originalTimer;
}

void Car::setOriginalTimer(int newTimer)
{
    originalTimer = newTimer;
    startTimer();

}

void Car::deleteCar()
{
    //remove car from scene and delete object
    //emit signal to MainWindow.decreaseCarQuantity()
    emit carDeleted(1);
    scene()->removeItem(this);
    delete this;
}

void Car::move()
{
    //register collisions, remove collided objects from scene and delete those same objects
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for(int i = 0; i < colliding_items.size(); i++){
        if(typeid(*(colliding_items[i])) == typeid(Car)){

            //increase collision counter by emitting a signal to MainWindow.increaseCollisionCounter()
            emit collisionHappened();

            QMediaPlayer * music = new QMediaPlayer();
            QAudioOutput *audioOutput = new QAudioOutput();
            music->setAudioOutput(audioOutput);
            music->setSource(QUrl("qrc:/music/resources/music/car_explosion.wav"));
            audioOutput->setVolume(10);
            music->play();

            //remove collided cars from scene and delete them
            scene()->removeItem(colliding_items[i]);
            scene()->removeItem(this);


            //delete objects
            delete colliding_items[i];
            delete this;

            return;
        }
        else if(typeid(*(colliding_items[i])) == typeid(TrafficLightLanes)){

            TrafficLightLanes *trafficLightLane = dynamic_cast<TrafficLightLanes*>(colliding_items.at(i));

            if(trafficLightLane->currentLight == "red"){
                stopTimer();
            }
        }
    }

    //move car based on it's starting position and check if it went beyond scene boundaries
    //if car went over scene boundaries, call Car.deleteCar()
    if(startPosition[0] == scene()->width()/2 - 90 && startPosition[1] == 0){
        //Started north, going south
        setPos(x(), y() + 2);
        if(pos().y() > scene()->height()){
            deleteCar();
            return;
        }
    }
    else if(startPosition[0] == scene()->width()/2 && startPosition[1] == scene()->height()){
        //Started south, going north
        setPos(x(), y() - 2);
        if(pos().y() + pixmap().height() < 0){
            deleteCar();
            return;
        }
    }
    else if(startPosition[0] == scene()->width() && startPosition[1] == scene()->height()/2 - 45){
        //Started east, going west
        setPos(x() - 2, y());
        if(pos().x() + pixmap().width() < 0){
            deleteCar();
            return;
        }
    }
    else if(startPosition[0] == 0 && startPosition[1] == scene()->height()/2 + 10){
        //Started west, going east
        setPos(x() + 2, y());
        if(pos().x() > scene()->width()){
            deleteCar();
            return;
        }
    }

}

void Car::stopTimer()
{
    timer->stop();
};

void Car::startTimer()
{
    timer->start(originalTimer);
}

