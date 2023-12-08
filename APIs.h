/****************************************************************/
/* 	  Author   	       : Mark Ehab                   	        */
/* 	  Date     	       : Aug 12, 2023               	        */
/*    Description	   : APIs Header File	                    */
/* 	  Version     	   : V1.0             	                    */
/****************************************************************/

#ifndef APIS_H
#define APIS_H

/*--------------------------------------------------------------*/
/*		            NEW USER DEFINED DATA TYPES  	            */
/*--------------------------------------------------------------*/

/* bus_t */
typedef struct 
{
    int busId;
    char* destination;
    int capacity;
    int availableSeats;
}bus_t;

/* reservation_t */
typedef struct 
{
   int reservationId;
   int busId;
   int numOfSeats;  
}reservation_t;

/* user_t */
typedef struct 
{
     char* username;
     char* password; 
     reservation_t** reservationsList;  
}user_t;

/*--------------------------------------------------------------*/
/*		                       MACROS           	            */
/*--------------------------------------------------------------*/

/* Login Status */
#define LOGIN_FAIL             0U
#define LOGIN_PASS             1U

/* Logout Status */
#define LOGOUT_FAIL            0U
#define LOGOUT_PASS            1U

/* Reservation Status */
#define RESERVATION_FAILD      0U
#define RESERVATION_PASSED     1U

/* Bus Id Status */
#define BUS_ID_INVALID         2U

/* Cancellation Status */
#define CANCELLATION_FAILD     0U
#define CANCELLATION_PASSED    1U

/* Exit Status */
#define EXIT_DISABLE           0U
#define EXIT_ENABLE            1U

/*--------------------------------------------------------------*/
/*		                FUNCTIONS PROTOTYPES  	                */
/*--------------------------------------------------------------*/

/**********************************************************************************/
/* Description     : Checks if login passed or not       			              */
/* Input Arguments : char* username , char* password	    	                  */
/* Return Type     : char                       				                  */
/**********************************************************************************/
char loginCheck(char* username,char* password);

/**********************************************************************************/
/* Description     : Shows all available buses and trips       			          */
/* Input Arguments : void                   	            	                  */
/* Return Type     : void                       				                  */
/**********************************************************************************/
void showAllBuses(void);

/**********************************************************************************/
/* Description     : Books a reservation for the user       			          */
/* Input Arguments : int busId , int numOfSeats	            	                  */
/* Return Type     : char                       				                  */
/**********************************************************************************/
char bookABus(int busId , int numOfSeats);

/**********************************************************************************/
/* Description     : Cancels a reservation based on its passed id     	          */
/* Input Arguments : int reservationId	            	                          */
/* Return Type     : char                       				                  */
/**********************************************************************************/
char cancelReservation(int reservationId);

/**********************************************************************************/
/* Description     : Shows all booked reservations            			          */
/* Input Arguments : int busId , int numOfSeats	            	                  */
/* Return Type     : void                       				                  */
/**********************************************************************************/
void showAllReservations(void);

/*--------------------------------------------------------------*/
/*		              EXTERN GLOBAL VARIABLES  	                */
/*--------------------------------------------------------------*/

extern user_t user;
extern bus_t buslist[5];

#endif