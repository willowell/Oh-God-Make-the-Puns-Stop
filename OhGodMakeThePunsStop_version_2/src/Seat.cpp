/*
 * Seat.cpp
 *
 *  Created on: Oct. 7, 2019
 *      Author: whowell
 */

#include <iostream>

#include "Seat.h"

namespace whowell {

Seat :: Seat():
	row(0),
	column(0),
	is_reserved(false)
{}

Seat :: Seat( int row_num, int column_num, bool seat_state ):
	row(row_num),
	column(column_num),
	is_reserved(seat_state)
{}

Seat :: ~Seat() {}

int Seat :: get_row()           const { return row;         }
int Seat :: get_column()        const { return column;      }
bool Seat :: is_seat_reserved() const { return is_reserved; }

void Seat :: set_row(      int row_num      ) { row = row_num;            }
void Seat :: set_column(   int column_num   ) { column = column_num;      }
void Seat :: set_reserved( bool seat_state  ) { is_reserved = seat_state; }

//For debug/tracking
void Seat :: display() const {
	std::cout << "Seat Info:"
			  << '\t' << "Row: "      << row
			  << '\t' << "Column: "   << column
			  << '\t' << "Reserved? " << (is_reserved ? "yes" : "no")
			  << std::endl;
}

} /* namespace whowell */
