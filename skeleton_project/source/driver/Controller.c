#include "Controller.h"
#include <stdio.h>
#include <time.h>


int isStopped = 0;

int ready(time_t timeStopped, time_t timeNow, int goal, int doors, MotorDirection *currentDir){
    int good2go = (timeNow > timeStopped) && goal != -2 && doors == 0 && *currentDir == 0;
    return good2go;
}

void initElev(MotorDirection *currentDir)
{

    int floor = elevio_floorSensor();
    printf("floor: %d \n",floor);
    
    if (floor != 0){
        setMotorDirection(DIRN_DOWN, currentDir);
    }

    while (floor != 0){
        floor = elevio_floorSensor();
        printf("floor: %d \n",floor);
    }

    setMotorDirection(DIRN_STOP, currentDir);

    return;
}

int stopped(void){
    return isStopped;
}

int arrived(MotorDirection *currentDir){
    return ((elevio_floorSensor() != -1) && (*currentDir == DIRN_STOP));
}

void openDoor(int *doors){
    elevio_doorOpenLamp(1);
    *doors = 1;
    return;
}

void closeDoor(int *doors){
    elevio_doorOpenLamp(0);
    *doors = 0;
    return;
}

void setMotorDirection(MotorDirection dirn, MotorDirection *currentDir){
    *currentDir = dirn;
    elevio_motorDirection(dirn);
    return;
}

void StopButton(node head, MotorDirection *currentDir, int *doors){ //blir kalt i main når stopknapp er trykket
        if (head == NULL){}
        else{                                          // litt usikker på pekere, men målet e at doors ska holda styr på om dørå e åpen
        head = clearQueue(head);
        }
        if (elevio_floorSensor() == -1)
        {
            setMotorDirection(DIRN_STOP, currentDir);
        }else{
            openDoor(doors);
        }
        elevio_stopLamp(1);
        isStopped = 1;
    // Vurdere å legge inn status på stop til å blokkere bestillinger
    elevio_stopLamp(0);
    return;

}