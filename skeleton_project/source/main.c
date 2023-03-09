#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"
#include "driver/Controller.h"
#include "driver/Queue.h"
#include "driver/variables.h"

enum doorStatus doors = doorClosed;

int good2go = 1;

int goal = -2;

int stop = 0;

MotorDirection direction = DIRN_STOP;

node queueHead = NULL; // Starten på køen, skape litt trøbbel

int obstruction = 0;

int main()
{
    // MotorDirection *currentDir = &direction; // Holde styr på retningen til heisen, trenge nok ikkje vær peker
    // Prøve uden denne
    elevio_init();
    printf("=== Example Program ===\n");
    printf("Press the stop button on the elevator panel to exit\n");

    initElev(); // Vårt start-program


    time_t timeClosed = time(NULL) - 3; // For å starta me dørene lukka, da de basere
                                        // på at den e minst 3 lavere enn nåværende tid



    elevio_buttonLamp(0, 1, 1);

    // elevio_motorDirection(DIRN_UP);

    while (1)
    {
        printf("Her starte løkka på ny \n");
        int floor = elevio_floorSensor();

        if(doors){
            // printf("d"); //brukt til å test om doors er åpne i 3 sekunder etter knappen er sluppet
        }
        time_t now = time(NULL);    //oppdaterer nåværende tid

        if (queueHead!=NULL && goal == -2){ //goal = -2 betyr at det ikke er noe mål enda, må settes til -2 når den kommer frem
            goal = queueHead->data;
        }

        if (floor == goal) // kjører når heis er fremme
        {
            setMotorDirection(DIRN_STOP); // setter motor til stopp, må fikses så den ikke kalles når heisen skal videre
            queueHead = clearVal(queueHead, goal);      // fjerner en verdi fra køen
            openDoor();       // åpner dørene
            timeClosed = time(NULL);    // sier at dørene ble åpnet nå, navnet er feil :(
            printf("goal is now %d \n", goal);  // brukt til feilsøking
            if(queueHead == NULL){  // hvis kø er tom skal det ikke være noe mål
                goal = -2;
            }
            printf("Clearval has been run\n"); // brukt til feilsøking
        }
        
        good2go = ready(timeClosed, now, goal); // sjekker om heisen er klar, dvs tid siden dører åpnet, om dører er åpne og har et mål
        

        printf("floor: %d \n", floor);
        printf("Goal: %d \n", goal);

        if(good2go){
            if (floor == -1){
            }                              // trenger løsning viss etasje udefinert
            else if (goal > floor)
            {
                setMotorDirection(DIRN_UP);
                // printf("jeje");
                good2go = 0;
            }else if (goal < floor)
            {
                setMotorDirection(DIRN_DOWN);
                good2go = 0;
            }
            
            
        }

        if (elevio_stopButton())
        {
            StopButton(); // gjør noen ting når stopp trykkes, se definisjon
            queueHead = NULL;       // setter kø til ingenting, kan muligens skape trøbbel at minne ikke frigjøres
            elevio_motorDirection(DIRN_STOP);
            if (elevio_floorSensor() != -1){ // står heisen i en etasje skal den starte timer på åpne dører
                timeClosed = time(NULL);    //sier når dørene ble åpnet
            }else{
                setMotorDirection(DIRN_DOWN);
                while(elevio_floorSensor() != 0){};     // gå ned til etasje er lik 0, altså første
                setMotorDirection(DIRN_STOP);   // stopp der
            }

            continue; //starter løkken på ny etter stop-knapp

        }
        if (now >= timeClosed + 3 && doors==doorOpen){ // closes doors if open for more than three secs since stop
                closeDoor();      // kanskje legge til at denne kun kjøres dersom dørene er åpne
                printf("Doors closed \n");  // det kan gjørs me global variabel
        }

        for (int i = 0; i < N_FLOORS; i++) // oppdatere knapper
        {
            for (int j = 0; j < N_BUTTONS; j++)
            {
                if (elevio_callButton(i, j) == 1){
                    queueHead = addFloor(queueHead, i);
                    // printf("hei");
                }
            }
            
        }
        if(queueHead != NULL){  // brukt til feilsøking
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

        obstruction = elevio_obstruction();

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
