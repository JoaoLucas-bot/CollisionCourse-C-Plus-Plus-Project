#include "trafficlightlanes.h"
#include "car.h"

TrafficLightLanes::TrafficLightLanes(QList<double> lanePosition, QObject *parent)
    : QObject{parent}
{
    setRect(0, 0, 300, 180);
    setPos(lanePosition[0], lanePosition[1]);
}

void TrafficLightLanes::trafficLightChanged(int trafficLight)
{
    //check which cars are on traffic light lane
    QList<QGraphicsItem *> colliding_items = collidingItems();

    if(trafficLight == 1){
        currentLight = "green";
    }
    else if(trafficLight == 0){
        currentLight = "red";
    }

    for(int i = 0; i < colliding_items.size(); i++){
        if(typeid(*(colliding_items[i])) == typeid(Car) && currentLight == "red"){

            Car *car = dynamic_cast<Car*>(colliding_items.at(i));
            car->stopTimer();

        }
        else if(typeid(*(colliding_items[i])) == typeid(Car) && currentLight == "green"){

            Car *car = dynamic_cast<Car*>(colliding_items.at(i));
            car->startTimer();

        }
    }
}
