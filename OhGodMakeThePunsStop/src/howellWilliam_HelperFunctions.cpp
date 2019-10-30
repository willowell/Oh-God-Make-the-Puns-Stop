#include "howellWilliam_HelperFunctions.h"
#include <iostream>
#include <string>
#include <cctype>
#include <vector>

#include "howellWilliam_Auditorium.h"
#include "howellWilliam_DoublyLinkedList.h"
#include "howellWilliam_HelperExceptions.h"

using namespace whowell_OhGodMakeThePunsStop;
using namespace whowell_OhGodMakeThePunsStop_HelperExceptions;

namespace whowell_OhGodMakeThePunsStop_HelperFunctions {
	int validateStringAsSingleDigitIntegerInRange( std::string str, int min, int max ) {
		std::string::size_type sz;
		bool isValid = false;
		int userShort;

		do {
			try {
				std::cin >> str;

				if ( str.length() > 1 )
					throw InvalidStringLengthException();

				for ( std::size_t i = 0; i < str.length(); i++ ) {
					if ( !isdigit( str.at( 0 ) ) )
						throw InvalidCharacterInputException();
					if ( !isdigit( str.at( i ) ) )
						throw InvalidCharacterInputException();
				}

				//Now, convert the string to an integer, store it in userShort
				//Then, check that the value is within the expected range
				userShort = std::stoi( str, &sz );

				if ( userShort < min || userShort > max )
					throw IntegerOutOfRangeException();
				//If no exception has been thrown by this point, then the input is valid.
				isValid = true;
			} catch ( InvalidStringLengthException& e ) {
				isValid = false;
				std::cout << e.what() << '\n';
			} catch ( InvalidCharacterInputException& e ) {
				isValid = false;
				std::cout << e.what() << '\n';
			} catch ( IntegerOutOfRangeException& e ) {
				isValid = false;
				std::cout << e.what() << '\n';
			}
		} while ( !isValid );

		return userShort;
	}

	int validateStringAsDoubleDigitIntegerInRange( std::string str, int min, int max ) {
		std::string::size_type sz;
		bool isValid = false;
		int userShort;

		do {
			try {
				std::cin >> str;

				if ( str.length() > 2 )
					throw InvalidStringLengthException();

				for ( std::size_t i = 0; i < str.length(); i++ ) {
					if ( !isdigit( str.at( 0 ) ) )
						throw InvalidCharacterInputException();
					if ( !isdigit( str.at( i ) ) )
						throw InvalidCharacterInputException();
				}

				//Now, convert the string to an integer, store it in userShort
				//Then, check that the value is within the expected range
				userShort = std::stoi( str, &sz );

				if ( userShort < min || userShort > max )
					throw IntegerOutOfRangeException();
				//If no exception has been thrown by this point, then the input is valid.
				isValid = true;
			} catch ( InvalidStringLengthException& e ) {
				isValid = false;
				std::cout << e.what() << '\n';
			} catch ( InvalidCharacterInputException& e ) {
				isValid = false;
				std::cout << e.what() << '\n';
			} catch ( IntegerOutOfRangeException& e ) {
				isValid = false;
				std::cout << e.what() << '\n';
			}
		} while ( !isValid );

		return userShort;
	}


	char validateStringAsCharacter( std::string str, char upperch1, char upperch2 ) {
		bool isValid = false;
		char userChar;

		do {
			try {
				std::cin >> str;

				if ( str.length() > 1 )
					throw InvalidStringLengthException();

				//Now, convert the string to an integer, store it in userShort
				//Then, check that the value is within the expected range
				userChar = str.at( 0 );

				if ( toupper( userChar ) == upperch1 || toupper( userChar ) == upperch2 )
					isValid = true;
				else
					throw InvalidCharacterInputException();

			} catch ( InvalidStringLengthException& e ) {
				isValid = false;
				std::cout << e.what() << '\n';
			} catch ( InvalidCharacterInputException& e ) {
				isValid = false;
				std::cout << e.what() << '\n';
			}
		} while ( !isValid );

		return userChar;
	}

	void performReservationsWithVectors( DoublyLinkedList* list, Auditorium* auditorium,
			std::vector< short > rows, short tickets ) {
		std::string buffer;
		char yetAnotherUserChar;

		try {
			for ( short i = 0; i < tickets; i++ ) {
				if ( list->searchForNodeAndGetStatus(
					//assume all the seats are on the first selected row
					( auditorium->getNumRows() / 2 ),
					//then, look at the seat in the middle
					//and subtract half the number of tickets that the user selected
					//so that the middle ticket is exactly in the middle of the row
					( auditorium->getNumSeats() / 2 ) - ( tickets / 2 ) + i ) == true )
						throw UnableToReserveASeatException();
			} //close for-loop

			//If no exception has been thrown, then all of the seats are available
			//and can now be reserved.
			printf( "The seats in the middle of the row are available!\n" );
			printf( "Would you like to reserve them? (\"Y\" or \"N\")\n" );
			yetAnotherUserChar = validateStringAsCharacter( buffer, 'Y', 'N' );

			if ( toupper( yetAnotherUserChar ) == 'Y' ) {
				//Reserve the seats.
				//These should not throw an exception, but if they do,
				//it will be handled by the catch block below.
				for ( short j = 0; j < tickets; j++ )
					list->reserveASeatWithoutInput( auditorium, ( auditorium->getNumRows() / 2 ),
						                          ( auditorium->getNumSeats() / 2 ) - ( tickets / 2 ) + j );
				printf( "Seats reserved!\n" );

			} else if ( toupper( yetAnotherUserChar ) == 'N' )
				printf( "The seats will not be reserved.\n" );
		} catch ( UnableToReserveASeatException& e ) {
			std::cout << e.what() << '\n';
		} //close try-catch block
	}
} /* namespace whowell_HelperFunctions */
