/*
 * Auditorium.h
 *
 *  Created on: Oct. 7, 2019
 *      Author: whowell
 */

#ifndef AUDITORIUM_H_
#define AUDITORIUM_H_

#include "Exceptions.h"
#include "Seat.h"

namespace whowell {

class Auditorium {
	private:
		int auditorium_id;
		int num_seats; //(Seats per row)
		int num_rows;
		int total_seats;
		int num_seats_open;
		int num_seats_reserved;

		std::list<Seat> seat_list;

	public:
		Auditorium();
		virtual ~Auditorium();

		int get_auditorium_id()      const;
		int get_num_seats()          const;
		int get_num_rows()           const;
		int get_total_seats()        const;
		int get_num_seats_open()     const;
		int get_num_seats_reserved() const;

		void set_auditorium_id(      int i );
		void set_num_seats(          int s );
		void set_num_rows(           int r );
		void set_total_seats(              );
		void set_num_seats_open(     int s );
		void set_num_seats_reserved( int s );

		void load_from_file(           std::fstream& from_file   );
		void write_to_file(            std::fstream& to_file     );
		Seat* search_for_seat(         short int row_num, short int seat_num );
		bool is_seat_already_reserved( short int row_num, short int seat_num );

		void reserve_seat(                  short int row_num, short int seat_num ) throw( UnableToReserveASeatException );
		void reserve_seat_without_input(    short int row_num, short int seat_num ) throw( UnableToReserveASeatException );
		void perform_automatic_reservation( short int num_of_tickets  );

		void reset_auditorium();


		void display()                                             const;
		void display_list()                                        const;
		void display_grid();
};

} /* namespace whowell */

#endif /* AUDITORIUM_H_ */
