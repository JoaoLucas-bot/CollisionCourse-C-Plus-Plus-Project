//#include <QGraphicsPixmapItem>
#include <QImage>
#include <QtMultimedia>
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "car.h"
#include "trafficlights.h"
#include "trafficlightlanes.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    collisionCounter = 0;
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, 770, 470);


    //possibleStarts' order: North, South, East, West
    possibleStarts = {{scene->width()/2 - 90, 0}, {scene->width()/2, scene->height()}, {scene->width(),scene->height()/2 - 45}, {0, scene->height()/2 + 10}};

    //Traffic lights' positions: North, South, East, West
    trafficLightPosition = {{230, 90} ,{470, 290}, {470, 90} ,{230, 290}};
    lanePosition = {{70, -50} ,{scene->width() / 2 + 10, scene->height() - 120},{scene->width() / 2 + 150, 50} ,{-60, scene->height() / 2 + 10}};


    //Create Traffic Lights
    for(int i = 0; i < 4; i++){
        TrafficLights *trafficLight = new TrafficLights(trafficLightPosition[i]);

        //Change Traffic Light to Red if North or South

        scene->addItem(trafficLight);

        //Add traffic lights to Traffic Light List
        trafficLightList.append(trafficLight);

        //Create traffic light lanes
        TrafficLightLanes *trafficLightLane = new TrafficLightLanes(lanePosition[i]);
        trafficLightLane->setPen(Qt::NoPen);
        scene->addItem(trafficLightLane);

        if(i==0 || i==1){
            trafficLight->currentLight="red";
            trafficLight->setPixmap(QPixmap(":images/resources/images/traffic_red.png"));
            trafficLightLane->currentLight="red";
        }

        QObject::connect(trafficLight, SIGNAL(trafficLightChanged(int)), trafficLightLane, SLOT(trafficLightChanged(int)));
    }

    ui->setupUi(this);
    ui->view->setScene(scene);
    ui->view->setSceneRect(0, 0, 770, 470);
    ui->view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->view->setBackgroundBrush(QBrush(QImage(":/images/resources/images/bg_02_resized.png")));

    spawnCar();


    //play bg music
    QMediaPlayer * music = new QMediaPlayer();
    QAudioOutput *audioOutput = new QAudioOutput();
    music->setAudioOutput(audioOutput);
    music->setSource(QUrl("qrc:/music/resources/music/Initial D-Deja Vu.mp3"));
    music->setLoops(QMediaPlayer::Infinite);
    audioOutput->setVolume(25);
    music->play();



    ui->view->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::getCarQuantity()
{
    return carQuantity;
}

//receives signal from car.collisionHappened()
void MainWindow::increaseCollisionCounter()
{
    //increase UI collision counter and call MainWindow.spawnCar() to add new cars in scene
    ui->collisionLabel->setText("Collisions: " + QString::number(++collisionCounter));

    //Reduce 2 since we deleted both colliding cars
    decreaseCarQuantity(2);
}

void MainWindow::spawnCar()
{
    int carsToSpawn = ui->carQuantityLabel->text().toInt() - getCarQuantity();

    for(int i = 0; i < carsToSpawn; i++){
        // generate random number for starting position
        int randomNumber = QRandomGenerator::global()->generate() % 4;

        Car *car = new Car(possibleStarts[randomNumber], randomNumber);

        carQuantity++;

        //create connectors between Car and MainWindow
        connect(car, SIGNAL(collisionHappened()), this, SLOT(increaseCollisionCounter()));
        connect(car, SIGNAL(carDeleted(int)), this, SLOT(decreaseCarQuantity(int)));

        // add new car to scene
        scene->addItem(car);
    }

}

void MainWindow::decreaseCarQuantity(int n = 1)
{
    carQuantity -= n;
    spawnCar();
}

void MainWindow::on_carSlider_valueChanged(int value)
{
    ui->carQuantityLabel->setText(QString::number(ui->carSlider->value()));
    spawnCar();
}

void MainWindow::on_stopButton_clicked()
{
    foreach (QGraphicsItem *item, scene->items()) {
        if(typeid(*(item)) == typeid(Car)){
            Car *car = dynamic_cast<Car*>(item);

            scene->removeItem(car);
            delete car;

            carQuantity--;
        }
    }
}


void MainWindow::on_startButton_clicked()
{
    spawnCar();
}

