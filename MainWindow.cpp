#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QTimer>
#include <QString>
#include  <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , s(new System)
//    , timeElapsed(0)
{
    passenger[0] = new Passenger(0, 0);
    passenger[1] = new Passenger(0, 0);
    passenger[2] = new Passenger(0, 0);
    passenger[3] = new Passenger(0, 0);

    ui->setupUi(this);
    setupTable();
    setupConnections();

//    timerDisplay = new QLCDNumber(this);
//            timerDisplay->setDigitCount(8);  // Format HH:MM:SS
//            timerDisplay->display("00:00:00");

    // Timer for simulating elevator movement
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateElevatorPositions);
    timer->start(10000);
//    connect(timer, &QTimer::timeout, this, &MainWindow::updateTimerDisplay);
//    connect(ui->startButton, &QPushButton::clicked, this, &MainWindow::startTimer);

}

//void MainWindow::updateTimerDisplay() {
//        timeElapsed++;
//        int hours = timeElapsed / 3600;
//        int minutes = (timeElapsed % 3600) / 60;
//        int seconds = timeElapsed % 60;

//        QString timeString = QString("%1:%2:%3")
//            .arg(hours, 2, 10, QChar('0'))
//            .arg(minutes, 2, 10, QChar('0'))
//            .arg(seconds, 2, 10, QChar('0'));

//        timerDisplay->display(timeString);
//    }


MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::setupTable() {
    ui->tableWidget->setRowCount(2);
    ui->tableWidget->setColumnCount(5);
    ui->tableWidget->setHorizontalHeaderLabels({" ", "Position", "Status", "Moving To","Doors"});

    // Initialize table rows
    ui->tableWidget->setItem(0, 0, new QTableWidgetItem("Elevator 1"));
    ui->tableWidget->setItem(1, 0, new QTableWidgetItem("Elevator 2"));
    ui->tableWidget->setItem(0, 1, new QTableWidgetItem("1"));
    ui->tableWidget->setItem(1, 1, new QTableWidgetItem("1"));
    ui->tableWidget->setItem(0, 2, new QTableWidgetItem("Idle"));
    ui->tableWidget->setItem(1, 2, new QTableWidgetItem("Idle"));
    ui->tableWidget->setItem(0, 3, new QTableWidgetItem("N/A"));
    ui->tableWidget->setItem(1, 3, new QTableWidgetItem("N/A"));
    ui->tableWidget->setItem(0, 4, new QTableWidgetItem("Closed"));
    ui->tableWidget->setItem(1, 4, new QTableWidgetItem("Closed"));
}

