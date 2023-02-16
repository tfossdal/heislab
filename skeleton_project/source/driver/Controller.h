#pragma once
#include "elevio.h"

int doors;
int moving;

int ready(void);
void stopped(void);
void arrived(void);
void openDoor(void);
void initElev(void);
