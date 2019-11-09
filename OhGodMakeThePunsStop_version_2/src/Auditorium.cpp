/*
 * Auditorium.cpp
 *
 *  Created on: Oct. 7, 2019
 *      Author: whowell
 */

#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <list>
#include <string>

#include <boost/format.hpp>

#include "Auditorium.h"
#include "Exceptions.h"
#include "Seat.h"
#include "Utilities.h"

namespace whowell {

Auditorium :: Auditorium():
	auditorium_id(0),
	num_seats(0),
	num_rows(0),
	total_seats(0),
	num_seats_open(0),
	num_seats_reserved(0)
{}

Auditorium :: ~Auditorium() {}

int Auditorium :: get_auditorium_id()      const { return auditorium_id;       }
int Auditorium :: get_num_seats()          const { return num_seats;           }
int Auditorium :: get_num_rows()           const { return num_rows;            }
int Auditorium :: get_total_seats()        const { return total_seats;         }
int Auditorium :: get_num_seats_open()     const { return num_seats_open;      }
int Auditorium :: get_num_seats_reserved() const { return num_seats_reserved;  }

void Auditorium :: set_auditorium_id(      int i ) { auditorium_id = i;                  }
void Auditorium :: set_num_seats(          int s ) { num_seats = s;                      }
void Auditorium :: set_num_rows(           int r ) { num_rows = r;                       }
void Auditorium :: set_total_seats(              ) { total_seats = num_seats * num_rows; }
void Auditorium :: set_num_seats_open(     int s ) { num_seats_open = s;                 }
void Auditorium :: set_num_seats_reserved( int s ) { num_seats_reserved = s;             }

void Auditorium :: load_from_file( std::fstream& from_file ) {

			std::string input_line;
			short open_seats = 0;
			short res_seats = 0;
			short i = 0;

			//Clear any altered bits, ensure the file is good before doing anything with it.
			from_file.clear();

			while ( std::getline( from_file, input_line ) ) {
				//currentString now contains the contents of one row.
				//Tell the Auditorium how many rows we have encountered.
				//The number of columns in the auditorium needs to be set only once
				if ( i == 0 ) {
					num_seats = input_line.length();
				}

				i++;
				num_rows = i;

				/* Examine the individual row. */
				for ( short j = 0; j < num_seats; ++j ) {
					if ( input_line.at( j ) == '*' ) { //RESERVED SEAT
						//CREATE NEW NODE WITH ROW NUM (i), SEAT NUM (j), and TRUE (RESERVED)
						seat_list.push_back( Seat( i, j, true ) );
						res_seats++;
					} else if ( input_line.at( j ) == '#' ) { //EMPTY SEAT
						//CREATE NEW NODE WITH ROW NUM (i), SEAT NUM (j), and FALSE (NOT RESERVED)
						seat_list.push_back( Seat( i, j, false ) );
						open_seats++;
					}
				}
			} //end while (!file->eof())

			num_seats_reserved = res_seats;
			num_seats_open = open_seats;
			set_total_seats();

			//List is now loaded and Auditorium contains numRows, numSeats, numSeatsReserved, and numSeatsOpen
			//Under this algorithm, the list will automatically be sorted such that ROW ONE SEATS
			//come BEFORE ROW TWO SEATS, etc.
		} //close push method

void Auditorium :: write_to_file( std::fstream& to_file ) {
	// Set the iterator to the start of the list.
	// The older project used a doubly linked list
	// with raw pointers.

	// As a predicate, the list must not be empty.
	if ( seat_list.empty() ) {
		std::cerr << "List is empty!" << std::endl;
		return;
	}

	std::list<Seat>::iterator iter = seat_list.begin();

	// both of these are for making the grid of #'s and *'s
	short int y = 0;
	short int x = 0;

	to_file.clear();

	while ( y < num_rows ) {
		x = 0;
		while ( x < num_seats ) {
			// Get the status of the seat and print the correcponding
			// character. Then, move the iterator, and increment x.
			iter->is_seat_reserved() ? to_file << '*' : to_file << '#';
			iter++;
			x++;
		}

		// Terminate the line with a newline,
		// and increment y and move to the next line.
		// Skip the newline if this is the last line.
		// This will not run on the last cycle of the loop.
		// Incrementing y before the test ensures that y == 10
		// on the last cycle. So, this part runs from 1 to 9
		// rather than from 0 to 9 as in the inner loop.
		// In the original version, the loop condition was y <= num_rows.
		y++;
		if ( y < num_rows ) {
			to_file << '\n';
		}
	}
}

Seat* Auditorium :: search_for_seat( short int row_num, short int seat_num ) {

		Seat query( row_num, seat_num, false );
		try {

			std::list<Seat>::iterator find_iter = std::find( seat_list.begin(), seat_list.end(), query );

			if ( find_iter != seat_list.end() ) {
				Seat* found = &( *find_iter );
				return found;
			}

			//If the node still has not been found, then it probably isn't in the list.
			//Throw an exception
			throw NodeNotFoundException();
		} catch ( NodeNotFoundException& e ) {
			e.what();
			return nullptr;
		}
	}

/**
 * Returns false if seat is available
 * Returns true is seat is unavailable or cannot be found.
 */
bool Auditorium :: is_seat_already_reserved( short int row_num, short int seat_num ) {
		Seat query( row_num, seat_num, false );

		try {

			std::list<Seat>::iterator find_iter = std::find( seat_list.begin(), seat_list.end(), query );

			if ( find_iter != seat_list.end() ) {
				return find_iter->is_seat_reserved();
			}

			//If the node still has not been found, then it probably isn't in the list.
			//Throw an exception
			throw NodeNotFoundException();
		} catch ( NodeNotFoundException& e ) {
			e.what();
			return true;
		}

	}

void Auditorium :: reserve_seat( short int row_num, short int seat_num ) throw ( UnableToReserveASeatException ) {
	std::string buffer;
	bool user_wants_to_reserve_seat = false;

	if ( is_seat_already_reserved( row_num, seat_num ) ) {
			throw UnableToReserveASeatException();
	} else {
		user_wants_to_reserve_seat = yes_or_no_prompt(
				"The seat is available!\nWould you like to reserve it? [y/n]"
		);

		if ( user_wants_to_reserve_seat ) {
			std::cout << "Reserving the seat..." << std::endl;
			search_for_seat( row_num, seat_num )->set_reserved( true );
			std::cout << "The seat is now reserved!" << std::endl;
			num_seats_reserved++;
			num_seats_open--;
		} else {
			std::cout << "The seat will not be reserved." << std::endl;
		}
	}
}

void Auditorium :: reserve_seat_without_input( short int row_num, short int seat_num ) throw ( UnableToReserveASeatException ) {
	if ( is_seat_already_reserved( row_num, seat_num ) ) {
		throw UnableToReserveASeatException();
	} else {
		search_for_seat( row_num, seat_num )->set_reserved( true );
		num_seats_reserved++;
		num_seats_open--;
	}
}

/**
 * I realized investing this much time in a function that deals with
 * edge-cases is probably a bad idea. I have decided to simply log the
 * special request instead. This function might be better suited if this
 * program was aware of multiple days; then this function could search through
 * the other available days for the seats.
 */

/**
 * Uses @param num_of_tickets to find a corresponding free number of seats in
 * an auditorium on a per-row basis. For example, if num of tickets is less than
 * the number of seats per row, this function will find a row with that many
 * seats free. If num of tickets is greater than the number of seats per row,
 * this function will find more than one row, and so on.
 *
 * This is an exceptional function and is only called when manual reservation fails.
 *
 * In the old project, this is performReservationsWithVectors, which had an
 * elaborate algorithm for choosing seats to reserve.
 */
void Auditorium :: perform_automatic_reservation( short int num_of_tickets ) {
/*
 * void performReservationsWithVectors( std::list<Seat>* list, Auditorium* auditorium,
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
 */
}

void Auditorium :: reset_auditorium() {
	// As a predicate, the list must not be empty.
	if ( seat_list.empty() ) {
		std::cerr << "List is empty!" << std::endl;
		return;
	}

	//TODO: correct way to mutate values?
	for ( auto& seat : seat_list ) {
		seat.set_reserved( false );
	}
}

void Auditorium :: display() const {
	std::cout << "Auditorium Info:\n"
			  << "\tID Number: " << auditorium_id << '\n'
			  << "\tTotal Number of Seats: " << total_seats << '\n'
			  << "\tNumber of Seats in Each Row: " << num_seats << '\n'
			  << "\tNumber of Rows: " << num_rows << '\n'
			  << "\tNumber of Seats Open: " << num_seats_open << '\n'
			  << "\tNumber of Seats Reserved " << num_seats_reserved << '\n'
			  << '\n' << std::endl;
}

void Auditorium :: display_list() const {
	std::cout << "List contents:" << std::endl;

	if ( seat_list.empty() ) {
		std::cerr << "List is empty!" << std::endl;
	} else {
		for ( auto const& seat : seat_list ) {
			seat.display();
		}
		std::cout << "End of list." << std::endl;
	}
}

void Auditorium :: display_grid() {
	// Set the iterator to the start of the list.
	// The older project used a doubly linked list
	// with raw pointers.

	// As a predicate, the list must not be empty.
	if ( seat_list.empty() ) {
		std::cerr << "List is empty!" << std::endl;
		return;
	}

	// This function would be readonly, but for some reason,
	// marking this function as readonly causes the program to expect
	// this iterator to be const,
	// which then means it cannot be moved across the list.
	std::list<Seat>::iterator iter = seat_list.begin();

	// both of these are for making the grid of #'s and *'s
	short int y = 0;
	short int x = 0;

	// Create padding for the top line of numbers
	// output:  Auditorium [ID Number]
	//          __12345...
	//          1 #####
	//          2 *****
	//          3 #####
	//          4 *****
	//          5 #####
	//          .
	//          .
	//          .

	// Print the auditorium's ID number
	std::cout << "Auditorium ID: " << auditorium_id << std::endl;

	// First two spaces for the top left corner
	std::cout << "  ";
	// Use num_seats to print the top line of numbers
	for (short int i = 0; i < num_seats; ++i) {
		std::cout << i;
	}
	std::cout << std::endl;

	// Iterate through the rest of the grid.
	// First, print the row number, then a space,
	// and then the actual seats.
	while ( y < num_rows ) {

		// This statement generates the line of numbers along the left side
		std::cout << y << ' ';

		// This inner loop prints out the actual seats using the iterator.
		// Reset x with each iteration of this inner loop.
		x = 0;
		while ( x < num_seats ) {
			// Get the status of the seat and print the correcponding
			// character. Then, move the iterator, and increment x.
			iter->is_seat_reserved() ? std::cout << '*' : std::cout << '#';
			iter++;
			x++;
		}

		// End the line, and increment y for the next number
		// for the start of the next line
		std::cout << std::endl;
		y++;
	}
}

} /* namespace whowell */
