/*
 * Utilities.cpp
 *
 *  Created on: Oct. 7, 2019
 *      Author: whowell
 */

#include <cctype>
#include <iostream>
#include <string>
#include <vector>

#include "Utilities.h"

using namespace std;

namespace whowell {
	// Exceptions /////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////

	IntegerOutOfRangeException :: IntegerOutOfRangeException() {}

	IntegerOutOfRangeException :: ~IntegerOutOfRangeException() noexcept {}

	const char* IntegerOutOfRangeException :: what() const noexcept {
		return "Integer value out of range. Please try again.\n";
	}



	InvalidCharacterInputException :: InvalidCharacterInputException() {}

	InvalidCharacterInputException :: ~InvalidCharacterInputException() noexcept {}

	const char* InvalidCharacterInputException :: what() const noexcept {
		return "Invalid character. Please try again.\n";
	}



	InvalidStringLengthException :: InvalidStringLengthException() {}

	InvalidStringLengthException :: ~InvalidStringLengthException() noexcept {}

	const char* InvalidStringLengthException :: what() const noexcept {
		return "String too long. Please try again.\n";
	}



	NodeNotFoundException :: NodeNotFoundException() {}

	NodeNotFoundException :: ~NodeNotFoundException() noexcept {}

	const char* NodeNotFoundException :: what() const noexcept {
		return "Node not found in list.\n";
	}

	UnableToReserveASeatException :: UnableToReserveASeatException() {}

	UnableToReserveASeatException :: ~UnableToReserveASeatException() noexcept {}

	const char* UnableToReserveASeatException :: what() const noexcept {
		return "Unable to reserve seat.\n";
	}

	// List Modification Functions ////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////
/*
	void performReservationsWithVectors( std::list<Seat>* list, Auditorium* auditorium,
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


	bool search_for_seat_and_get_status_from_list( std::list<Seat> from_list, int rowNum, int seatNum ) const {
		Node* current = head;
		try {
			if ( current->getRow() == rowNum && current->getSeat() == seatNum ) {
				//Then the first node is the one the user is looking for.
				//Return TRUE if it is RESERVED
				if ( current->isReserved() == true )
					return true;
				//Return FALSE if it is NOT RESERVED
				if ( current->isReserved() == false )
					return false;
			} else {
				//Cycle through the list.
				while ( current != nullptr ) {
					current = current->getNext();

					//Continue checking each node in the list.
					if ( current->getRow() == rowNum && current->getSeat() == seatNum ) {
						if ( current->isReserved() == true )
							return true;
						if ( current->isReserved() == false )
							return false;
					}
				}
			}
			//If the node still has not been found, then it probably isn't in the list.
			//Throw an exception
			throw NodeNotFoundException();
		} catch ( NodeNotFoundException& e ) {
			e.what();
			return true;
		}

	}

	Seat* search_for_and_get_seat_from_list( int rowNum, int seatNum ) {
		Node* current = head;
		Node* seek = nullptr;

		try {
			if ( current->getRow() == rowNum && current->getSeat() == seatNum ) {
				seek = current;
				return seek;
			} else {
				//Cycle through the list.
				while ( current != nullptr ) {
					current = current->getNext();

					//Continue checking each node in the list.
					if ( current->getRow() == rowNum && current->getSeat() == seatNum ) {
						seek = current;
						return seek;
					}
				}
			}
			//If the node still has not been found, then it probably isn't in the list.
			//Throw an exception
			throw NodeNotFoundException();
		} catch ( NodeNotFoundException& e ) {
			e.what();
			return nullptr;
		}
	}

	void reserve_a_seat( Auditorium* corresponding, int rowNum, int seatNum ) {
		std::string str;
		char userChar;

		if ( searchForNodeAndGetStatus( rowNum, seatNum ) == true )
			throw UnableToReserveASeatException();
		else {
			//Then the seat is available.
			std::cout << "The seat you have chosen is available!\n";
			std::cout << "Would you like to reserve it? (\"Y\" or \"N\")\n";
			userChar = validateStringAsCharacter( str, 'Y', 'N' );

			if ( toupper( userChar ) == 'Y' ) {
				std::cout << "I will reserve the seat for you.\n";
				searchForAndGetNode( rowNum, seatNum )->setReserved( true );
				std::cout << "The seat is now reserved!\n";
				corresponding->setNumSeatsReserved( corresponding->getNumSeatsReserved() + 1 );
				corresponding->setNumSeatsOpen( corresponding->getNumSeatsOpen() - 1 );

			} else if ( toupper( userChar ) == 'N' )
				std::cout << "The seat will not be reserved.\n";
		}
	}

	void reserve_a_seat_without_input( Auditorium* corresponding, int rowNum, int seatNum ) {
		if ( searchForNodeAndGetStatus( rowNum, seatNum ) == true )
			throw UnableToReserveASeatException();
		else {
			searchForAndGetNode( rowNum, seatNum )->setReserved( true );
			corresponding->setNumSeatsReserved( corresponding->getNumSeatsReserved() + 1 );
			corresponding->setNumSeatsOpen( corresponding->getNumSeatsOpen() - 1 );
		}
	}

	void display_list_as_auditorium( Auditorium* corresponding ) const {
		Node* current = head;

		const short WIDTH = corresponding->getNumSeats();
		const short HEIGHT = corresponding->getNumRows();
		short h;
		short w;

		std::cout << "  ";
		for ( short i = 1; i <= WIDTH; i++ ) {
			if ( i > 9 )
				std::cout << ( i - 10 );
			else
				std::cout << i;
		}
		std::cout << '\n';

		h = 1;
		while ( h <= HEIGHT ) {
			//As long as the current node and the next node have the same row number,
			//This is the same line
			std::cout << h << ' ';
			w = 1;
			while ( w <= WIDTH ) {
				if ( current->isReserved() )
					std::cout << '*';
				if ( !current->isReserved() )
					std::cout << '#';
				current = current->getNext();
				w++;
			}
			//Otherwise, print a newline
			std::cout << '\n';
			h++;
		}
	}

	void write_to_file( std::fstream* file, Auditorium* corresponding ) const {
		Node* current = head;

		const short WIDTH = corresponding->getNumSeats();
		const short HEIGHT = corresponding->getNumRows();
		short h = 1;
		short w = 1;

		file->clear();

		while ( h <= HEIGHT ) {
			w = 1;
			while ( w <= WIDTH ) {
				if ( current->isReserved() )
					*file << '*';
				if ( !current->isReserved() )
					*file << '#';
				current = current->getNext();
				w++;
			}
			//eliminate extra newline.
			if ( w == WIDTH + 1 && h < HEIGHT ) {
				//Otherwise, print a newline
				*file << '\n';
			}
			h++;
		}
	}
*/
    // Validation Functions ///////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////

