#include "Door.h"

Door::Door() : isOpened(false) {}

void Door::open() {
    isOpened = true;
}

void Door::close() {
    isOpened = false;
}

bool Door::getStatus() const {
    return isOpened;
}
