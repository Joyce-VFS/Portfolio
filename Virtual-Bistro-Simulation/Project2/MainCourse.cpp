//Name: Joyce Vieira Ferreira Dos Santos
//Date: 9/22/2024
//Description:In MainCourse.hpp I defined the subclasses and functions necessary for the 'Virtual Bistro' expansion and now this file (MAINCOURSE.CPP) will be used for the implementation of the hpp file.
//CSCI 235


#include "Dish.hpp"
#include "MainCourse.hpp" //Here I'm including the header file that constain the subclass definitions.
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
MainCourse::MainCourse() : Dish(), cooking_method_(), protein_type_("UNKNOWN"),side_dishes_(), gluten_free_(false) {}

/**
 * Parameterized constructor.
 * @param name The name of the main course.
 * @param ingredients A vector of the ingredients used in the main course.
 * @param prep_time The preparation time in minutes.
 * @param price The price of the main course.
 * @param cuisine_type The cuisine type of the main course.
 * @param cooking_method The cooking method used for the main course.
 * @param protein_type The type of protein used in the main course.
 * @param side_dishes A vector of the side dishes served with the main course.
 * @param gluten_free Boolean flag indicating if the main course is gluten-free.
 */
MainCourse::MainCourse(const std::string& name, const std::vector<std::string>& ingredients, int prep_time, double price,
	CuisineType cuisine_type, CookingMethod cooking_method, const std::string& protein_type, const std::vector<SideDish>& side_dishes, bool gluten_free)
	: Dish(name, ingredients, prep_time, price, cuisine_type), cooking_method_(cooking_method), 
	protein_type_(protein_type), side_dishes_(side_dishes), gluten_free_(gluten_free) {}

//Accessor and Mutators start here

//Getters first (accessors)
/**
 * @return The cooking method of the dish.
 */
MainCourse::CookingMethod MainCourse::getCookingMethod() const{
	return cooking_method_;
}

/**
 * @return The protein type of the dish.
 */
std::string MainCourse::getProteinType() const {
	return protein_type_;
}

/**
 * @return The Side dishes.
 */
std::vector<MainCourse::SideDish> MainCourse::getSideDishes() const {
	return side_dishes_;
}

/**
 * @return The gluten-free flah.
 */
bool MainCourse::isGlutenFree() const {
	return gluten_free_;
}


//Setters second (mutators)
/**
 * Sets the cooking method the dish.
 * @param cooking_method A reference to the cooking method of the dish.
 * @post Sets the private member `cooking_method_` to the value of the parameter.
 */
void MainCourse::setCookingMethod(CookingMethod cooking_method) {
	cooking_method_ = cooking_method;
}

/**
 * Sets the protein type the dish.
 * @param protein_type A reference to the protein type of the dish.
 * @post Sets the private member `protein_type_` to the value of the parameter.
 */
void MainCourse::setProteinType(const std::string& protein_type) {
	protein_type_ = protein_type;
}

/**
 * Sets gluten free flag.
 * @param gluten_free As true if the dish is gluten free.
 * @post Sets the private member `vegetarian_` to the value of the parameter.
 */
void MainCourse::setGlutenFree(bool gluten_free){
	gluten_free_ = gluten_free;
}
//Method to add side dish
/**
 * Add side dish to main course.
 * @param side_dish.
 * @post Sets the private member `side_dishes_` to the value of the parameter.
 */
void MainCourse::addSideDish(const SideDish& side_dish) {
	side_dishes_.push_back(side_dish);
}