	short int validate_string_as_single_digit_integer_in_range( std::string buffer, short int min, short int max ) {
		std::string::size_type sz = 0;
		bool is_valid = false;
		short int user_short = 0;

		do {
			try {
				std::cin >> buffer;

				if ( buffer.length() > 1 ) {
					throw InvalidStringLengthException();
				}

				if ( !isdigit( buffer.at( 0 ) ) ) {
					throw InvalidCharacterInputException();
				}

				for ( std::size_t i = 0; i < buffer.length(); ++i ) {
					if ( !isdigit( buffer.at( i ) ) ) {
						throw InvalidCharacterInputException();
					}
				}

				//Now, convert the string to an integer, store it in user_short
				//Then, check that the value is within the expected range
				user_short = std::stoi( buffer, &sz );

				if ( user_short < min || user_short > max ) {
					throw IntegerOutOfRangeException();
				}
				//If no exception has been thrown by this point, then the input is valid.
				is_valid = true;
			} catch ( InvalidStringLengthException& e ) {
				is_valid = false;
                std::cerr << e.what() << std::endl;
			} catch ( InvalidCharacterInputException& e ) {
				is_valid = false;
                std::cerr << e.what() << std::endl;
			} catch ( IntegerOutOfRangeException& e ) {
				is_valid = false;
                std::cerr << e.what() << std::endl;
			}
		} while ( !is_valid );

		return user_short;
	}

	short int validate_string_as_double_digit_integer_in_range( std::string buffer, short int min, short int max ) {
		std::string::size_type sz = 0;
		bool is_valid = false;
		short int user_short = 0;

		do {
			try {
				std::cin >> buffer;

				if ( buffer.length() > 2 ) {
					throw InvalidStringLengthException();
				}

				if ( !isdigit( buffer.at( 0 ) ) ) {
					throw InvalidCharacterInputException();
				}

				for ( std::size_t i = 0; i < buffer.length(); ++i ) {
					if ( !isdigit( buffer.at( i ) ) ) {
						throw InvalidCharacterInputException();
					}
				}

				//Now, convert the string to an integer, store it in userShort
				//Then, check that the value is within the expected range
				user_short = std::stoi( buffer, &sz );

				if ( user_short < min || user_short > max ) {
					throw IntegerOutOfRangeException();
				}
				//If no exception has been thrown by this point, then the input is valid.
				is_valid = true;
			} catch ( InvalidStringLengthException& e ) {
				is_valid = false;
                std::cout << e.what() << std::endl;
			} catch ( InvalidCharacterInputException& e ) {
				is_valid = false;
                std::cout << e.what() << std::endl;
			} catch ( IntegerOutOfRangeException& e ) {
				is_valid = false;
                std::cout << e.what() << std::endl;
			}
		} while (!is_valid);

		return user_short;
	}

	char validate_string_as_character(std::string buffer, char upper_case_character) {
		bool is_valid = false;
		char user_char = '\n';

		do {
			try {
				std::cin >> buffer;

				if ( buffer.length() > 1 ) {
					throw InvalidStringLengthException();
				}

				//Now, convert the string to an integer, store it in userShort
				//Then, check that the value is within the expected range
				user_char = buffer.at(0);

				if ( toupper( user_char ) == upper_case_character ) {
					is_valid = true;
				} else {
					throw InvalidCharacterInputException();
				}

			} catch ( InvalidStringLengthException& e ) {
				is_valid = false;
                std::cout << e.what() << std::endl;
			} catch ( InvalidCharacterInputException& e ) {
				is_valid = false;
                std::cout << e.what() << std::endl;
			}
		} while (!is_valid);

		return toupper(user_char);
	}

	bool yes_or_no_prompt( std::string prompt ) {
		char answer = 'a';

		do {
			std::cout << prompt << std::endl;
			std::cin >> answer;

			answer = toupper(answer);

			if ( answer != 'Y' && answer != 'N' ) {
				std::cout << "Please try again!" << std::endl;
			}
		} while ( answer != 'Y' && answer != 'N' );

		return (answer == 'Y');
	}

} /* namespace whowell */
