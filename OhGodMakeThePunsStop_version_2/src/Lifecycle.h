#ifndef OHGODMAKETHEPUNSSTOP_VERSION_2_LIFECYCLE_H
#define OHGODMAKETHEPUNSSTOP_VERSION_2_LIFECYCLE_H

#include "Utilities.h"

namespace Whowell {
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
}

#endif //OHGODMAKETHEPUNSSTOP_VERSION_2_LIFECYCLE_H
