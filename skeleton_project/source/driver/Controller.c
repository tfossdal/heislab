#include "Controller.h"
#include <stdio.h>

MotorDirection *currentDir;
int isStopped = 0;

void initElev(void){

    int floor = elevio_floorSensor();
    printf("floor: %d \n",floor);
    
    if (floor != 0){
        setMotorDirection(DIRN_DOWN);
    }

    while (floor != 0){
        floor = elevio_floorSensor();
        printf("floor: %d \n",floor);
    }

    setMotorDirection(DIRN_STOP);
    
    return;
}

int stopped(void){
    return isStopped;
}

int arrived(void){
    return ((elevio_floorSensor() != -1) && (*currentDir == DIRN_STOP));
}

void openDoor(void){
    return;
}

void setMotorDirection(MotorDirection dirn){
    *currentDir = dirn;
    elevio_motorDirection(dirn);
}

void checkStopButton(node head){
    while (elevio_stopButton() == 1)
    {
        clearQueue(head);
        if (elevio_stopButton() == -1)
        {
            setMotorDirection(DIRN_STOP);
        }else{
            openDoor();
        }
        elevio_stopLamp(1);
        isStopped = 1;
    }
    // Vurdere å legge inn status på stop til å blokkere bestillinger
    elevio_stopLamp(0);
}