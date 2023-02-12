// AL-ASKAR KARAM
// REPULOJEGYEK

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"
#include "database.h"
//#include "debugmalloc.h"

// menu prototipusok
void menu(node **database);
void flights_menu(node **database);
void flight_search_menu(node **database);
void administrator_menu(node **database);

// fomenu
int main(void)
{
    //elso elemre mutato pointer
    node *all_flights = NULL;

    menu(&all_flights);
    
    //adatbazis felszabaditas
    free_list(all_flights);
}

void menu(node **database)
{


    while (1)
    {
        char input = 0;
        do
        {
            // menu
            printf("\nÜdvözöljük! Kérem válasszon a menüpontok közül:\n"
                   "[1] Járatok\n"
                   "[2] Járatkeresés\n"
                   "[3] Adminisztrátor\n"
                   "[4] Kilépés\n");

            scanf(" %c", &input);

            switch (input)
            {
            case '1':
                flights_menu(&*database);
                break;

            case '2':
                flight_search_menu(&*database);
                break;

            case '3':
                administrator_menu(&*database);
                break;

            case '4':
                return;
            }
        } while (input != '1' && input != '2' && input != '3' && input != '4');
    }
}

void flights_menu(node **database)
{

    char flight[6];
    if (print_flights(*database))
    {
        do
        {
            printf("Válasszon járatot: ");
            scanf(" %s", flight);
        } while (flight_exists(*database, flight) == false);

        buy_ticket(&*database, flight);
        back();
    };
}

void flight_search_menu(node **database)
{
    while (1)
    {
        char input = 0;
        do
        {
            printf("\nVálasszon a menüpontok közül: \n"
                   "[1] Keresés járatszám szerint\n"
                   "[2] Keresés városok szerint\n"
                   "[3] Vissza\n");
            scanf(" %c", &input);
        } while (input != '1' && input != '2' && input != '3');
        char search[6] = "123456";
        char *search2 = "a";
        switch (input)
        {
        case '1':

            do
            {
                printf("Járatszám: ");
                scanf(" %s", search);
            } while (flight_exists(*database, search) == false);
            buy_ticket(&*database, search);
            back();
            break;
        case '2':
            do
            {
                printf("Honnan-Hova?: ");
                scanf(" %s", search);
                search2 = search_city(*database, search);
            } while (flight_exists(*database, search2) == false);
            buy_ticket(&*database, search2);
            back();
            break;
        case '3':
            return;
            break;
        }
    }
}

void administrator_menu(node **database)
{
    char *password = "password";
    char input[24];
    printf("Password: ");
    scanf("%s", input);

    // ha jo a jelszo
    if (strcmp(password, input) == 0)
    {
        while (1)
        {
            char input = 0;
            do
            {
                printf("\nVálasszon a menüpontok közül: \n"
                       "[1] Új járat nyílvántartás\n"
                       "[2] Járatok adatai\n"
                       "[3] Vissza\n");
                scanf(" %c", &input);

            } while (input != '1' && input != '2' && input != '3');

            node *new_flight;
            switch (input)
            {
            case '1':
                new_flight = add_flights_data();
                add_node(&*database, new_flight);
                break;
            case '2':
                if (print_flights(*database))
                {
                    char flight[6];
                    do
                    {
                        printf("Válasszon járatot: ");
                        scanf(" %s", flight);
                    } while (flight_exists(*database, flight) == false);
                    read_seatmap(*database, flight);
                    meals(*database, flight);
                    back();
                };
                break;
            case '3':
                return;
                break;
            }
        }
    }
}
