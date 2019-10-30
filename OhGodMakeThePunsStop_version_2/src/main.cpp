//============================================================================
// Name        : OhGodMakeThePunsStop_version_2.cpp
// Author      : wphowell
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <chrono>
#include <exception>
#include <fstream>
#include <iostream>
#include <list>
#include <memory>
#include <string>
#include <thread>
#include <vector>

#include <boost/format.hpp>

#include "Auditorium.h"
#include "Seat.h"
#include "Theatre.h"
#include "Utilities.h"


namespace whowell {

	bool is_debug = true;

	std::fstream      file_1;
	std::fstream      file_2;
	std::fstream      file_3;
	Auditorium        auditorium_1;
	Auditorium        auditorium_2;
	Auditorium        auditorium_3;
	Theatre           theatre;

	/// User input

	short int user_short = 0;
	short int user_selected_tickets = 0;
	short int user_choice = 0;
	int pause_time_ms = 250;
	char user_char = 'a';
	bool user_wants_manual_reservation = false;
	bool user_wants_to_quit = false;
	bool is_password_good = false;
	std::string buffer;
	std::string key = "admin";
	std::vector < short int > user_selected_seats;
	std::vector < short int > user_selected_rows;

	void pause_thread(int for_milliseconds) {
		std::this_thread::sleep_for( std::chrono::milliseconds( for_milliseconds ) );
	}

	void return_to_main_menu() {
		std::cout << "Returning to the main menu." << std::endl;
		// Wait a little bit before returning to the main menu.
		pause_thread( pause_time_ms );
	}

	void handle_main_menu() {
    	user_short = -1;
    	user_choice = -1;

    	std::cout << "Please enter a number corresponding to a menu item.\n"
    			  << "(1) View an auditorium.\n"
				  << "(2) Make a reservation.\n"
				  << "(3) Advanced options.\n"
				  << "(4) Save and quit."
    			  << std::endl;

    	user_short = validate_string_as_single_digit_integer_in_range( buffer, 1, 4 );
    	user_choice = user_short;

    	// Wait a little bit after accepting user input to show the next menu.
    	pause_thread( pause_time_ms );
	}

	void handle_auditorium_display_menu() {
			user_short = -1;

			std::cout << "Please enter the number of the auditorium you wish to view.\n"
					  << "You can choose Auditorium (1), (2), or (3).\n"
					  << std::endl;

			user_short = validate_string_as_single_digit_integer_in_range( buffer, 1, 3 );

			// Wait a little bit after accepting user input to show an auditorium.
			pause_thread( pause_time_ms );

			switch ( user_short ) {
				case 1: {
					auditorium_1.display_grid();
					break;
				}
				case 2: {
					auditorium_2.display_grid();
					break;
				}
				case 3: {
					auditorium_3.display_grid();
					break;
				}
				default: {
					std::cerr << "This should be unreachable!\n"
							  << "(short int) user_short is " << user_short
							  << std::endl;
					break;
				}
			}
		}

