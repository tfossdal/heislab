#include "Controller.h"
#include <stdio.h>

void initElev(void){
    int floor = elevio_floorSensor();
    printf("floor: %d \n",floor);
    
    if (floor != 0){
        elevio_motorDirection(DIRN_DOWN);
    }

    while (floor != 0){
        floor = elevio_floorSensor();
        printf("floor: %d \n",floor);
    }

    elevio_motorDirection(DIRN_STOP);
    
    return;
}