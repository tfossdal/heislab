#pragma once
#include "elevio.h"
#include "Queue.h"

int ready(time_t timeStopped, time_t timeNow, int goal, int doors, MotorDirection *currentDir);

int stopped(void);

int arrived(MotorDirection *currentDir);

void openDoor(int *doors);

void closeDoor(int *doors);

void initElev(MotorDirection *currentDir);

void setMotorDirection(MotorDirection dirn, MotorDirection *currentDir);

void StopButton(node head, MotorDirection *currentDir, int *doors);