void MainWindow::setupConnections() {
//    connect(ui->startButton, &QPushButton::clicked, this, [this](){
//        for (int i=0; i<4; i++){
//            QString spinBoxName = "p" + QString::number(i+1) + "sButton";
//            QSpinBox *spinBox = findChild<QSpinBox *>(spinBoxName);
//            int sfloor = spinBox->value();
//            passenger[i]->setStartFloor(sfloor);
//            spinBoxName = "p" + QString::number(i+1) + "dButton";
//            spinBox = findChild<QSpinBox *>(spinBoxName);
//            int dfloor = spinBox->value();
//            passenger[i]->setDestinationFloor(dfloor);
//            if (passenger[i]->getStartFloor() == passenger[i]->getDestinationFloor()){return;}
//            QString requestButtonName = "";
//            if (passenger[i]->getStartFloor() < passenger[i]->getDestinationFloor()){
//                requestButtonName += "upButton_";
//            } else{requestButtonName  += "downButton_";}
//            requestButtonName += passenger[i]->getStartFloor();
//            QPushButton *button = findChild<QPushButton *>(requestButtonName);
//qDebug()  << "Hellooo";
//            button->setChecked(true);
//qDebug()  << "Hellooo";
//        }


//        for (int i=0; i<4; i++){
//            s.handleFloorRequest(passenger[i]->getDestinationFloor());
//        }

//    });
    // Connect buttons to handle request

    connect(ui->upButton_1, &QPushButton::clicked, this, [this](){s.handleFloorRequest(1); });
    connect(ui->downButton_2, &QPushButton::clicked, this, [this](){ s.handleFloorRequest(2); });
    connect(ui->upButton_2, &QPushButton::clicked, this, [this](){ s.handleFloorRequest(2); });
    connect(ui->downButton_3, &QPushButton::clicked, this, [this](){ s.handleFloorRequest(3); });
    connect(ui->upButton_3, &QPushButton::clicked, this, [this](){ s.handleFloorRequest(3); });
    connect(ui->downButton_4, &QPushButton::clicked, this, [this](){ s.handleFloorRequest(4); });
    connect(ui->upButton_4, &QPushButton::clicked, this, [this](){ s.handleFloorRequest(4); });
    connect(ui->downButton_5, &QPushButton::clicked, this, [this](){ s.handleFloorRequest(5); });

    // Connect door buttons
    connect(ui->E1OpenButton, &QPushButton::clicked, this, [this](){ if (s.getElevator(1)->isMoving() == false) {
            s.handleOpenDoor(1);
            updateTable(1, s.getElevator(1)->getCurrentFloor(), s.getElevator(1)->getTargetFloor(), s.getElevator(1)->doorOpened());
        } });
    connect(ui->E1CloseButton, &QPushButton::clicked, this, [this](){
        s.handleCloseButton(1);
        updateTable(1, s.getElevator(1)->getCurrentFloor(), s.getElevator(1)->getTargetFloor(), s.getElevator(1)->doorOpened());
        });
    connect(ui->E2OpenButton, &QPushButton::clicked, this, [this](){ if (s.getElevator(2)->isMoving() == false) {
        s.handleOpenDoor(2);
        updateTable(2, s.getElevator(2)->getCurrentFloor(), s.getElevator(2)->getTargetFloor(), s.getElevator(2)->doorOpened());
        } });
    connect(ui->E2CloseButton, &QPushButton::clicked, this, [this](){
        s.handleCloseButton(2);
        updateTable(2, s.getElevator(2)->getCurrentFloor(), s.getElevator(2)->getTargetFloor(), s.getElevator(2)->doorOpened());
    });

    // Connect floor buttons
    connect(ui->E1F1Button, &QPushButton::clicked, this, [this](){ s.moveElevator(s.getElevator(1), 1); });
    connect(ui->E1F2Button, &QPushButton::clicked, this, [this](){ s.moveElevator(s.getElevator(1), 2); });
    connect(ui->E1F3Button, &QPushButton::clicked, this, [this](){ s.moveElevator(s.getElevator(1), 3); });
    connect(ui->E1F4Button, &QPushButton::clicked, this, [this](){ s.moveElevator(s.getElevator(1), 4); });
    connect(ui->E1F5Button, &QPushButton::clicked, this, [this](){ s.moveElevator(s.getElevator(1), 5); });
    connect(ui->E2F1Button, &QPushButton::clicked, this, [this](){ s.moveElevator(s.getElevator(2), 1); });
    connect(ui->E2F2Button, &QPushButton::clicked, this, [this](){ s.moveElevator(s.getElevator(2), 2); });
    connect(ui->E2F3Button, &QPushButton::clicked, this, [this](){ s.moveElevator(s.getElevator(2), 3); });
    connect(ui->E2F4Button, &QPushButton::clicked, this, [this](){ s.moveElevator(s.getElevator(2), 4); });
    connect(ui->E2F5Button, &QPushButton::clicked, this, [this](){ s.moveElevator(s.getElevator(2), 5); });

    // Connect safety measures buttons
    connect(ui->E1OverloadButton, &QPushButton::clicked, this, [this](){ s.handleOverload(1); });
    connect(ui->E2OverloadButton, &QPushButton::clicked, this, [this](){ s.handleOverload(2); });
    connect(ui->E1DoorBlockButton, &QPushButton::clicked, this, [this](){ s.handleBlockage(1); });
    connect(ui->E2DoorBlockButton, &QPushButton::clicked, this, [this](){ s.handleBlockage(2); });
    connect(ui->FireEmergencyButton, &QPushButton::clicked, this, [this](){s.handleFireEmergency();});
    connect(ui->PowerOutageButton, &QPushButton::clicked, this, [this](){s.handlePowerOutage();});
    connect(ui->E1HelpButton, &QPushButton::clicked, this, [this](){ s.handleHelpButton(1); });
    connect(ui->E2HelpButton, &QPushButton::clicked, this, [this](){ s.handleHelpButton(2); });

    // Connect elevator signals to update the UI table
    connect(s.getElevator(1), &Elevator::floorChanged, this, [this](int floor) {
        updateTable(1, floor, s.getElevator(1)->getTargetFloor(), s.getElevator(1)->doorOpened());
    });
    connect(s.getElevator(2), &Elevator::floorChanged, this, [this](int floor) {
        updateTable(2, floor, s.getElevator(2)->getTargetFloor(), s.getElevator(2)->doorOpened());
    });

    connect(s.getElevator(1), &Elevator::doorStatusChanged, this, [this](int floor) {
        updateTable(1, floor, s.getElevator(1)->getTargetFloor(), s.getElevator(1)->doorOpened());
    });
    connect(s.getElevator(2), &Elevator::doorStatusChanged, this, [this](int floor) {
        updateTable(2, floor, s.getElevator(2)->getTargetFloor(), s.getElevator(2)->doorOpened());
    });
    connect(s.getElevator(1), &Elevator::arrivedAtFloor, this, [this](int floor) {
        updateTable(1, floor, s.getElevator(1)->getTargetFloor(), s.getElevator(1)->doorOpened());

    });
    connect(s.getElevator(2), &Elevator::arrivedAtFloor, this, [this](int floor) {
        updateTable(2, floor, s.getElevator(2)->getTargetFloor(), s.getElevator(2)->doorOpened());
    });

}

void MainWindow::updateElevatorPositions() {
    s.getElevator(1)->simulateMovement();
    s.getElevator(2)->simulateMovement();
}

void MainWindow::updateTable(int elevatorId, int currentFloor, int targetFloor, bool opened) {
    int row = elevatorId - 1;
    ui->tableWidget->setItem(row, 1, new QTableWidgetItem(QString::number(currentFloor)));
    ui->tableWidget->setItem(row, 2, new QTableWidgetItem(targetFloor != currentFloor  ? "Moving" : "Idle"));
    ui->tableWidget->setItem(row, 3, new QTableWidgetItem(targetFloor == currentFloor ? "N/A" : QString::number(targetFloor)));
    ui->tableWidget->setItem(row, 4, new QTableWidgetItem(opened == true ? "Open" : "Closed"));
}
