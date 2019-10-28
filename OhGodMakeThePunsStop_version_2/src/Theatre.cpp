/*
 * Theatre.cpp
 *
 *  Created on: Oct. 7, 2019
 *      Author: whowell
 */

#include <iostream>

#include "Theatre.h"

namespace whowell {

Theatre :: Theatre():
		total_seats(0),
		total_seats_open(0),
		total_seats_reserved(0),
		total_sales(0),
		user_seats(0),
		user_sale(0)
{}

Theatre :: ~Theatre() {}

void Theatre :: set_total_seats(          int seats ) { total_seats          = seats; }
void Theatre :: set_total_seats_open(     int seats ) { total_seats_open     = seats; }
void Theatre :: set_total_seats_reserved( int seats ) { total_seats_reserved = seats; }
void Theatre :: set_user_seats(           int seats ) { user_seats           = seats; }

void Theatre :: calculate_total_sales() {
	total_sales = ( total_seats_reserved * ticket_price );
	user_sale   = ( user_seats           * ticket_price );
}

void Theatre :: display() {

	calculate_total_sales();
	std::cout << "Ticket Report for Theater:\n"
			  << "Total Seats: " << total_seats << '\n'
			  << "Total Seats Open: " << total_seats_open << '\n'
			  << "Total Seats Reserved: " << total_seats_reserved << '\n';
	printf( "Total sales from theater: $%.2f\n\n", total_sales);

	std::cout << "Tickets purchased this session:\n"
		      << "Tickets purchased: " << user_seats << '\n';
	printf( "Sales from user purchase: $%.2f\n\n", user_sale);
}

} /* namespace whowell */
