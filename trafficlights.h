
#ifndef TRAFFICLIGHTS_H
#define TRAFFICLIGHTS_H


#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <Qt3DInput/QMouseEvent>


class TrafficLights : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit TrafficLights(QList<double> trafficLightPosition, QGraphicsItem *parent = nullptr);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    QTimer* lightTimer;
    const QPixmap redLight = QPixmap(":images/resources/images/traffic_red.png");
    const QPixmap greenLight = QPixmap(":images/resources/images/traffic_green.png");
    QString currentLight = "green";

signals:
    void trafficLightChanged(int);

public slots:
    void changeLight();

};

#endif // TRAFFICLIGHTS_H
