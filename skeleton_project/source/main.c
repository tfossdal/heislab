#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"
#include "driver/Controller.h"
#include "driver/Queue.h"

int main()
{
    MotorDirection direction = DIRN_STOP;
    MotorDirection *currentDir = &direction;

    elevio_init();
    printf("=== Example Program ===\n");
    printf("Press the stop button on the elevator panel to exit\n");

    initElev(currentDir);

    node queueHead = NULL;

    time_t timeClosed = time(NULL) - 3;

    int doors = 0;

    int good2go = 1;

    int goal = -2;

    elevio_buttonLamp(0, 1, 1);

    // elevio_motorDirection(DIRN_UP);

    while (1)
    {
        printf("Her starte løkka på ny \n");
        int floor = elevio_floorSensor();

        if(doors){
            // printf("d"); //brukt til å test om doors er åpne i 3 sekunder etter knappen er sluppet
        }
        time_t now = time(NULL);

        if (queueHead!=NULL && goal == -2){ //goal = -2 betyr at det ikke er noe mål enda, må settes til -2 når den kommer frem
            goal = queueHead->data;
        }

        if (floor == goal) // kjører når heis er fremme
        {
            setMotorDirection(DIRN_STOP, currentDir);
            queueHead = clearVal(queueHead, goal);
            openDoor(&doors);
            timeClosed = time(NULL);
            printf("goal is now %d \n", goal);
            if(queueHead == NULL){
                goal = -2;
            }
            printf("Clearval has been run\n");
        }
        
        good2go = ready(timeClosed, now, goal, doors, currentDir); // sjekker om heisen er klar, dvs tid siden dører åpnet, om dører er åpne og har et mål
        

        printf("floor: %d \n", floor);
        printf("Goal: %d \n", goal);

        if(good2go){
            if (floor == -1){
            }                              // trenger løsning viss etasje udefinert
            else if (goal > floor)
            {
                setMotorDirection(DIRN_UP, currentDir);
                // printf("jeje");
                good2go = 0;
            }else if (goal < floor)
            {
                setMotorDirection(DIRN_DOWN, currentDir);
                good2go = 0;
            }
            
            
        }

        if (elevio_stopButton())
        {
            StopButton(queueHead, currentDir, &doors);
            queueHead = NULL;
            elevio_motorDirection(DIRN_STOP);
            if (elevio_floorSensor() != -1){ // står heisen i en etasje skal den starte timer på åpne dører
                timeClosed = time(NULL);
            }else{
                setMotorDirection(DIRN_DOWN, currentDir);
                while(elevio_floorSensor() != 0){};
                setMotorDirection(DIRN_STOP, currentDir);
            }

            continue; //starte løkken på ny

        }
        if (now > timeClosed + 3){ // closes doors if open for more than three secs since stop
            closeDoor(&doors);
            printf("Doors closed \n");
        }

        for (int i = 0; i < N_FLOORS; i++)
        {
            for (int j = 0; j < N_BUTTONS; j++)
            {
                if (elevio_callButton(i, j) == 1){
                    queueHead = addFloor(queueHead, i);
                    // printf("hei");
                }
            }
            
        }
        if(queueHead != NULL){
            printf("head e ikkje NULL \n");
        }



        // if (floor == 0)
        // {
        //     elevio_motorDirection(DIRN_STOP);
        // }

        // if (floor == N_FLOORS - 1)
        // {
        //     elevio_motorDirection(DIRN_STOP);
        // }

        // for (int f = 0; f < N_FLOORS; f++)
        // {
        //     for (int b = 0; b < N_BUTTONS; b++)
        //     {
        //         int btnPressed = elevio_callButton(f, b);
        //         elevio_buttonLamp(f, b, btnPressed);
        //     }
        // }

        if (elevio_obstruction())
        {
            elevio_stopLamp(1);
        }
        else
        {
            elevio_stopLamp(0);
        }
    }

    return 0;
}
