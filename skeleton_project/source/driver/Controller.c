#include "Controller.h"
#include <stdio.h>

void initElev(void){
    int floor = elevio_floorSensor();
    printf("floor: %d \n",floor);
    printf("h");
    
    if (floor == -1){
        elevio_motorDirection(DIRN_DOWN);
    }

    while (floor != 0){
        floor = elevio_floorSensor();
        printf("floor: %d \n",floor);
    }

    elevio_motorDirection(DIRN_STOP);
    
    return;
}