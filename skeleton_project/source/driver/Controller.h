#pragma once
#include "elevio.h"
#include "Queue.h"

int ready(void);

int stopped(void);

int arrived(void);

void openDoor(void);

void initElev(void);

void setMotorDirection(MotorDirection dirn);

void checkStopButton(node head);