	void handle_reservation_menu() {
		user_short = -1;
		user_wants_manual_reservation = false;

		std::cout << "Please enter the number of the auditorium you wish to view.\n"
				  << "You can choose Auditorium (1), (2), or (3).\n"
				  << std::endl;

		user_short = validate_string_as_single_digit_integer_in_range( buffer, 1, 3 );

		// Wait a little bit after accepting user input to show an auditorium.
		pause_thread( pause_time_ms );

		switch ( user_short ) {
			case 1: {
				auditorium_1.display_grid();
				break;
			}
			case 2: {
				auditorium_2.display_grid();
				break;
			}
			case 3: {
				auditorium_3.display_grid();
				break;
			}
			default: {
				std::cerr << "This should be unreachable!\n"
						  << "(short int) user_short is " << user_short
						  << std::endl;
				break;
			}
		}
		std::cout << std::endl;

		std::cout << "Please enter the number of tickets you wish to purchase."
				  << std::endl;

		user_selected_tickets = validate_string_as_double_digit_integer_in_range( buffer, 1, 100 );

		// Wait a little bit before showing the next prompt.
		pause_thread( pause_time_ms );

		user_wants_manual_reservation = yes_or_no_prompt(
				"Would you like to manually reserve the seats? [y/n]\n"
				"Otherwise, the program will automatically find available seats for you.\n"
		);

		short int loop_limit = user_selected_tickets;

		// For every ticket the user wants, set aside a slot for a seat.
		for ( short int i = 0; i < loop_limit; ++i ) {
			user_selected_rows.push_back( i );
			user_selected_seats.push_back( i );
		}

		if ( user_wants_manual_reservation ) {
			// The vectors are now big enough to store the user's desired seats.
			// Request values for the seat positions.
			for (short int k = 0; k < loop_limit; k++) {
				std::cout << "Please enter the row number for the "
						  << boost::format("%1% seat that you want to purchase.")
						  % ( k + 1 )
						  << std::endl;
				user_selected_rows[ k ] = validate_string_as_double_digit_integer_in_range( buffer, 1, 100 );

				std::cout << "Please enter the seat number for the "
						  << boost::format("%1% seat that you want to purchase.")
						  % ( k + 1 )
						  << std::endl;
				user_selected_seats[ k ] = validate_string_as_double_digit_integer_in_range( buffer, 1, 100 );
			}

			// The vectors shoul now hold all the seats that the user wants.
			// Check the availability of the seats.
			try {
				switch ( user_short ) {
					// Auditorium 1
					case 1: {
						for ( short int i = 0; i < user_selected_tickets; ++i ) {
							auditorium_1.reserve_seat_without_input(
									user_selected_rows[ i ], user_selected_seats[ i ]
							);
						}
						std::cout << "Seats reserved!" << std::endl;

						break;
					}

					// Auditorium 2
					case 2: {
						for ( short int i = 0; i < user_selected_tickets; ++i ) {
							auditorium_2.reserve_seat_without_input(
									user_selected_rows[ i ], user_selected_seats[ i ]
							);
						}
						std::cout << "Seats reserved!" << std::endl;

						break;
					}

					// Auditorium 3
					case 3: {
						for ( short int i = 0; i < user_selected_tickets; ++i ) {
							auditorium_3.reserve_seat_without_input(
									user_selected_rows[ i ], user_selected_seats[ i ]
							);
						}
						std::cout << "Seats reserved!" << std::endl;

						break;
					}

					default: {
						std::cerr << "This should be unreachable!\n"
								  << "(short int) user_short is " << user_short
								  << std::endl;
						break;
					}
				} // Close switch-case
			} catch ( UnableToReserveASeatException& e ) {
				std::cout << e.what() << std::endl;
			}
		} else {
			std::cout << "The program will use the number of tickets you want to purchase "
					  << "to find as many consecutive seats free in an auditorium.\n"
					  << "If the program cannot find the number of seats you want, "
					  << "the program will ask you if you want to log your request\n"
					  << "so that a manager can view your request and take care of it."
					  << std::endl;

			try {
				switch ( user_short ) {
					case 1: {
						auditorium_1.perform_automatic_reservation( user_selected_tickets );
						break;
					}
					case 2: {
						auditorium_2.perform_automatic_reservation( user_selected_tickets );
						break;
					}
					case 3: {
						auditorium_3.perform_automatic_reservation( user_selected_tickets );
						break;
					}
					default: {
						std::cerr << "This should be unreachable!\n"
								  << "(short int) user_short is " << user_short
								  << std::endl;
						break;
					}
				}

			} catch ( UnableToReserveASeatException& e ) {
					//! TODO: handle logging request to file
			}
		}
		// Reset the vectors.
		user_selected_rows.clear();
		user_selected_seats.clear();

	}

	void handle_advanced_options_menu() {
		user_short = -1;
		buffer.clear();

		std::cout << "Please enter the password to continue.\n"
				  << "If the password is incorrect, you will be returned to the main menu."
				  << std::endl;
		std::cin >> buffer;

		is_password_good = check_password( buffer, key );

		if ( is_password_good ) {
			std::cout << "Welcome, administator!" << std::endl;
			std::cout << "Please enter a number corresponding to a menu item.\n"
					  << "(1) View special seating requests.\n"
	    			  << "(2) View sales report.\n"
					  << "(3) Print sales report.\n"
					  << "(4) Backup current auditorium files.\n"
					  << "(5) Undo current session.\n"
					  << "(6) Reset auditoriums.\n"
					  << "(7) Return to main menu.\n"
					  << std::endl;
		} else {
			std::cout << "The password you entered is incorrect." << std::endl;
		}
	}

	void handle_quit_menu() {
		user_wants_to_quit = yes_or_no_prompt(
			"Are you sure you want to quit? [y/n]\nChanges to the data will be saved."
		);

		if (user_wants_to_quit) {
			// Wait a little bit after accepting user input to show the next text.
			std::this_thread::sleep_for(std::chrono::milliseconds(250));

			std::cout << "Quitting the program.\n"
					  << "Please wait while the data is saved." << std::endl;

			file_1.open( "A1.txt", std::ios::out | std::ios::trunc );
			file_2.open( "A2.txt", std::ios::out | std::ios::trunc );
			file_3.open( "A3.txt", std::ios::out | std::ios::trunc );

			auditorium_1.write_to_file( file_1 );
			auditorium_2.write_to_file( file_2 );
			auditorium_3.write_to_file( file_3 );

			file_1.close();
			file_2.close();
			file_3.close();

			std::cout << "The data has been saved to the files." << std::endl;

		} else {
			return_to_main_menu();
		}
	}

