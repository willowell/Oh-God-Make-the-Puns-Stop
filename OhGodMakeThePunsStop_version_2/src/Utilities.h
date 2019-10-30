/*
 * Utilities.h
 *
 *  Created on: Oct. 7, 2019
 *      Author: whowell
 */

#ifndef UTILITIES_H_
#define UTILITIES_H_

#include "Auditorium.h"
#include "Exceptions.h"
#include "Theatre.h"

namespace whowell {
	extern bool is_debug;

	extern std::fstream      file_1;
	extern std::fstream      file_2;
	extern std::fstream      file_3;
	extern Auditorium        auditorium_1;
	extern Auditorium        auditorium_2;
	extern Auditorium        auditorium_3;
	extern Theatre           theatre;

	/// User input

	extern short int user_short;
	extern short int user_selected_tickets;
	extern short int user_choice;
	extern int pause_time_ms;
	extern char user_char;
	extern bool user_wants_manual_reservation;
	extern bool user_wants_to_quit;
	extern bool is_password_good;
	extern std::string buffer;
	extern std::string key;
	extern std::vector < short int > user_selected_seats;
	extern std::vector < short int > user_selected_rows;

	// Validation Functions ///////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////

	short int validate_string_as_single_digit_integer_in_range( std::string buffer, short int min, short int max );

	short int validate_string_as_double_digit_integer_in_range( std::string buffer, short int min, short int max );

	char validate_string_as_character( std::string buffer, char upper_case_character );

	bool yes_or_no_prompt( std::string prompt );

	bool check_password( std::string attempt, std::string key );

	////////////////////////////////////////////////////////////////////////////
	/// SUBROUTINES ////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////

	void pause_thread(int for_milliseconds);

	void calculate_theatre_values();

	////////////////////////////////////////////////////////////////////////////
	/// MENU ITEMS /////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////

	void return_to_main_menu();

	void handle_main_menu();

	void handle_auditorium_display_menu();

	void handle_reservation_menu();

	void handle_advanced_options_menu();

	void handle_quit_menu();
} /* namespace whowell */

#endif /* UTILITIES_H_ */
