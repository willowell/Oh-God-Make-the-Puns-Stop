#include <fstream>
#include <iostream>
#include <vector>

#include "howellWilliam_Auditorium.h"
#include "howellWilliam_DoublyLinkedList.h"
#include "howellWilliam_HelperExceptions.h"
#include "howellWilliam_HelperFunctions.h"
#include "howellWilliam_Node.h"
#include "howellWilliam_Node.h"
#include "howellWilliam_Theater.h"


using namespace whowell_OhGodMakeThePunsStop;
using namespace whowell_OhGodMakeThePunsStop_HelperExceptions;
using namespace whowell_OhGodMakeThePunsStop_HelperFunctions;

int main() {

    std::fstream*        file1;
    std::fstream*        file2;
    std::fstream*        file3;
    Auditorium*          audi1;
    Auditorium*          audi2;
    Auditorium*          audi3;
    Theater*             theater;
    DoublyLinkedList*    list1;
    DoublyLinkedList*    list2;
    DoublyLinkedList*    list3;
    short                userShort           = 0;
    short                userSelectedTickets = 0;
    short                choice              = 0;
    std::string          buffer;
    //Vectors for holding the row and seat positions of the seats that the user wanted to purchase
    std::vector< short > userSelectedSeats;
    std::vector< short > userSelectedRows;

    ////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////
    ///INIT PHASE

    try {
        file1 = new std::fstream( "A1.txt", std::ios::in );
        file2 = new std::fstream( "A2.txt", std::ios::in );
        file3 = new std::fstream( "A3.txt", std::ios::in );
    } catch (...) {
        std::cerr << "Something bad happened to the files!\n";
        return 0;
    }

    audi1   = new Auditorium();
    audi2   = new Auditorium();
    audi3   = new Auditorium();
    theater = new Theater();
    list1   = new DoublyLinkedList();
    list2   = new DoublyLinkedList();
    list3   = new DoublyLinkedList();

    ////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////
    ///LOAD PHASE

    list1->load( file1, audi1 );
    list2->load( file2, audi2 );
    list3->load( file3, audi3 );

    //Close the input files - they aren't needed until the end of the program.
    file1->close();
    file2->close();
    file3->close();

    ////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////
    ///MAIN LOOP

    main_menu:
	userShort = -1;
    printf( "1. View Auditorium\n" );
    printf( "2. Reserve Tickets\n" );
    printf( "3. Ticket Report\n"   );
    printf( "4. Quit\n"            );

	userShort = ( short ) validateStringAsSingleDigitIntegerInRange( buffer, 1, 4 );
    choice = userShort;

    if ( choice == 1 ) {
    	userShort = -1;
        printf( "1. Auditorium 1\n" );
        printf( "2. Auditorium 2\n" );
        printf( "3. Auditorium 3\n" );

        userShort = ( short ) validateStringAsSingleDigitIntegerInRange( buffer, 1, 3 );

        if ( userShort == 1 )
        	list1->displayAsAuditorium( audi1 );
        if ( userShort == 2 )
        	list2->displayAsAuditorium( audi2 );
        if ( userShort == 3 )
        	list3->displayAsAuditorium( audi3 );
        std::cout << "\n\n";
        std::cout << "Returning to main menu.\n";
        goto main_menu;
    }

    if ( choice == 2 ) {
    	userShort = -1;
    	printf( "Please choose an auditorium:\n" );
        printf( "1. Auditorium 1\n"              );
        printf( "2. Auditorium 2\n"              );
       	printf( "3. Auditorium 3\n"              );

       	userShort = ( short ) validateStringAsSingleDigitIntegerInRange( buffer, 1, 3 );

        if ( userShort == 1 )
        	list1->displayAsAuditorium( audi1 );
        if ( userShort == 2 )
        	list2->displayAsAuditorium( audi2 );
        if ( userShort == 3 )
        	list3->displayAsAuditorium( audi3 );
        std::cout << "\n\n";

		printf( "Please enter the number of tickets you want to purchase.\n" );
		userSelectedTickets = ( short ) validateStringAsDoubleDigitIntegerInRange( buffer, 1, 100 );

		short i = userSelectedTickets;

		for ( short j = 0; j < i; j++ ) {
			userSelectedRows.push_back( j );
			userSelectedSeats.push_back( j );
		}

		//The vectors are now big enough to store all necessary seats
		//Request values for the seat positions
		for ( short k = 0; k < userSelectedTickets; k++ ) {
			printf( "Please enter the row number for the %d seat that you want to purchase.\n", k + 1 );
			userSelectedRows[ k ] = validateStringAsDoubleDigitIntegerInRange( buffer, 1, 100 );

			printf( "Please enter the seat number for the %d seat that you want to purchase.\n", k + 1 );
			userSelectedSeats[ k ] = validateStringAsDoubleDigitIntegerInRange( buffer, 1, 100 );
		}
		//The vectors should now hold all the seats that the user wants.
		//Check to see that the seats are available.
		try {
			if ( userShort == 1 ) {
				for ( short i = 0; i < userSelectedTickets; i++ )
					list1->reserveASeatWithoutInput( audi1, userSelectedRows[ i ], userSelectedSeats[ i ] );
				printf( "Seats reserved!\n" );
			}
			if ( userShort == 2 ) {
				for ( short i = 0; i < userSelectedTickets; i++ )
					list2->reserveASeatWithoutInput( audi2, userSelectedRows[ i ], userSelectedSeats[ i ] );
				printf( "Seats reserved!\n" );
			}
			if ( userShort == 3 ) {
				for ( short i = 0; i < userSelectedTickets; i++ )
					list3->reserveASeatWithoutInput( audi3, userSelectedRows[ i ], userSelectedSeats[ i ] );
				printf( "Seats reserved!\n" );
			}
		} catch ( UnableToReserveASeatException& e ) {
			std::cout << e.what() << '\n';
			std::cout << "Attempting to locate good seats...\n";

			if ( userShort == 1 )
				performReservationsWithVectors( list1, audi1, userSelectedRows, userSelectedTickets );
			if ( userShort == 2 )
				performReservationsWithVectors( list2, audi2, userSelectedRows, userSelectedTickets );
			if ( userShort == 3 )
				performReservationsWithVectors( list3, audi3, userSelectedRows, userSelectedTickets );
		}

		//Reset the vectors
		userSelectedRows.clear();
		userSelectedSeats.clear();

		std::cout << "Returning to main menu.\n";
		goto main_menu;
	} //close if (choice == 2) //reserve a seat

	if ( choice == 3 ) {
		theater->setTotalSeatsOpen(
				audi1->getNumSeatsOpen() + audi2->getNumSeatsOpen() + audi3->getNumSeatsOpen()
		);
		theater->setTotalSeatsReserved(
				audi1->getNumSeatsReserved() + audi2->getNumSeatsReserved() + audi3->getNumSeatsReserved()
		);
		theater->setUserSeats( userSelectedTickets );
		theater->display();
		std::cout << "Returning to main menu.\n";
		goto main_menu;
	}

	if ( choice == 4 )
		std::cout << "Quitting the program.\n";

    ////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////
    ///FILE OUTPUT

	//Reopen the files for output - delete any data already in the files.
	file1->open( "A1.txt", std::ios::out | std::ios::trunc );
	file2->open( "A2.txt", std::ios::out | std::ios::trunc );
	file3->open( "A3.txt", std::ios::out | std::ios::trunc );

	list1->writeToFile( file1, audi1 );
	list2->writeToFile( file2, audi2 );
	list3->writeToFile( file3, audi3 );

    ////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////
    ///GARBAGE COLLECTION

	file1->close();
	file2->close();
	file3->close();

	delete file1;
	delete file2;
	delete file3;
	delete audi1;
	delete audi2;
	delete audi3;
	delete theater;
	delete list1;
	delete list2;
	delete list3;

	file1   = nullptr;
	file2   = nullptr;
	file3   = nullptr;
	audi1   = nullptr;
	audi2   = nullptr;
	audi3   = nullptr;
	theater = nullptr;
	list1   = nullptr;
	list2   = nullptr;
	list3   = nullptr;

    return 0;
}
