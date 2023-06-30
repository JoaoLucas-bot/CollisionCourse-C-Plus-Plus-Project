
#ifndef CAR_H
#define CAR_H

#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QTimer>
#include <QObject>


class Car : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Car(QList<double> startCoordinates,int carOrientation, QGraphicsItem *parent = nullptr);
    QList<double> getStartPosition();
    int getOriginalTimer();
    void setOriginalTimer(int newTimer);

private:
    int originalTimer;
    QTimer *timer;
    QList<double> startPosition;
    void deleteCar();


public slots:
    void move();
    void stopTimer();
    void startTimer();

signals:
    void collisionHappened();
    void carDeleted(int);

};

#endif // CAR_H
