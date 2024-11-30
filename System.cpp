#include "System.h"
#include <QDebug>
#include <QTimer>

System::System(QObject* parent) : QObject(parent) {
    elevators[0] = new Elevator(1, this);
    elevators[1] = new Elevator(2, this);
}

void System::requestElevator(int floor) {
    emit elevatorRequested(floor);
    elevators[0]->requestFloor(floor);
}

Elevator* System::getElevator(int id) {
    return elevators[id - 1];
}


void System::handleFloorRequest(int floor) {
    // Determine which elevator should respond
    int distanceFrom1 = abs(floor - getElevator(1)->getCurrentFloor());
    int distanceFrom2 = abs(floor - getElevator(2)->getCurrentFloor());

    if (distanceFrom1 < distanceFrom2 || (distanceFrom1 == distanceFrom2 && !getElevator(1)->isMoving())){moveElevator(getElevator(1), floor);}
    else {moveElevator(getElevator(2), floor);}

}

void System::moveElevator(Elevator* selectedElevator, int floor){
    if (selectedElevator->doorOpened()){selectedElevator->closeDoor();}
    selectedElevator->requestFloor(floor);
}


void System::handleOverload(int elevatorID){
    getElevator(elevatorID)->openDoor();
    qDebug() << "Elevator " << elevatorID << ": Overload.";
    if (elevatorID == 1 ){
        QTimer::singleShot(10000, [this](){getElevator(1)->closeDoor();});
    }
    else {QTimer::singleShot(10000, [this](){getElevator(2)->closeDoor();});
   }
}
void System::handleBlockage(int elevatorID){
    getElevator(elevatorID)->openDoor();
    qDebug() << "Elevator " << elevatorID << ": Something is preventing the door from  closing.";
    if (elevatorID == 1 ){
        QTimer::singleShot(10000, [this](){getElevator(1)->closeDoor();});
    }
    else {QTimer::singleShot(10000, [this](){getElevator(2)->closeDoor();});
   }
}
void System::handleFireEmergency(){
    for (int  i=0; i<2; i++){
        moveElevator(getElevator(i+1),1);
        qDebug() << "Elevator " << i+1 << ": Fire emergency message!!!";
        getElevator(i+1)->openDoor();
    }
}
void System::handlePowerOutage(){
    for (int  i=0; i<2; i++){
        moveElevator(getElevator(i+1),1);
        qDebug() << "Elevator " << i+1 << ": Power outage emergency message!!!";
        getElevator(i+1)->openDoor();
    }
}

void System::handleOpenDoor(int elevatorID){
    getElevator(elevatorID)->openDoor();
    if (elevatorID == 1 ){
        QTimer::singleShot(10000, [this](){getElevator(1)->closeDoor();});
    }
    else {QTimer::singleShot(10000, [this](){getElevator(2)->closeDoor();});
   }
}
void System::handleCloseButton(int elevatorID){ getElevator(elevatorID)->closeDoor(); }

void System::handleHelpButton(int elevatorID){
    qDebug()  << "Elevator " << elevatorID << ": Connecting to building safety service";}
