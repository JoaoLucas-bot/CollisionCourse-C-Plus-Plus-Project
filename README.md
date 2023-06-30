# CollisionCourse-C-Project
This project was based on the creation of a graphical application, developed in Qt and C++, for simulation of car traffic at an intersection.

Requirements:
Since the project was developed by 3 elements, the requirement was the existence of two or more tracks
by direction and cars generated in random lanes and speeds. However, it was also developed from the
optional functionality, from the 4 students project, of traffic control with traffic lights.

Functionalities:
Based on the project requirement, which is applied, were also developed
functionalities that complement this requirement. The set of features of the program are as follows:
- Selection of the number of cars to be displayed on the screen;
- Cars randomly generated in one of four possible locations;
- Random speeds for each generated car;
- Traffic control by traffic lights;

Design and Code:
In order to meet the requirements of the program, it was verified that at least two classes would have
to be developed for the objects 'Car' and 'TrafficLight'. During development, it was also
verified the need to create a third class, 'TrafficLightLane', to support the class
‘TrafficLight’. In the end, the structure of our application was as follows:
- Headers:
- car.h
- trafficlights.h
- trafficlightlanes.h
- mainwindow.h
1- CPPs:
- car.ccp
- trafficlights.cpp
- trafficlightlanes.cpp
- mainwindow.cpp
- main.cpp
- UI:
- mainwindow.ui
