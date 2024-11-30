#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLCDNumber>
#include "System.h"
#include "Passenger.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

//public slots:
//    void updateTimerDisplay();

private:
    Ui::MainWindow *ui;
    System s;
    Passenger* passenger[4];
//    int timeElapsed;
//    QLCDNumber *timerDisplay;

    void setupTable();
    void setupConnections();

    void updateElevatorPositions();
    void updateTable(int elevatorId, int currentFloor, int targetFloor, bool opened);
};

#endif
