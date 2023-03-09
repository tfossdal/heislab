#pragma once
#include "elevio.h"
#include "Queue.h"

int ready(time_t timeStopped, time_t timeNow, int goal);

int stopped(void);

int arrived();

void openDoor();

void closeDoor();

void initElev();

void setMotorDirection(MotorDirection dirn);

void StopButton();

