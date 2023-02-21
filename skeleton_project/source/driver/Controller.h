#pragma once
#include "elevio.h"
#include "Queue.h"

int ready(void);

int stopped(void);

int arrived(MotorDirection *currentDir);

void openDoor(void);

void initElev(MotorDirection *currentDir);

void setMotorDirection(MotorDirection dirn, MotorDirection *currentDir);

void checkStopButton(node head, MotorDirection *currentDir);
