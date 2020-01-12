/*
 * Theatre.h
 *
 *  Created on: Oct. 7, 2019
 *      Author: Whowell
 */

#ifndef OHGODMAKETHEPUNSSTOP_VERSION_2_THEATRE_H
#define OHGODMAKETHEPUNSSTOP_VERSION_2_THEATRE_H

#include <fstream>

namespace Whowell {
	
	class Theatre {
	private:
		static constexpr float ticket_price = 7.99;
		
		int total_seats;
		int total_seats_open;
		int total_seats_reserved;
		float total_sales;
		int user_seats;
		float user_sale;
	public:
		Theatre();
		
		virtual ~Theatre();
		
		void set_total_seats(int seats);
		
		void set_total_seats_open(int seats);
		
		void set_total_seats_reserved(int seats);
		
		void set_user_seats(int seats);
		
		void display();
		
		void view_sales_report();
		
		void calculate_total_sales();
		
		void save_sales_report(std::fstream & to_file);
	};
	
} /* namespace Whowell */

#endif /*OHGODMAKETHEPUNSSTOP_VERSION_2_THEATRE_H*/
