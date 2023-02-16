#pragma once

int floor; //floorsensor
bool doors;
bool moving;

bool ready(void);
void stopped(void);
void arrived(void);
void openDoor(void);
