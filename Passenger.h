#ifndef PASSENGER_H
#define PASSENGER_H

#include <QObject>

class Passenger : public QObject {
    Q_OBJECT

public:
    Passenger(int startFloor, int destinationFloor);
    int getStartFloor() const;
    int getDestinationFloor() const;
    void setStartFloor(int floor);
    void setDestinationFloor(int floor);

private:
    int startFloor;
    int destinationFloor;
};

#endif
