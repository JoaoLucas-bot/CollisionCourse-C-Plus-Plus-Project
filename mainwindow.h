
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QList>
#include <QRandomGenerator>

#include "trafficlights.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QGraphicsScene *scene;
    QList<QList<double>> possibleStarts;
    QList<QList<double>> trafficLightPosition;
    QList<QList<double>> lanePosition;
    QList<TrafficLights*> trafficLightList;
    int collisionCounter;

    int getCarQuantity();
    void setCarQuantity(int newQuantity);


public slots:
    void increaseCollisionCounter();

private slots:
    void on_carSlider_valueChanged(int value);

    void decreaseCarQuantity(int n);

    void on_stopButton_clicked();

    void on_startButton_clicked();

private:
    int carQuantity = 0;
    Ui::MainWindow *ui;
    void spawnCar();
};

#endif // MAINWINDOW_H
