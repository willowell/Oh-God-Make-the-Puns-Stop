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

/**
 * Display is a debug method.
 */
void Theatre :: display() {

	calculate_total_sales();
	std::cout << "Sales report for theatre:\n"
			  << "Total seats in theatre: "          << total_seats << '\n'
			  << "Total seats open: "                << total_seats_open << '\n'
			  << "Total seats reserved: "            << total_seats_reserved << '\n'
			  << "Total sales  from theatre: "       << total_sales
			  << std::endl;

	std::cout << "Tickets purchased this session:\n"
		      << "Tickets purchased: "               << user_seats << '\n'
			  << "User sale from this session: "     << user_sale
			  << std::endl;
}

void Theatre :: view_sales_report() {
	calculate_total_sales();
	std::cout << "Sales report for theatre:\n"
			  << "Total seats in theatre: "          << total_seats << '\n'
			  << "Total seats open: "                << total_seats_open << '\n'
			  << "Total seats reserved: "            << total_seats_reserved << '\n'
			  << "Total sales  from theatre: "       << total_sales
			  << std::endl;

	std::cout << "Tickets purchased this session:\n"
		      << "Tickets purchased: "               << user_seats << '\n'
			  << "User sale from this session: "     << user_sale
			  << std::endl;
}

} /* namespace whowell */
