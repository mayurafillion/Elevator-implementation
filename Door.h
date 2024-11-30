#ifndef DOOR_H
#define DOOR_H

#include <QString>

class Door {
public:

    Door();

    void open();
    void close();

    bool getStatus() const;

private:
    bool isOpened;
};

#endif
