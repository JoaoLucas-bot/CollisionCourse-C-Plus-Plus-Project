#ifndef TRAFFICLIGHTLANES_H
#define TRAFFICLIGHTLANES_H

#include <QObject>
#include <QGraphicsItem>

class TrafficLightLanes : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    explicit TrafficLightLanes(QList<double> lanePosition, QObject *parent = nullptr);
    QString currentLight = "green";

public slots:
    void trafficLightChanged(int currentLight);

};

#endif // TRAFFICLIGHTLANES_H
