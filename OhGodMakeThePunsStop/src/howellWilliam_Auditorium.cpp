#include "howellWilliam_Auditorium.h"

#include <iostream>


using namespace whowell_OhGodMakeThePunsStop;

Auditorium :: Auditorium() {
	numSeats = numRows = numSeatsOpen = numSeatsReserved = sales = 0;
}

Auditorium :: ~Auditorium() {}

int Auditorium :: getNumSeats()         const { return numSeats;         }
int Auditorium :: getNumRows()          const { return numRows;          }
int Auditorium :: getNumSeatsOpen()     const { return numSeatsOpen;     }
int Auditorium :: getNumSeatsReserved() const { return numSeatsReserved; }
int Auditorium :: getSales()            const { return sales;            }

void Auditorium :: setNumSeats(         int s ) { numSeats = s;          }
void Auditorium :: setNumRows(          int r ) { numRows = r;           }
void Auditorium :: setNumSeatsOpen(     int s ) { numSeatsOpen = s;      }
void Auditorium :: setNumSeatsReserved( int s ) { numSeatsReserved = s;  }
void Auditorium :: setSales(            int s ) { sales = s;             }

void Auditorium :: display() const {
	std::cout << "Auditorium Info:\n"
			  << "\tNumber of Seats in Each Row: " << numSeats << '\n'
			  << "\tNumber of Rows: " << numRows << '\n'
			  << "\tNumber of Seats Open: " << numSeatsOpen << '\n'
			  << "\tNumber of Seats Reserved " << numSeatsReserved << '\n'
			  << "\tSales: " << sales << '\n' << '\n';
}

