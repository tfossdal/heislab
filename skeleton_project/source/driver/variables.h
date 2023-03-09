#pragma once
#include "elevio.h"
#include "Queue.h"

enum doorStatus {doorClosed, doorOpen};

extern enum doorStatus doors;

extern int good2go;

extern int goal;

extern int stop;

extern int floor;

extern MotorDirection direction;

extern node queueHead;

extern int obstruction;

