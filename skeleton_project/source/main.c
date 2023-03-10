#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"
#include "driver/Controller.h"
#include "driver/Queue.h"
#include "driver/variables.h"

enum doorStatus doors = doorClosed;

int good2go = 1; // hei

int goal = -2;

int stop = 0;

MotorDirection direction = DIRN_STOP;

node queueHead = NULL; // Starten på køen, skape litt trøbbel

int obstruction = 0;

int lastFloor = 0;

MotorDirection lastDir;

int hasStopped = 0;

int main()
{
    elevio_init();
    printf("=== Example Program ===\n");
    printf("Press the stop button on the elevator panel to exit\n");

    initElev(); // Vårt start-program

    time_t timeOpened = time(NULL) - 3; // For å starta me dørene lukka, da de basere
                                        // på at den e minst 3 lavere enn nåværende tid

    elevio_buttonLamp(0, 1, 1);

    while (1)
    {
        printf("Her starte løkka på ny \n");
        int floor = elevio_floorSensor();

        if (floor != -1)
        { // Sets the floor indicator
            elevio_floorIndicator(floor);
            lastFloor = floor;
        }

        if (floor == goal && direction == DIRN_STOP)
        {
            queueHead = clearVal(queueHead, goal);
            printf("cleard cuz f=g\n");
        }

        if (goal != -2 && hasStopped)
        {
            if (goal > lastFloor)
            {
                setMotorDirection(DIRN_UP);
            }
            else if (goal < lastFloor)
            {
                setMotorDirection(DIRN_DOWN);
            }
            else if (lastDir == DIRN_UP)
            {
                setMotorDirection(DIRN_DOWN);
            }
            else if (lastDir == DIRN_DOWN)
            {
                setMotorDirection(DIRN_UP);
            }
            hasStopped = 0;
        }

        time_t now = time(NULL); // oppdaterer nåværende tid

        if (queueHead != NULL && direction == DIRN_STOP)
        { // goal = -2 betyr at det ikke er noe mål enda, må settes til -2 når den kommer frem
            goal = queueHead->data;
        }

        if (obstruction == 1)
        {
            if (doors == doorOpen)
            {
                timeOpened = now;
            }
        }
        printf("her?\n");

        if ((direction != DIRN_STOP) && (floor != -1))
        {
            node p;
            p = queueHead;
            if (queueHead == NULL)
            {
                break;
            };
            while (p->next != NULL)
            {
                if (floor == p->data && p->btnType != BUTTON_HALL_UP && direction == DIRN_DOWN)
                {
                    stopMidway();
                    timeOpened = now;
                    break;
                }
                else if (floor == p->data && p->btnType != BUTTON_HALL_DOWN && direction == DIRN_UP)
                {
                    stopMidway();
                    timeOpened = now;
                    break;
                }

                p = p->next;
            }
        }

        if (floor == goal && direction != DIRN_STOP) // kjører når heis er fremme
        {
            setMotorDirection(DIRN_STOP);      // setter motor til stopp, må fikses så den ikke kalles når heisen skal videre
            openDoor();                        // åpner dørene
            timeOpened = time(NULL);           // sier at dørene ble åpnet nå, navnet er feil :(
            printf("goal is now %d \n", goal); // brukt til feilsøking
            if (queueHead == NULL)
            { // hvis kø er tom skal det ikke være noe mål
                goal = -2;
            }
            else
            {
                goal = queueHead->data;
            }
            printf("Clearval has been run\n"); // brukt til feilsøking

            for (int i = 0; i < 3; i++)
            {
                elevio_buttonLamp(floor, i, 0);
            }
        }

        good2go = ready(timeOpened, now, goal); // sjekker om heisen er klar, dvs tid siden dører åpnet, om dører er åpne og har et mål

        printf("floor: %d \n", floor);
        printf("Goal: %d \n", goal);

        if (good2go)
        {
            if (floor == -1)
            {
            } // trenger løsning viss etasje udefinert
            else if (goal > floor)
            {
                setMotorDirection(DIRN_UP);
                // printf("jeje");
                good2go = 0;
            }
            else if (goal < floor)
            {
                setMotorDirection(DIRN_DOWN);
                good2go = 0;
            }
        }

        if (elevio_stopButton())
        {
            if (direction != DIRN_STOP)
            {
                lastDir = direction;
            }
            queueHead = NULL; // setter kø til ingenting, kan muligens skape trøbbel at minne ikke frigjøres
            if (elevio_floorSensor() != -1)
            {                            // står heisen i en etasje skal den starte timer på åpne dører
                timeOpened = time(NULL); // sier når dørene ble åpnet
                setMotorDirection(DIRN_STOP);
            }
            printf("før stopp\n");
            StopButton(); // gjør noen ting når stopp trykkes, se definisjon
            printf("etter stopp\n");
        }
        printf("Helt etter stopp\n");
        if (now >= timeOpened + 3 && doors == doorOpen)
        {                              // closes doors if open for more than three secs since stop
            closeDoor();               // kanskje legge til at denne kun kjøres dersom dørene er åpne
            printf("Doors closed \n"); // det kan gjørs me global variabel
        }
        printf("Eg kjøre videre altså\n");

        for (int i = 0; i < N_FLOORS; i++) // oppdatere knapper
        {
            for (int j = 0; j < N_BUTTONS; j++)
            {
                if (elevio_callButton(i, j) == 1 && floor != i)
                {
                    queueHead = addFloor(queueHead, i, j);
                    elevio_buttonLamp(i, j, 1);
                }
            }
        }
        if (queueHead != NULL)
        { // brukt til feilsøking
            printf("head e ikkje NULL \n");
        }
        obstruction = elevio_obstruction();
    }
    return 0;
}