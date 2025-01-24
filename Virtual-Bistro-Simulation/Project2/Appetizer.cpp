//Name: Joyce Vieira Ferreira Dos Santos
//Date: 9/22/2024
//Description:In Appetizer.hpp I defined the subclasses and functions necessary for the 'Virtual Bistro' expansion and now this file (APPETIZER.CPP) will be used for the implementation of the hpp file.
//CSCI 235

#include "Dish.hpp"
#include "Appetizer.hpp" //Here I'm including the header file that constain the subclass definitions.
#include <iostream> 
#include <iomanip> //Header required for price formatting (output to two decimal places).
#include <string>
#include <stdlib.h>
#include <vector>

	//Constructors start here

/**
* Default constructor.
* Initializes all private members with default values.
*/
Appetizer::Appetizer() : Dish(), serving_style_(), spiciness_level_(0), vegetarian_(false) {}

/**
 * Parameterized constructor.
 * @param name The name of the appetizer.
 * @param ingredients The ingredients used in the appetizer.
 * @param prep_time The preparation time in minutes.
 * @param price The price of the appetizer.
 * @param cuisine_type The cuisine type of the appetizer.
 * @param serving_style The serving style of the appetizer.
 * @param spiciness_level The spiciness level of the appetizer.
 * @param vegetarian Flag indicating if the appetizer is vegetarian.
 */
Appetizer::Appetizer(const std::string &name, const std::vector<std::string> &ingredients, int prep_time, double price, CuisineType cuisine_type, ServingStyle serving_style, int spiciness_level, bool vegetarian) : Dish(name, ingredients, prep_time, price, cuisine_type), serving_style_(serving_style), spiciness_level_(spiciness_level), vegetarian_(vegetarian) {}


	//Accessor and Mutators start here

//Getters first (accessors)
/**
 * @return The serving style of the dish.
 */
Appetizer::ServingStyle Appetizer::getServingStyle() const {
	return serving_style_;
}

/**
 * @return The spiciness level of the dish.
 */
int Appetizer::getSpicinessLevel()const {
	return spiciness_level_;
}

/**
 * @return The true if the dish is vegetarian.
 */
bool Appetizer::isVegetarian() const {
	return vegetarian_;
}

//Setters second (mutators)
/**
 * Sets the serving style the dish.
 * @param serving_style A reference to the serving style of the dish.
 * @post Sets the private member `serving_style_` to the value of the parameter.
 */
void Appetizer::setServingStyle(ServingStyle serving_style) {
	serving_style_ = serving_style;
}

/**
 * Sets the spiceness level the dish.
 * @param spiciness_level A integer to the spiciness level of the dish.
 * @post Sets the private member `spiciness_level_` to the value of the parameter.
 */
void Appetizer::setSpicinessLevel(int spiciness_level) {
	spiciness_level_ = spiciness_level;
}

/**
 * Sets vegetarian flag.
 * @param vegetarian As true if the dish is vegetarian.
 * @post Sets the private member `vegetarian_` to the value of the parameter.
 */
void Appetizer::setVegetarian(bool vegetarian) {
	vegetarian_ = vegetarian;
}