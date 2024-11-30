#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <QObject>
#include "Door.h"

class Elevator : public QObject {
    Q_OBJECT

public:
    Elevator(int id, QObject* parent = nullptr);
    int getCurrentFloor() const;
    int getTargetFloor() const;
    Door getDoor() const;
    bool isMoving() const;
    bool doorOpened() const;
    void requestFloor(int floor);
    void openDoor();
    void closeDoor();
    void simulateMovement();
    void continueMovement();

signals:
    void floorChanged(int floor);
    void doorStatusChanged(bool isOpen);
    void arrivedAtFloor(int floor);

private:
    int id;
    int currentFloor;
    int targetFloor;
    bool moving;
    Door door;
    bool doorMoving;
};

#endif
