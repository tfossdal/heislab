#include "Controller.h"
#include <stdio.h>
#include <time.h>
#include "variables.h"

int ready(time_t timeStopped, time_t timeNow, int goal)
{
    int good2go = (timeNow > timeStopped + 3) && goal != -2 && doors == doorClosed && direction == 0;
    return good2go; // returner ready, om dørene er lukket, har et mål, dørene lukket og ikke i bevegelse
}

void initElev()
{

    int floor = elevio_floorSensor();
    printf("floor: %d \n", floor);

    for (int i = 0; i < N_FLOORS; i++) // oppdatere lys på knapper
    {
        for (int j = 0; j < N_BUTTONS; j++)
        {
            elevio_buttonLamp(i, j, 0);
        }
    }

    if (floor != 0)
    {
        setMotorDirection(DIRN_DOWN);
    }

    while (floor != 0)
    { // oppdaterer floor til den har nådd bunnen og starter while-løkka i main
        floor = elevio_floorSensor();
        printf("floor: %d \n", floor);
    }

    setMotorDirection(DIRN_STOP);

    return;
}

int arrived()
{ // sjekker om etasje definert og heisen står i ro
    return ((elevio_floorSensor() != -1) && (direction == DIRN_STOP));
}

void openDoor()
{
    elevio_doorOpenLamp(1);
    doors = doorOpen;
    return;
}

void closeDoor()
{
    elevio_doorOpenLamp(0);
    doors = doorClosed;
    return;
}

void setMotorDirection(MotorDirection dirn)
{
    direction = dirn;
    elevio_motorDirection(dirn);
    return;
}

void StopButton()
{ // blir kalt i main når stopknapp er trykket
    if (queueHead == NULL)
    {
    }
    else
    { // litt usikker på pekere, men målet e at doors ska holda styr på om dørå e åpen
        queueHead = clearQueue(queueHead);
    }
    if (elevio_floorSensor() == -1) // viss etasje udef, stopp
    {
        setMotorDirection(DIRN_STOP);
        goal = -2;
    }
    else
    { // viss etasje definert, åpne dører
        openDoor();
    }
    elevio_stopLamp(1);
    stop = 1;
    hasStopped = 1;
    goal = -2;

    for (int i = 0; i < N_FLOORS; i++) // oppdatere lys på knapper
    {
        for (int j = 0; j < N_BUTTONS; j++)
        {
            elevio_buttonLamp(i, j, 0);
        }
    }

    while (stop)
    {
        stop = elevio_stopButton();
    }
    elevio_stopLamp(0);
    return;
}

void stopMidway(void)
{
    setMotorDirection(DIRN_STOP);
    int currentfloor = elevio_floorSensor();
    clearVal(queueHead, currentfloor);
    openDoor();
    for (int i = 0; i < 3; i++)
    {
        elevio_buttonLamp(currentfloor, i, 0);
    }

    return;
}