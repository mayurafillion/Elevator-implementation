#include "Passenger.h"

Passenger::Passenger(int startFloor, int destinationFloor)
    : startFloor(startFloor), destinationFloor(destinationFloor) {}

int Passenger::getStartFloor() const { return startFloor; }
int Passenger::getDestinationFloor() const { return destinationFloor; }

void Passenger::setStartFloor(int floor) {startFloor = floor;}
void Passenger::setDestinationFloor(int floor) {destinationFloor = floor;}
