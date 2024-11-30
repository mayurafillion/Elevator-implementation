#ifndef SENSOR_H
#define SENSOR_H

#include <QObject>

class Sensor : public QObject {
    Q_OBJECT

public:
    Sensor(QObject* parent = nullptr);
    bool isDoorBlocked() const;
    bool isOverloaded() const;
    void setDoorBlocked(bool blocked);
    void setOverloaded(bool overloaded);

signals:
    void doorBlockedStatusChanged(bool blocked);
    void overloadStatusChanged(bool overloaded);

private:
    bool doorBlocked;
    bool overloaded;
};

#endif
