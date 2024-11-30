#include "Elevator.h"
#include <QTimer>
#include <QDebug>

Elevator::Elevator(int id, QObject* parent)
    : QObject(parent), id(id), currentFloor(1), targetFloor(1), moving(false), door(Door()), doorMoving(false) {}

int Elevator::getCurrentFloor() const { return currentFloor; }
int Elevator::getTargetFloor() const { return targetFloor; }
Door Elevator::getDoor() const{ return door; };
bool Elevator::isMoving() const { return moving; }
bool Elevator::doorOpened() const { return door.getStatus() == true; }

void Elevator::requestFloor(int floor) {
        targetFloor = floor;
        moving = true;
        emit floorChanged(currentFloor);
        simulateMovement();

}

void Elevator::openDoor() {
    if (isMoving() || doorMoving || doorOpened()){return;}
    doorMoving = true;
    door.open();
    qDebug() << "DING!!!";
    QTimer::singleShot(1000, [this](){
        qDebug() << "Elevator " << id << " doors open at floor " << getCurrentFloor();
        doorMoving = false;
    });
    emit doorStatusChanged(door.getStatus());

}

void Elevator::closeDoor() {
    if (doorMoving == true){return;}
    doorMoving = true;
    door.close();
    QTimer::singleShot(2000, [this](){
        qDebug() << "Elevator " << id << " doors close";
        doorMoving = false;
    });
    emit doorStatusChanged(door.getStatus());
}

void Elevator::simulateMovement() {
    QTimer::singleShot(2000, [this]() {
        if (currentFloor < targetFloor) {
            currentFloor++;
        } else if (currentFloor > targetFloor) {
            currentFloor--;
        } else {
            if (moving == true){
                moving = false;
                openDoor();
                QTimer::singleShot(10000, [this](){closeDoor();});

            }

            emit arrivedAtFloor(currentFloor);
            return;
        }
        emit floorChanged(currentFloor);
        simulateMovement();
    });
}
