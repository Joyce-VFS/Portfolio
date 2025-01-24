//Name: Joyce Vieira Ferreira Dos Santos
//Date: 9/22/2024
//Description:In Dessert.hpp I defined the subclasses and functions necessary for the 'Virtual Bistro' expansion and now this file (DESSERT.CPP) will be used for the implementation of the hpp file.
//CSCI 235

#include "Dish.hpp"
#include "Dessert.hpp" //Here I'm including the header file that constain the subclass definitions.
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
Dessert::Dessert() : Dish(), flavor_profile_(), sweetness_level_(0), contains_nuts_(false){}

/**
 * Parameterized constructor.
 * @param name The name of the dessert.
 * @param ingredients The ingredients used in the dessert.
 * @param prep_time The preparation time in minutes.
 * @param price The price of the dessert.
 * @param cuisine_type The cuisine type of the dessert.
 * @param flavor_profile The flavor profile of the dessert.
 * @param sweetness_level The sweetness level of the dessert.
 * @param contains_nuts Flag indicating if the dessert contains nuts.
 */
Dessert::Dessert(const std::string& name, const std::vector<std::string>& ingredients, int prep_time, double price, CuisineType cuisine_type, FlavorProfile flavor_profile, int sweetness_level, bool contains_nuts)
	: Dish(name, ingredients, prep_time, price, cuisine_type), flavor_profile_(flavor_profile), sweetness_level_(sweetness_level), contains_nuts_(contains_nuts) {}

//Accessor and Mutators start here

//Getters first (accessors)
/**
 * @return The flavor profile of the dish.
 */
Dessert::FlavorProfile Dessert::getFlavorProfile() const {
	return flavor_profile_;
}

/**
 * @return The sweetness level of the dish.
 */
int Dessert::getSweetnessLevel()const {
	return sweetness_level_;
}

/**
 * @return The contain nuts flah.
 */
bool Dessert::containsNuts() const {
	return contains_nuts_;
}


//Setters second (mutators)
/**
 * Sets the flavor profile the dessert.
 * @param flavor_profile A reference to the cooking method of the dish.
 * @post Sets the private member `flavor_profile_` to the value of the parameter.
 */
void Dessert::setFlavorProfile(FlavorProfile flavor_profile) {
	flavor_profile_ = flavor_profile;
}

/**
 * Sets the sweetness level of the dessert.
 * @param sweetness_level A reference to the protein type of the dish.
 * @post Sets the private member `protein_type_` to the value of the parameter.
 */
void Dessert::setSweetnessLevel(int sweetness_level) {
	sweetness_level_ = sweetness_level;
}

/**
 * Sets contain nuts flag.
 * @param contains_nuts As true if the dessert contain nuts.
 * @post Sets the private member `contains_nuts_` to the value of the parameter.
 */
void Dessert::setContainsNuts(bool contains_nuts){
	contains_nuts_ = contains_nuts;
}