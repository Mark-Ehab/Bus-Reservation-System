/****************************************************************/
/* 	Author   	 : Mark Ehab                   	    		    */
/* 	Date     	 : Aug 12, 2023               					*/
/*  Description	 : Bus Reservation System Test	        		*/
/* 	Version      : V1.0             	                		*/
/****************************************************************/

/*--------------------------------------------------------------*/
/*						INCLUDED LIBRARIES						*/
/**-------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "apis.h"

/*--------------------------------------------------------------*/
/*		 	 			   	ENTRY POINT							*/
/*--------------------------------------------------------------*/
void main()
{
	/* Extern Global Variables Initializations */
	user.username = "Mark";				
	user.password = "12345";
	user.reservationsList = (reservation_t**)malloc(0*sizeof(reservation_t*));
	bus_t bus1 = {10,"Aswan",40,20};
	bus_t bus2 = {20,"Alex",40,30};
	bus_t bus3 = {30,"Cairo",40,10};
	bus_t bus4 = {40,"Sokhna",40,0};
	bus_t bus5 = {50,"October",40,2};
	buslist[0]=bus1;
	buslist[1]=bus2;
	buslist[2]=bus3;
	buslist[3]=bus4;
	buslist[4]=bus5;

	/* Local Variables Declarations and Definitions */
	char inputName[20] , inputPassword[20];
	char mainMenuOption ;
	int bus_id , num_of_seats , reservation_id;
	char loginStatus = LOGIN_FAIL , logoutStatus = LOGOUT_FAIL , exitStatus = EXIT_DISABLE;

	while(1)
	{
		/* Login Menu */
		while (loginStatus == LOGIN_FAIL)
		{
			printf("\n/*********************************/\n/*           Login Menu          */\n/*********************************/\n\n");
			printf("Username : ");
			scanf("%s",inputName);
			fflush(stdin);
			printf("Password : ");
			scanf("%s",inputPassword);
			fflush(stdin);
			loginStatus = loginCheck(inputName,inputPassword);
		}

		/* Main Menu */
		while(logoutStatus == LOGOUT_FAIL && exitStatus == EXIT_DISABLE)
		{
			printf("\n/*******************************************************/\n/* 			Main Menu		       */\n/*******************************************************/\n/*  In this menu you have all features the app can do  */\n/*  which can be stated as follows:                    */\n/*						       */\n/*  1) Show all available buses and trips              */\n/*  2) Book a reservation        		       */\n/*  3) Cancel a reservation                            */\n/*  4) Show all reservations                           */\n/*  5) Log out                                         */\n/*  6) Exit                                            */\n/*						       */\n/* Please press from 1 to 6 to select desired option:- */\n/*******************************************************/\n\n");	
			printf("Please enter your option : ");
			scanf("%c",&mainMenuOption);
			fflush(stdin);
			printf("\n");

			/* Switch on entered main menu option */
			switch (mainMenuOption)
			{
				case '1':
					/* Show all availble buses */
					showAllBuses();
					break;
				case '2':
					/* Book a reservation */
					printf("Please set bus id: ");
					scanf("%d",&bus_id);
					fflush(stdin);
					printf("Please set number of seats: ");
					scanf("%d",&num_of_seats);
					fflush(stdin);
					printf("\n");
					bookABus(bus_id,num_of_seats);
					break;
				case '3':
					/* Cancel a reservation */
					printf("Please set reservation id: ");
					scanf("%d",&reservation_id);
					fflush(stdin);
					cancelReservation(reservation_id);
					break;
				case '4':
					/* Show all reservations */
					showAllReservations();
					break;
				case '5':
					/* Logout and back to login menu */
					logoutStatus = LOGOUT_PASS;
					break;
				case '6':
					/* Exit the program */
					exitStatus = EXIT_ENABLE;
					break;
				
				default:
					printf("\nInvalid Option ! ... Please Try Again\n\n");
			}
		}
		/* Check if the user logged out or exited the program */
		if(logoutStatus == LOGOUT_PASS)
		{
			logoutStatus = LOGOUT_FAIL;
			loginStatus = LOGIN_FAIL;
		}
		else if(exitStatus == EXIT_ENABLE)
		{
			printf("/*------------------------------*/\n/*        END THE PROGRAM       */\n/*------------------------------*/\n");
			break;
		}	
	}
}
