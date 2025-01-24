/**
 * @file Kitchen.hpp
 * @brief This file contains the declaration of the Kitchen subclass, which represents the kitchen in a virtual bistro simulation.
 *
 * The Kitchen subclass includes attributes such as total preparation time, count of elaborate dishes (more than 5 ingredients), new order,
 * serve dish, get prep time sum, calculate avg prep time, calculate elaborate dish percentage, tally cuisine type, release dish below prep time,
 * release dish off cuisine type, kitchen report.
 * It provides constructors, accessor and mutator functions, and a display function to manage and present
 * the details of a dish.
 *
 * @date 10/04/2024
 * @author Joyce Vieira Ferreira Dos Santos
 */

#ifndef KITCHEN_HPP
#define KITCHEN_HPP

#include "ArrayBag.hpp"
#include "Dish.hpp"
#include <vector>
#include <string>
#include <iomanip>
#include <iostream>

class Kitchen : public ArrayBag<Dish> {
private:
	int total_prep_time_;
	int count_elaborate_;

public:
	/**
	* Default constructor.
	* Default-initializes all private members.
	*/
	Kitchen();

	//@return true if a dish was sucessfully added from the kitchen
	bool newOrder(const Dish& dish);

	//@return true if a dish was sucessfully removed from the kitchen
	bool serveDish(const Dish& dish);

	//@return The sum of preparation times
	int getPrepTimeSum() const;

	//@return The average prep time
	int calculateAvgPrepTime() const;

	//@return integer count of the Elaborate dishes
	int elaborateDishCount() const;

	//@return Percentage (double) of elaborated dishes. lowest possible is 0%
	double calculateElaboratePercentage() const;

	/**
	 * @param : A reference to a string representing a cuisine type with a value in
	 ["ITALIAN", "MEXICAN", "CHINESE", "INDIAN", "AMERICAN",
	 "FRENCH", "OTHER"].
	 * @return : An integer tally of the number of dishes in the kitchen of the
	 given cuisine type.
	 If the argument string does not match one of the expected
	 cuisine types, the tally is zero.
	 NOTE: No pre-processing of the input string necessary, only
	 uppercase input will match.
	 */
	int tallyCuisineTypes(const std::string& cuisine) const;

	/* @return : The number of dishes removed from the kitchen.*/
	int releaseDishesBelowPrepTime(int time = 0);

	/*@return : The number of dishes removed from the kitchen.
	 NOTE : No pre - processing of the input string necessary, only
	 uppercase input will match.
	 If the input string does not match one of the expected cuisine
	 types, do not remove any dishes.
	 */
	int releaseDishesOfCuisineType(const std::string& cuisine = "ALL");

	/**
	 * @post : Outputs a report of the dishes currently in the kitchen in the
	 form:
	 "ITALIAN: {x}\nMEXICAN: {x}\nCHINESE: {x}\nINDIAN:
	 {x}\nAMERICAN: {x}\nFRENCH: {x}\nOTHER: {x}\n\n
	 AVERAGE PREP TIME: {x}\ELABORATE: {x}%\n"
	 Note that the average preparation time should be rounded to the
	 NEAREST integer, and the
	 percentage of elaborate dishes in the kitchen should be rounded
	 to 2 decimal places.

	 Example output:
	 ITALIAN: 2
	 MEXICAN: 3
	 CHINESE: 2
	 INDIAN: 1
	 AMERICAN: 1
	 FRENCH: 2
	 OTHER: 2
	 AVERAGE PREP TIME: 62
	 ELABORATE: 53.85%
	 */
	void kitchenReport() const;

};

#endif
