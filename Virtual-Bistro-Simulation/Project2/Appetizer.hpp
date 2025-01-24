//Name: Joyce Vieira Ferreira Dos Santos
//Date: 9/22/2024
//Description:  This file (APPETIZERT HPP) will be used to define subclasses of Dish classes, public and private members used on the project 'Virtual Bistro', expanding for proj 2.
//CSCI 235

#ifndef APPETIZER_HPP
#define APPETIZER_HPP

#include "Dish.hpp"
#include <vector>
#include <string>

class Appetizer : public Dish {
public:
	//ServingSTyle enum definition
	enum ServingStyle { PLATED, FAMILY_STYLE, BUFFET };

		//Constructors start here

	/**
	* Default constructor.
	* Initializes all private members with default values.
	*/
	Appetizer();

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
	Appetizer(const std::string& name, const std::vector<std::string>& ingredients, int prep_time, double price, CuisineType cuisine_type, ServingStyle serving_style, int spiciness_level, bool vegetarian);


		//Accessor and Mutators start here

	//Getters first (accessors)
	/**
	 * @return The serving style of the dish.
	 */
	ServingStyle getServingStyle() const;

	/**
	 * @return Spiciness level of the dish.
	 */
	int getSpicinessLevel() const;

	// Vegetarian Flag
	/**
	 * @return Vegetarian flag for the dish if appropriate.
	 */
	bool isVegetarian() const;
	

	//Setters second (mutators)
	/**
	 * Sets the serving style the dish.
	 * @param serving_style A reference to the serving style of the dish.
	 * @post Sets the private member `serving_style_` to the value of the parameter.
	 */
	void setServingStyle(ServingStyle serving_style);

	/**
	 * Sets the spiciness level of the dish.
	 * @param spiciness_level A reference to the spiciness level of the dish.
	 * @post Sets the private member `spiciness_level_` to the value of the parameter.
	 */
	void setSpicinessLevel(int spiciness_level);

	/**
	 * Sets whether the dish is vegetarian.
	 * @param vegetarian A reference to whether the dish is vegetarian.
	 * @post Sets the private member `vegetarian_` to the value of the parameter.
	 */
	void setVegetarian(bool vegetarian);

private:
	ServingStyle serving_style_;
	int spiciness_level_;
	bool vegetarian_;

};

#endif
