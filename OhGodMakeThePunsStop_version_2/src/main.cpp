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

	bool is_debug = false;

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
	bool user_wants_to_log_request;
	bool user_wants_to_quit = false;
	bool is_password_good = false;
	std::string buffer;
	std::string key = "admin";
	std::vector < short int > user_selected_seats;
	std::vector < short int > user_selected_rows;
	std::vector < std::string > user_logged_requests;
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

				// Save any changes in the auditoriums
				// to the Theatre
				calculate_theatre_values();

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

				// Recalculate any changes to the Theatre.
				// The user can view and/or print a sales report in this menu,
				// so this calculation should happen here. Otherwise, the
				// sales report won't reflect the auditoriums' current state.
				calculate_theatre_values();

				// In the event that the user had made any special requests
				// this session, save them here before displaying
				// the advanced options menu. An administrator can view
				// special requests in this menu. Like the theatre values,
				// this is to make sure the special requests menu reflects
				// the current state of the auditoriums.
				save_reservation_requests_to_file();

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
