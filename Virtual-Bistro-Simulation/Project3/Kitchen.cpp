/**
 * @file Kitchen.cpp
 * @brief This file contains the implementation of the Kitchen subclass, which represents a kitchen in a virtual bistro simulation.
 *
 * The Kitchen subclass includes methods to manage and present the details kitchen operation.
 * The implementation of hpp ensures that the Kitchen is correctly formatted.
 *
 * @date 10/04/2024
 * @author Joyce Vieira Ferreira Dos Santos
 */

#include "Kitchen.hpp" //Here i'm including the header file that contains the subclass definitions
#include "Dish.hpp" //to handle Dish objs
#include "ArrayBag.hpp"
#include <string>
#include <vector>
#include <iomanip>
#include <iostream>
#include <cmath>

		//Constructor start here
/**
 * Default constructor.
 * Default-initializes all private members.
 */
Kitchen::Kitchen() : total_prep_time_(0), count_elaborate_(0) {

}


		//Unique Methods start here
/**
 * @param : A reference to a `Dish` being added to the kitchen.
 * @post : If the given `Dish` is not already in the kitchen, adds the
 `Dish` to the kitchen and updates the preparation time sum and elaborate
 dish count if the dish is elaborate.
 * @return : Returns true if a `Dish` was successfully added to the
 kitchen, false otherwise.
 Hint: Use the above definition of equality to help determine if a
 `Dish` is already in the kitchen.
 */
bool Kitchen::newOrder(const Dish& dish) {
	if (!contains(dish)) {
		add(dish);
		total_prep_time_ += dish.getPrepTime();
		if(dish.getIngredients().size() >= 5 && dish.getPrepTime() >= 60) {
			count_elaborate_++;
		}
		return true;
	}
	return false;
}

/**
 * @param : A reference to a `Dish` leaving the kitchen.
 * @return : Returns true if a dish was successfully removed from the
 kitchen (i.e.,
 items_), false otherwise.
 * @post : Removes the dish from the kitchen and updates the preparation
 time sum.
 If the `Dish` is elaborate, it also updates the elaborate count.
 */
bool Kitchen::serveDish(const Dish& dish) {
	if (remove(dish)) {
		total_prep_time_ -= dish.getPrepTime();
		if (dish.getIngredients().size() >= 5 && dish.getPrepTime() >= 60) {
			count_elaborate_--;
		}
		return true;
	}
	return false;
}

/**
 * @return : The integer sum of preparation times for all the dishes
 currently in the kitchen.
 */
int Kitchen::getPrepTimeSum()const {
	return total_prep_time_;
}

/**
 * @return : The average preparation time (int) of all the dishes in the
 kitchen. The lowest possible average prep time should be 0.
 * @post : Computes the average preparation time (double) of the kitchen
 rounded to the NEAREST integer.
 */
int Kitchen::calculateAvgPrepTime() const {
	if (getCurrentSize() == 0)return 0;
	return static_cast<int>(round(static_cast<double>(total_prep_time_) / getCurrentSize()));
}

/**
 * @return : The integer count of the elaborate dishes in the kitchen.
 */
int Kitchen::elaborateDishCount() const {
	return count_elaborate_;
}

/**
 * @return : The percentage (double) of all the elaborate dishes in the
 kitchen. The lowest possible percentage should be 0%.
 * @post : Computes the percentage of elaborate dishes in the kitchen
 rounded up to 2 decimal places.
 */
double Kitchen::calculateElaboratePercentage() const {
	if (getCurrentSize() == 0)return 0.0;
	return round((static_cast<double>(count_elaborate_) / getCurrentSize()) * 10000) / 100.0;
}

/**
 * @param : A reference to a string representing a cuisine type with a
 value in
 ["ITALIAN", "MEXICAN", "CHINESE", "INDIAN", "AMERICAN",
 "FRENCH", "OTHER"].
 * @return : An integer tally of the number of dishes in the kitchen of the
 given cuisine type.
 If the argument string does not match one of the expected
 cuisine types, the tally is zero.
 NOTE: No pre-processing of the input string necessary, only
 uppercase input will match.
 */
int Kitchen::tallyCuisineTypes(const std::string& cuisine) const {
	int count = 0;
	for (int i = 0; i < getCurrentSize(); i++) {
		if (items_[i].getCuisineType() == cuisine) {
			count++;
		}
	}
	return count;
}

/**
 * @param : A reference to an integer representing the preparation time
 threshold of the dishes to be removed from
 the kitchen, with a default value of 0.
 * @post : Removes all dishes from the kitchen whose preparation time is
 less than the given time.
 If no time is given, removes all dishes from the kitchen. Ignore
 negative input.
 * @return : The number of dishes removed from the kitchen.
 */
int Kitchen::releaseDishesBelowPrepTime(int time) {
	int count = 0;
	//this for loop doesnt need incrementation to avoid skipping elements
	for (int i = 0; i < getCurrentSize(); ) {
		if (items_[i].getPrepTime() < time) {
			serveDish(items_[i]);
			count++;
		}
		else {
			++i;
		}
	}
	return count;
}

/**
 * @param : A reference to a string representing a cuisine type with a
 value in
 ["ITALIAN", "MEXICAN", "CHINESE", "INDIAN", "AMERICAN",
 "FRENCH", "OTHER"],
 or a default value of "ALL" if no cuisine type is given.
 Testing
 Although you will no longer submit your test file, you must continue to thoroughly and
 methodically test your code.
 * @post : Removes all dishes from the kitchen whose cuisine type matches
 the given type.
 If no cuisine type is given, removes all dishes from the kitchen.
 * @return : The number of dishes removed from the kitchen.
 NOTE: No pre-processing of the input string necessary, only
 uppercase input will match.
 If the input string does not match one of the expected cuisine
 types, do not remove any dishes.
 */
int Kitchen::releaseDishesOfCuisineType(const std::string& cuisine) {
	int count = 0;
	//this for loop doesnt need incrementation to avoid skipping elements
	for (int i = 0; i < getCurrentSize();) {
		if (cuisine == "ALL" || items_[i].getCuisineType() == cuisine) {
			serveDish(items_[i]);
			count++;
		}
		else {
			++i;
		}
	}
	return count;
}

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
void Kitchen::kitchenReport() const {
	std::cout << "ITALIAN: " << tallyCuisineTypes("ITALIAN") << "\n";
	std::cout << "MEXICAN: " << tallyCuisineTypes("MEXICAN") << "\n";
	std::cout << "CHINESE: " << tallyCuisineTypes("CHINESE") << "\n";
	std::cout << "INDIAN: " << tallyCuisineTypes("INDIAN") << "\n";
	std::cout << "AMERICAN: " << tallyCuisineTypes("AMERICAN") << "\n";
	std::cout << "FRENCH: " << tallyCuisineTypes("FRENCH") << "\n";
	std::cout << "OTHER: " << tallyCuisineTypes("OTHER") << "\n";
	std::cout << "\nAVERAGE PREP TIME: " << calculateAvgPrepTime() << "\n";
	std::cout << std::fixed << std::setprecision(2);
	std::cout << "ELABORATE: " << calculateElaboratePercentage() << "%\n";
}




