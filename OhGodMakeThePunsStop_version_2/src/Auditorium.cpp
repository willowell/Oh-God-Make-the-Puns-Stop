/*
 * Auditorium.cpp
 *
 *  Created on: Oct. 7, 2019
 *      Author: whowell
 */

#include <algorithm>
#include <iostream>
#include <list>
#include <sstream>
#include <string>

#include <boost/format.hpp>

#include "Auditorium.h"
#include "Utilities.h"

namespace whowell {

Auditorium :: Auditorium():
	auditorium_id(0),
	num_seats(0),
	num_rows(0),
	num_seats_open(0),
	num_seats_reserved(0),
	sales(0)
{}

Auditorium :: ~Auditorium() {}

int Auditorium :: get_auditorium_id()      const { return auditorium_id;       }
int Auditorium :: get_num_seats()          const { return num_seats;           }
int Auditorium :: get_num_rows()           const { return num_rows;            }
int Auditorium :: get_num_seats_open()     const { return num_seats_open;      }
int Auditorium :: get_num_seats_reserved() const { return num_seats_reserved;  }
int Auditorium :: get_sales()              const { return sales;               }

void Auditorium :: set_auditorium_id(      int i ) { auditorium_id = i;        }
void Auditorium :: set_num_seats(          int s ) { num_seats = s;            }
void Auditorium :: set_num_rows(           int r ) { num_rows = r;             }
void Auditorium :: set_num_seats_open(     int s ) { num_seats_open = s;       }
void Auditorium :: set_num_seats_reserved( int s ) { num_seats_reserved = s;   }
void Auditorium :: set_sales(              int s ) { sales = s;                }

void Auditorium :: load_from_file( std::fstream from_file) {

			std::string input_line;
			short open_seats = 0;
			short res_seats = 0;
			short i = 0;

			//Clear any altered bits, ensure the file is good before doing anything with it.
			from_file.clear();

			while ( std::getline(from_file, input_line) ) {
				//currentString now contains the contents of one row.
				//Tell the Auditorium how many rows we have encountered.
				//The number of columns in the auditorium needs to be set only once
				if ( i == 0 ) {
					num_seats = input_line.length() - 1;
				}

				i++;
				num_rows = i;

				/* Examine the individual row. */
				for ( short j = 1; j <= num_seats; j++ ) {
					if ( input_line.at( j ) == '*' ) { //RESERVED SEAT
						//CREATE NEW NODE WITH ROW NUM (i), SEAT NUM (j), and TRUE (RESERVED)
						seat_list.push_back(Seat(i, j, true));
						res_seats++;
					} else if ( input_line.at( j ) == '#' ) { //EMPTY SEAT
						//CREATE NEW NODE WITH ROW NUM (i), SEAT NUM (j), and FALSE (NOT RESERVED)
						seat_list.push_back(Seat(i, j, false));
						open_seats++;
					}
				}
			} //end while (!file->eof())

			num_seats_reserved = res_seats;
			num_seats_open = open_seats;

			//List is now loaded and Auditorium contains numRows, numSeats, numSeatsReserved, and numSeatsOpen
			//Under this algorithm, the list will automatically be sorted such that ROW ONE SEATS
			//come BEFORE ROW TWO SEATS, etc.
		} //close push method

Seat& Auditorium :: search_for_seat( int row_num, int seat_num ) {

		Seat query(row_num, seat_num, false);
		try {

			std::list<Seat>::iterator find_iter = std::find(seat_list.begin(), seat_list.end(), query);

			if (find_iter != seat_list.end()) {
				return *find_iter;
			}

			//If the node still has not been found, then it probably isn't in the list.
			//Throw an exception
			throw NodeNotFoundException();
		} catch ( NodeNotFoundException& e ) {
			e.what();
			return nullptr;
		}
	}

bool Auditorium :: search_for_seat_and_get_status(int row_num, int seat_num ) const {
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

void Auditorium :: display() const {
	std::cout << "Auditorium Info:\n"
			  << "\tID Number: " << auditorium_id << '\n'
			  << "\tNumber of Seats in Each Row: " << num_seats << '\n'
			  << "\tNumber of Rows: " << num_rows << '\n'
			  << "\tNumber of Seats Open: " << num_seats_open << '\n'
			  << "\tNumber of Seats Reserved " << num_seats_reserved << '\n'
			  << "\tSales: " << sales << '\n' << std::endl;
}

void Auditorium :: display_list() const {
	std::cout << "List contents:" << std::endl;

	if (seat_list.empty()) {
		std::cout << "List is empty!" << std::endl;
	} else {
		for (auto const& seat : seat_list) {
			seat.display();
		}
		std::cout << "End of list." << std::endl;
	}
}

} /* namespace whowell */
