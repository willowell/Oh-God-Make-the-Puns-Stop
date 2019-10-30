#include "howellWilliam_Theater.h"

#include <iostream>


using namespace whowell_OhGodMakeThePunsStop;

Theater :: Theater() { totalSeatsOpen = totalSeatsReserved = totalSales = userSeats = userSale = 0; }

Theater :: ~Theater() {}

void Theater :: setTotalSeatsOpen(     int s ) { totalSeatsOpen = s; }
void Theater :: setTotalSeatsReserved( int s ) { totalSeatsReserved = s; }
void Theater :: setUserSeats(          int s ) { userSeats = s; }

void Theater :: calcTotalSales() {
	totalSales = ( totalSeatsReserved * TICKET_PRICE );
	userSale = ( userSeats * TICKET_PRICE );
}

void Theater :: display() {

	calcTotalSales();
	std::cout << "Ticket Report for Theater:\n"
			  << "Total Seats Open: " << totalSeatsOpen << '\n'
			  << "Total Seats Reserved: " << totalSeatsReserved << '\n';
	printf( "Total sales from theater: $%.2f\n\n", static_cast< float >( totalSales ) );

	std::cout << "Tickets purchased this session:\n"
		      << "Tickets purchased: " << userSeats << '\n';
	printf( "Sales from user purchase: $%.2f\n\n", static_cast< float >( userSale ) );
}
