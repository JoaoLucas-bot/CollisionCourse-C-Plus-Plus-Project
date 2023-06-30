#include <QGraphicsItem>
#include <QTimer>
#include "trafficlights.h"

TrafficLights::TrafficLights(QList<double> trafficLightPosition, QGraphicsItem *parent)
    : QObject(), QGraphicsPixmapItem(parent)
{

    setPos(trafficLightPosition[0], trafficLightPosition[1]);
    setPixmap(greenLight);
    lightTimer = new QTimer();
    QObject::connect(lightTimer, SIGNAL(timeout()), this, SLOT(changeLight()));
    lightTimer->start(5000);

}

void TrafficLights::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    changeLight();
}

void TrafficLights::changeLight()
{
    //set new traffic light
    if(currentLight == "green"){
        setPixmap(redLight);
        currentLight = "red";
        emit trafficLightChanged(0);
    }
    else if(currentLight == "red"){
        setPixmap(greenLight);
        currentLight = "green";
        emit trafficLightChanged(1);
    }
}

