#include "Sensor.h"

Sensor::Sensor(QObject* parent)
    : QObject(parent), doorBlocked(false), overloaded(false) {}

bool Sensor::isDoorBlocked() const { return doorBlocked; }
bool Sensor::isOverloaded() const { return overloaded; }

void Sensor::setDoorBlocked(bool blocked) {
    if (doorBlocked != blocked) {
        doorBlocked = blocked;
        emit doorBlockedStatusChanged(doorBlocked);
    }
}

void Sensor::setOverloaded(bool overloaded) {
    if (this->overloaded != overloaded) {
        this->overloaded = overloaded;
        emit overloadStatusChanged(overloaded);
    }
}