	void calculate_theatre_values() {
		theatre.set_total_seats(
				auditorium_1.get_total_seats() +
				auditorium_2.get_total_seats() +
				auditorium_3.get_total_seats()
		);

		theatre.set_total_seats_open(
				auditorium_1.get_num_seats_open() +
				auditorium_2.get_num_seats_open() +
				auditorium_3.get_num_seats_open()
		);

		theatre.set_total_seats_reserved(
				auditorium_1.get_num_seats_reserved() +
				auditorium_2.get_num_seats_reserved() +
				auditorium_3.get_num_seats_reserved()
		);

		theatre.set_user_seats( user_selected_tickets );

		theatre.calculate_total_sales();

		theatre.display();
	}

}

int main() {
	using namespace whowell;

    ////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////
    ///INIT PHASE

	try {
		file_1 = std::fstream( "A1.txt", std::ios::in );
		file_2 = std::fstream( "A2.txt", std::ios::in );
		file_3 = std::fstream( "A3.txt", std::ios::in );
	} catch (...) {
		std::cerr << "Something went wrong with the files!" << std::endl;
		return EXIT_FAILURE;
	}

	auditorium_1.set_auditorium_id(1);
	auditorium_2.set_auditorium_id(2);
	auditorium_3.set_auditorium_id(3);

    ////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////
    ///LOAD PHASE

	auditorium_1.load_from_file(file_1);
	auditorium_2.load_from_file(file_2);
	auditorium_3.load_from_file(file_3);

    //Close the input files - they aren't needed until the end of the program.
    file_1.close();
    file_2.close();
    file_3.close();

    if (is_debug) {
    	auditorium_1.display();
    	auditorium_1.display_list();

    	auditorium_2.display();
    	auditorium_2.display_list();

    	auditorium_3.display();
    	auditorium_3.display_list();
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////
    ///MAIN LOOP

    do {
    	handle_main_menu();

    	switch ( user_choice ) {
    		/**
    		 * AUDITORIUM_DISPLAY_MENU
    		 * In this menu, the user can choose an auditorium to display.
    		 * The auditorium will then display its seating as a grid.
    		 */
			case 1: {
				handle_auditorium_display_menu();

				return_to_main_menu();

				break;
			}
			////////////////////////////////////////////////////////////////////
			/// END AUDITORIUM_DISPLAY_MENU ////////////////////////////////////
			////////////////////////////////////////////////////////////////////

			/**
			 * RESERVATION_MENU
			 */
			case 2: {
				handle_reservation_menu();

				return_to_main_menu();

				break;
			}
			////////////////////////////////////////////////////////////////////
			/// END RESERVATION_MENU ///////////////////////////////////////////
			////////////////////////////////////////////////////////////////////

			/**
			 * ADVANCED_OPTIONS_MENU
			 * In this menu, the user can choose to reset the auditoriums,
			 * either by (re)loading the files, thereby undoing the current session
			 * or by resetting all seats to be unreserved.
			 * The user can also choose to print a sales report.
			 * The user can also choose to backup (write to different file) the current files.
			 * The user must enter a password in order to access this menu.
			 * For debug purposes, this password is "admin".
			 */
			case 3: {
				handle_advanced_options_menu();

				return_to_main_menu();

				break;
			}
			////////////////////////////////////////////////////////////////////
			/// END ADVANCED_OPTIONS_MENU //////////////////////////////////////
			////////////////////////////////////////////////////////////////////

			/**
			 * QUIT_MENU
			 * Ask the user if they are sure they want to quit [y/n].
			 * If yes, quit the program. If no, return to the main menu.
			 */
			case 4: {
				handle_quit_menu();

				break;
			}
			////////////////////////////////////////////////////////////////////
			/// END QUIT_MENU //////////////////////////////////////////////////
			////////////////////////////////////////////////////////////////////

			default: {
				std::cerr << "This should be unreachable!\n"
						  << "(short int) user_choice is " << user_choice
						  << std::endl;
				break;
			}
    	}

    	// Wait a little bit before returning to the main menu or exiting.
    	pause_thread( pause_time_ms );
    } while (!user_wants_to_quit);

    std::cout << "Exiting." << std::endl;

	return EXIT_SUCCESS;
}
