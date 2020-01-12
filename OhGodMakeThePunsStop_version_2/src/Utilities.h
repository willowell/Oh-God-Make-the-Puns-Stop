/*
 * Utilities.h
 *
 *  Created on: Oct. 7, 2019
 *      Author: Whowell
 */

#ifndef OHGODMAKETHEPUNSSTOP_VERSION_2_UTILITIES_H
#define OHGODMAKETHEPUNSSTOP_VERSION_2_UTILITIES_H

#include "Auditorium.h"
#include "Exceptions.h"
#include "Theatre.h"

namespace Whowell {
	extern bool is_debug;
	
	extern std::fstream file_1;
	extern std::fstream file_2;
	extern std::fstream file_3;
	extern Auditorium auditorium_1;
	extern Auditorium auditorium_2;
	extern Auditorium auditorium_3;
	extern Theatre theatre;
	
	/// User input
	
	extern short int user_short;
	extern short int user_selected_tickets;
	extern short int user_choice;
	extern int pause_time_ms;
	extern char user_char;
	extern bool user_wants_manual_reservation;
	extern bool user_wants_to_log_request;
	extern bool user_wants_to_quit;
	extern bool is_password_good;
	extern std::string buffer;
	extern std::string key;
	extern std::vector<short int> user_selected_seats;
	extern std::vector<short int> user_selected_rows;
	extern std::vector<std::string> user_logged_requests;
	
	// Validation Functions ///////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////
	
	/**
	 * Validates user input as a single digit integer in a range [min, max].
	 * WARNING: This function does not impose any predicates on min or max yet,
	 * therefore this function will break if min > max.
	 *
	 * This function works fine for checking if the user has given a whole number in the range [0, 9].
	 */
	int validate_string_as_single_digit_integer_in_range(std::string buffer, short int min, short int max);
	
	/**
	 * Validates user input as a double digit integer in a range [min, max].
	 * WARNING: This function does not impose any predicates on min or max yet,
	 * therefore this function will break if min > max.
	 *
	 * This function works fine for checking if the user has given a whole number in the range [0, 99].
	 */
	int validate_string_as_double_digit_integer_in_range(std::string buffer, short int min, short int max);
	
	/**
	 * Validates user input as a single character regardless of character case.
	 *
	 * It is possible that the user may enter a single digit number that corresponds
	 * to the ASCII code of a character.
	 */
	char validate_string_as_character(std::string buffer, char upper_case_character);
	
	/**
	 * Prints the prompt and then validates user input as being either 'y' or 'n',
	 * disregarding character case.
	 *
	 * Returns true if user entered 'y'; returns false otherwise.
	 */
	bool yes_or_no_prompt(const std::string& prompt);
	
	/**
	 * Simple wrapper around an if/else on string.compare().
	 */
	bool check_password(const std::string& attempt, std::string answer);
	
	////////////////////////////////////////////////////////////////////////////
	/// SUBROUTINES ////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////
	
	/**
	 * Pause the thread for a specified number of milliseconds.
	 */
	void pause_thread(int for_milliseconds);
	
	/**
	 * Accepts a value and switches on the available auditoriums,
	 * displaying the user's choice.
	 * Note: the program must validate on_switch before passing it here.
	 * Otherwise, say if the user passes -1, 56, or something like that,
	 * the default case will be triggered.
	 *
	 * This is just a simple wrapper around a switch statement that was
	 * showing up a lot.
	 */
	void display_auditoriums_on_switch(int on_switch);
	
	/**
	 * Use the current state of the auditoriums to compute the values
	 * for the Theatre object.
	 */
	void calculate_theatre_values();
	
	/**
	 * Builds a string from the number of tickets the user requested,
	 * and adds this request to the vector that holds user requests.
	 */
	void log_reservation_request();
	
	/**
	 * Saves the values in the vector that holds user requests to a file.
	 * Each line in the file corresponds to an item in the vector.
	 */
	void save_reservation_requests_to_file();
	
	////////////////////////////////////////////////////////////////////////////
	/// MENU ITEMS /////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////
	
	/**
	 * Prints "Returning to main menu" and pauses the thread.
	 */
	void return_to_main_menu();
	
	/**
	 * Prints the main menu, validates user input for the menu item choice,
	 * and then pauses the thread before proceeding.
	 */
	void handle_main_menu();
	
	
	/**
	 * Asks the user for the number of an auditorium,
	 * prints the auditorium to the console,
	 * and then pauses the thread before proceeding.
	 */
	void handle_auditorium_display_menu();
	
	void handle_reservation_menu();
	
	void handle_advanced_options_menu();
	
	/**
	 * First, prompts the user whether or not they are sure
	 * that they want to quit.
	 *
	 * If the user says yes, the program saves the current state
	 * of the auditoriums to file, as well as any special requests.
	 * The main program loop breaks out here, causing the program to exit.
	 *
	 * If the user says no, the program simply returns to the main menu.
	 */
	void handle_quit_menu();
} /* namespace Whowell */

#endif /*OHGODMAKETHEPUNSSTOP_VERSION_2_UTILITIES_H*/
