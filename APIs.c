/****************************************************************/
/* 	Author   	 : Mark Ehab                   	     		    */
/* 	Date     	 : Aug 12, 2023               				    */
/*  Description	 : APIs Program File	                		*/
/* 	Version      : V1.0             	                		*/
/****************************************************************/

/*--------------------------------------------------------------*/
/*						INCLUDED LIBRARIES						*/
/*--------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "apis.h"

/*--------------------------------------------------------------*/
/*		  			 GLOBAL VARIABLES DECLARATIONS			    */
/*--------------------------------------------------------------*/
user_t user;				/* Create user (Global) */
bus_t buslist[5];			/* Create list of buses */
static int reservationsCount = 0;	/* Global variable to hold number of resevations */

/*--------------------------------------------------------------*/
/*	           		 FUNCTIONS IMPLEMENTATIONS			  		*/
/*--------------------------------------------------------------*/

/**********************************************************************************/
/* Description     : Checks if login passed or not       			 			  */
/* Input Arguments : char* username , char* password	    	                  */
/* Return Type     : char                       			         			  */
/**********************************************************************************/
char loginCheck(char* username,char* password)
{
	/* Local variables definitions */
	char passFlag; 				/* Local variable to hold login status */

	/* Check if username and password are passed successfully or not */
	if(!strcmp(username,user.username) && !strcmp(password,user.password))
	{
		/* Username and password are passed successfully */
		passFlag = LOGIN_PASS;

		/* Enter the app main menu */
		printf("Login passed successfully\n\n/*******************************************************/\n/*                                                     */\n/*            WELCOME TO BUS RESERVATION APP           */\n/*                                                     */\n/*******************************************************/\n\n");
	}
	else
	{
		/* Username and password are not passed successfully */
		passFlag = LOGIN_FAIL;

		/* Show an error pop up message */
		printf("Login failed ... Either Username or Password is invalid, Please try again.\n\n");
	}

	return passFlag;
}
/**********************************************************************************/
/* Description     : Shows all available buses and trips       					  */
/* Input Arguments : void                   	            	                  */
/* Return Type     : void                       				 				  */
/**********************************************************************************/
void showAllBuses(void)
{
	/* Local variables definitions */
	int busCounter;

	/* Print a separating line */
	printf("\n-----------------------------------------\n");

	/* Traverse list of buses */
	for(busCounter = 0 ; busCounter<5 ;busCounter++)
	{
		/* Print to the user the id, destination, capacity and number of available seats for each bus */
		printf("Bus: %d\nBus Id: %d\nBus Destination: %s\nBus Capacity: %d\nNumber of available seats: %d\n-----------------------------------------\n",busCounter+1,buslist[busCounter].busId,buslist[busCounter].destination,buslist[busCounter].capacity,buslist[busCounter].availableSeats);
	}

	/* Print a new line */
	printf("\n");
}	
/**********************************************************************************/
/* Description     : Books a reservation for the user       					  */
/* Input Arguments : int busId , int numOfSeats	            	                  */
/* Return Type     : char                       		               		      */
/**********************************************************************************/
char bookABus(int busId , int numOfSeats)
{
	/* Local variables definitions */
	char reservationFlag = BUS_ID_INVALID;		/* Local variable to hold reservation status */
	int busCounter;					/* Local variable to act as bus counter */

	/* Traverse list of buses */
	for(busCounter = 0 ; busCounter<5 ;busCounter++)
	{
		/* Check if passed bus id is valid or not */
		if(buslist[busCounter].busId == busId)
		{
			/* Bus id is valid */

			/* Check if there are available seats in the bus */
			if(buslist[busCounter].availableSeats == 0)	
			{
				/* There are no available seats in the bus */
				reservationFlag = RESERVATION_FAILD;

				/* Print bus is fully booked to the user */
				printf("\nBus is fully booked !\n\n");
			}
			/* Check if available seats are enough for reservation seats */
			else if(buslist[busCounter].availableSeats < numOfSeats) 
			{
				/* There are no enough seats in the bus */
				reservationFlag = RESERVATION_FAILD;

				/* Print There are no enough seats in the bus to the user */
				printf("\nThere are no enough seats in the bus !\n\n");
			}
			else if(buslist[busCounter].availableSeats >= numOfSeats)
			{
				/* There are enough seats in the bus */
				reservationFlag = RESERVATION_PASSED;

				/* Decrease the number of available seats in the bus by the number of reserved seats */
				buslist[busCounter].availableSeats -= numOfSeats;

				/* Book the reservation */
				user.reservationsList = (reservation_t**)realloc(user.reservationsList,++reservationsCount * sizeof(reservation_t*));
				
				/* Add the user's new reservation to their reservations list */
				user.reservationsList[reservationsCount-1] = (reservation_t*)malloc(sizeof(reservation_t));
				user.reservationsList[reservationsCount-1]->reservationId = reservationsCount;
				user.reservationsList[reservationsCount-1]->busId = busId ;
				user.reservationsList[reservationsCount-1]->numOfSeats = numOfSeats ;

				/* Print Reservation is done ! for the user */
				printf("\nReservation is done !\n\n");
			}
			break;
		}
	}

	/* Check if passed bus id is not found */
	if(reservationFlag == BUS_ID_INVALID)
	{
		/* Passed bus id is not found */
		reservationFlag = RESERVATION_FAILD;

		/* Print Invalid Bus Id ! to the user */
		printf("\nInvalid Bus Id !\n\n");
	}

	return reservationFlag;
}
/**********************************************************************************/
/* Description     : Cancels a reservation based on its passed id     	          */
/* Input Arguments : int reservationId	            	                          */
/* Return Type     : char                       		             		      */
/**********************************************************************************/
char cancelReservation(int reservationId)
{
	/* Local variables definitions */
	char cancellationFlag = CANCELLATION_FAILD;	/* Local variable to hold cancellation status */
	int reservationCounter;				/* Local variable to act as reservation counter  */
	int reservationsToBeReArranged;			/* Local variable to hold number of resevations to be re-arranged in reservation list after cancellation */
	int busCounter;					/* Local variable to act as bus counter */

	/* Check if reservation list is empty or not */
	if(reservationsCount == 0)
	{
		/* Reservation list is empty */
		printf("\nSorry no reservations to be cancelled !\n\n");
	}
	else
	{
		/* Reservation list is not empty */

		/* Traverse list of reservations */
		for(reservationCounter = 0 ; reservationCounter < reservationsCount ; reservationCounter++)
		{
			/* Check if passed resevation id is valid or not */
			if(reservationId == user.reservationsList[reservationCounter]->reservationId)
			{
				/* Passed resevation id is valid */
				cancellationFlag = CANCELLATION_PASSED;

				/* Print the cancelled resevation for the user */
				printf("\nReservation %d is cancelled !\n",user.reservationsList[reservationCounter]->reservationId);
				
				/* Traverse list of buses */
				for(busCounter = 0 ; busCounter<5 ;busCounter++)
				{
					/* Check bus id in the cancelled resevation with other bus ids */
					if(buslist[busCounter].busId == user.reservationsList[reservationCounter]->busId)
					{	
						/* Increase the number of available seats in the bus by the number of reserved seats in the cancelled reservation */
						buslist[busCounter].availableSeats += user.reservationsList[reservationCounter]->numOfSeats;
						break;
					}
				}

				/* Check if cancelled resevation is the last reservation is the list */
				if(reservationCounter == reservationsCount-1)
				{
					/* Cancelled resevation is the last reservation is the list */

					/* Cancel the reservation */
					free(user.reservationsList[reservationCounter]);
				}
				else
				{
					/* Cancelled resevation is the not last reservation is the list */

					/* Calculate the number of reservations to be re-arranged */
					reservationsToBeReArranged = reservationsCount-1-reservationCounter;

					/* Re-arrang reservation list after cancellation */
					while(reservationsToBeReArranged)
					{
						user.reservationsList[reservationCounter]->reservationId = user.reservationsList[reservationCounter+1]->reservationId; 
						user.reservationsList[reservationCounter]->busId = user.reservationsList[reservationCounter+1]->busId; 
						user.reservationsList[reservationCounter]->numOfSeats = user.reservationsList[reservationCounter+1]->numOfSeats; 
						reservationsToBeReArranged--;
						reservationCounter++;
					}

					/* Cancel the reservation */
					free(user.reservationsList[reservationCounter]);
				}

				/* Remove the resevation from reservation list */
				user.reservationsList = (reservation_t**)realloc(user.reservationsList,--reservationsCount * sizeof(reservation_t*));
				
				/* Check if reservation list is not empty */
				if(reservationsCount > 0)
				{
					/* Reservation list is not empty */

					/* Print reservation list for the user after cancellation */
					showAllReservations();
				}
				else
				{
					/* Reservation list is empty */

					/* Print There are no reservations left ! after cancellation */
					printf("\nThere are no reservations left !\n\n");
				}

				break;
			}
		}

		/* Check if passed reservation id is invalid or not found */
		if(cancellationFlag == CANCELLATION_FAILD)
		{	
			/* Passed reservation id is invalid or not found */

			/* Print Invalid Reservation Id ! to the user */
			printf("\nInvalid Reservation Id !\n\n");
		}
	}

	return cancellationFlag;
}
/**********************************************************************************/
/* Description     : Shows all booked reservations            					  */
/* Input Arguments : int busId , int numOfSeats	            	                  */
/* Return Type     : void                                                         */
/**********************************************************************************/
void showAllReservations(void)
{
	/* Local varialbles definitions */
	int reservationCounter;				/* Local variable to act as reservation counter  */
	
	/* Check if reservation list is empty */
	if(reservationsCount == 0)
	{
		/* Reservation list is empty */
		printf("\nSorry no reservations are booked\n\n");
	}
	else
	{
		/* Print a separating line */
		printf("\n-----------------------------------------\n");

		/* Traverse list of reservations */
		for(reservationCounter = 0 ; reservationCounter < reservationsCount ; reservationCounter++)
		{
			/* Print to the user the reservation id, bus id and number of reserved seats for each reservation */
			printf("Reservation Id: %d\nBus Id: %d\nNumber of reserved seats: %d\n-----------------------------------------\n",user.reservationsList[reservationCounter]->reservationId,user.reservationsList[reservationCounter]->busId,user.reservationsList[reservationCounter]->numOfSeats);
		}

		/* Print a new line */
		printf("\n");
	}	
}