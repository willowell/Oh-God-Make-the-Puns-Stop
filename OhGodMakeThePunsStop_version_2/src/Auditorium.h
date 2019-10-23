/*
 * Auditorium.h
 *
 *  Created on: Oct. 7, 2019
 *      Author: whowell
 */

#ifndef AUDITORIUM_H_
#define AUDITORIUM_H_

#include <list>

#include "Seat.h"

namespace whowell {

class Auditorium {
	private:
		static const int ticket_price = 7;
		int auditorium_id;
		int num_seats; //(Seats per row)
		int num_rows;
		int num_seats_open;
		int num_seats_reserved;
		int sales;

		std::list<Seat> seat_list;

	public:
		Auditorium();
		virtual ~Auditorium();

		int get_auditorium_id()      const;
		int get_num_seats()          const;
		int get_num_rows()           const;
		int get_num_seats_open()     const;
		int get_num_seats_reserved() const;
		int get_sales()              const;

		void set_auditorium_id(      int i );
		void set_num_seats(          int s );
		void set_num_rows(           int r );
		void set_num_seats_open(     int s );
		void set_num_seats_reserved( int s );
		void set_sales(              int s );

		void load_from_file( std::fstream from_file );
		Seat& search_for_seat( int row_num, int seat_num );
		bool search_for_seat_and_get_status( int row_num, int seat_num ) const;

		void display() const;
		void display_list() const;
};

} /* namespace whowell */

#endif /* AUDITORIUM_H_ */
