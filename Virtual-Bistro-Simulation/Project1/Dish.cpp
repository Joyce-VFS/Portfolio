//Name: Joyce Vieira Ferreira Dos Santos
//Date: 9/15/2024
//Description: In Dish.hpp I defined the classes and functions necessary for the 'Virtual Bistro project' 
// and now this file (DISH.CPP) will be used for the implementation of the hpp file.
//CSCI 235

#include "Dish.hpp" //Here I'm including the header file that constain the class definitions.
#include <iostream> 
#include <iomanip> //Header required for price formatting (output to two decimal places).
#include <string>
#include <stdlib.h>
#include <vector>

/**Default constructor.
* 
* Initializes a default dish with following values:
* -name: "UNKNOWN"
* -ingrdients: empty list
* -prep_time: 0 minutes
* -price: $0.00
* -cuisine_type: OTHER (undefined)
* 
* This constructor is going to be used when no data is provided when object is created.
**/
Dish::Dish() : name_("UNKNOWN"), prep_time_(0), price_(0.0), cuisine_type_(OTHER) {
}

/**Parameterized constructor.
*
* Initializes a dish with specified values following values:
* @param name The name of the dish.
* @param ingrdients A vector of ingredients (when default, empty list).
* @param prep_time The prep time in minutes (when default, 0 minutes).
* @param price The price of the dish in dollars (when default, $0.0).
* @param cuisine_type The cuisine type (when default, OTHER). 
*
**/
Dish::Dish(const std::string& name, const std::vector<std::string>& ingredients,const int prep_time,const double price,const CuisineType cuisine_type)
	: name_(name), ingredients_(ingredients), prep_time_(prep_time), price_(price), cuisine_type_(cuisine_type) {

}


	//Setters first

/**
* @pre Sets the name of the dish.
* @param name A new name fot the dish.
* @post The dish's name is updated.
**/
void Dish::setName(const std::string& name) {
	name_ = name;	//update variable 'name_' iwth the new name inputed.
}

/**
* @pre Sets the ingredients of the dish.
* @param ingredients A vector of new ingredients.
* @post The dish's ingredients list is updated.
**/
void Dish::setIngredients(const std::vector<std::string>& ingredients) {
	ingredients_ = ingredients;	//Update variable 'ingredients_' with list inputed.
}

/**
* @pre Sets the prep time of the dish.
* @param prep_time The new prep time in minutes.
* @post The dish's prep time is updated.
**/
void Dish::setPrepTime(const int prep_time) {
	prep_time_ = prep_time;	//Update variable 'prep_time_' with new value inputed.
}

/**
* @pre Sets the price of the dish.
* @param price The new price of dish.
* @post The dish's price is updated.
**/
void Dish::setPrice(const double price) {
	price_ = price;	//Update variable 'price_' with new value inputed.
}

/**
* @pre Sets the cuisine type of the dish.
* @param cuisine_type_ The new cuisine type (from CuisineType enum).
* @post The dish's cuisine type is updated.
**/
void Dish::setCuisineType(const CuisineType cuisine_type) {
	cuisine_type_ = cuisine_type;	//Update variable 'cuisine_type_' with new enum value.
}


	//Getters second

/**
* @return The name of the dish.
**/
std::string Dish::getName() const {
	return name_;	//Just return the private member variable 'name_'
}

/**
* @return The vector containing the ingredients of the dish.
**/
std::vector<std::string> Dish::getIngredients() const {
	return ingredients_;	//Just return the private member variable 'ingredients_'
}

/**
* @return The prep time of the dish.
**/
int Dish::getPrepTime() const {
	return prep_time_;	//Just return the private member variable 'pre_time_'
}

/**
* @return The price of the dish.
**/
double Dish::getPrice() const {
	return price_;	//Just return the private member variable 'price_'
}

/**
* @return The cuisine type of the dish.
**/
std::string Dish::getCuisineType() const {
	switch (cuisine_type_) {
	case ITALIAN: return "ITALIAN";
	case MEXICAN: return "MEXICAN";
	case CHINESE: return "CHINESE";
	case INDIAN: return "INDIAN"; 
	case AMERICAN: return "AMERICAN";
	case FRENCH: return "FRENCH";
	default: return "OTHER";
	}
	
}

	//Display
/**
 * @pre Displays the details of the dish.
 * @post Outputs the dish's details, including name, ingredients, preparation time, price, and cuisine type.
 **/
void Dish::display() const {
	std::cout << "Dish Name: " << name_ << std::endl;								//Output name of the dish
	std::cout << "Ingredients: ";	
	for (size_t i = 0; i < ingredients_.size(); ++i) {
		std::cout << ingredients_[i];
		if (i < ingredients_.size() - 1) std::cout << ", ";
	}																			//Output the list of ingredients separated by comma
	std::cout << "\nPreparation Time: " << prep_time_ << " minutes";			//Output prep time of the dish
	std::cout << "\nPrice: $" << std::fixed << std::setprecision(2) << price_;	//Output price (two decimal places) of the dish.
	std::cout << "\nCuisine Type: ";
	std::cout << getCuisineType() << std::endl;
}