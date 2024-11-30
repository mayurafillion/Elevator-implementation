#ifndef SYSTEM_H
#define SYSTEM_H

#include <QObject>
#include "Elevator.h"

class System : public QObject {
    Q_OBJECT

public:
    System(QObject* parent = nullptr);

    void handleFloorRequest(int floor);
    void moveElevator(Elevator* selectedElevator, int floor);
    void handleOverload(int elevatorID);
    void handleBlockage(int elevatorID);
    void handleFireEmergency();
    void handlePowerOutage();
    void handleOpenDoor(int elevatorID);
    void handleCloseButton(int elevatorID);
    void handleHelpButton(int elevatorID);

    void requestElevator(int floor);
    Elevator* getElevator(int id);

signals:
    void elevatorRequested(int floor);

private:
    Elevator* elevators[2];
};

#endif
