//Name: Joyce Vieira Ferreira Dos Santos
//Date: 9/15/2024
//Description: This file (DISH HPP) will be used to define classes, public and private members used on the project 'Virtual Bistro'
//CSCI 235

#ifndef DISH_HPP
#define DISH_HPP
#include <vector>
#include <string>
#include <iomanip> //Header required for price formatting (output to two decimal places).
#include <stdlib.h>
#include <iostream>

// @class Dish will represent a bistro simulation. It will model the components of a dish
// such as name, ingredients, prep time, cuisine, price.
// will use methods: set and get (mutator and accessor), to interact with those components.

class Dish {
public:
	//@enum CuisineType define different cuisine types that a dish can belong to.
	//@param cuisine_type_
	//@post sets the private member 'cuisine_type_' to the value of the parameter.
	enum CuisineType {ITALIAN, MEXICAN, CHINESE, INDIAN, AMERICAN, FRENCH, OTHER};


	/**
	*Default constructor.
	* Initializes all private members with default values:
		*-name : "UNKNOWN"
		* -ingredients : Empty list
		* -prep_time : 0
		* -price : 0.0
		* -cuisine_type : OTHER
	**/
	Dish();


	/**
	* Parameterized constructor.
		* @param name A reference to the name of the dish.
		* @param ingredients A reference to a list of ingredients (default is empty list).
		* @param prep_time The preparation time in minutes (default is 0).
		* @param price The price of the dish (default is 0.0).
		* @param cuisine_type The cuisine type of the dish (a CuisineType enum) with default value OTHER.
	Accessors and Mutators:
		* @post The private members are set to the values of the corresponding parameters.
	**/
	Dish(const std::string& name, const std::vector<std::string>& ingredients = {}, const int prep_time = 0, const double price = 0.0, const CuisineType cuisine_type = OTHER);

	//Setters (mutators) Methods

	/**
	* @pre Sets the name of the dish.
	* @param name A reference to the new name if the dish.
	* @post The name of the dish is updated.
	**/
	void setName(const std::string& name);

	/**
	* @pre Sets the ingredient of the dish.
	* @param ingredients A reference to the list of new ingredients.
	* @post The ingredients of the dish is updated.
	**/
	void setIngredients(const std::vector<std::string>& ingredients);

	/**
	* @pre Sets the prep time of the dish.
	* @param prep_time The new prep time in minutes..
	* @post The prep time of the dish is updated.
	**/
	void setPrepTime(const int prep_time);

	/**
	* @pre Sets the price of the dish.
	* @param price The new price in minutes..
	* @post The price of the dish is updated.
	**/
	void setPrice(const double price);

	/**
	* @pre Sets the cuisine type of the dish.
	* @param cuisine_type The new cuisine type (from CuisineType enum).
	* @post The cuisine type of the dish is updated.
	**/
	void setCuisineType(const CuisineType cuisine_type);


	//Getters (accessors) Methods

	/**
	* @return The name of the dish.
	**/
	std::string getName() const;

	/**
	* @return The list of ingredients used in the dish.
	**/
	std::vector <std::string> getIngredients() const;

	/**
	* @return The prep time of the dish in minutes.
	**/
	int getPrepTime() const;

	/**
	* @return The price of the dish.
	**/
	double getPrice() const;

	/**
	* @return The cuisine type of the dish in string form.
	**/
	std::string getCuisineType() const;


	//Display
	/**
	* Displays the details of the dish.
	* @post Outputs the dish's details, including name, ingredients, preparation time, price, and cuisine type, to the standard output.
	* The information must be displayed in the following format:
	*
	* Dish Name: [Name of the dish]
	* Ingredients: [Comma-separated list of ingredients]
	* Preparation Time: [Preparation time] minutes
	* Price: $[Price, formatted to two decimal places]
	* Cuisine Type: [Cuisine type]
	**/
	void display() const;

	private:
		std::string name_;									//The name of the dish.
		std::vector<std::string> ingredients_;				//A list of ingredients used in the dish.	 
		int prep_time_;										//Preparation time in minutes.
		double price_;										//Price of the dish.
		CuisineType cuisine_type_;							//Cuisine type of the dish (from CuisineType enum)

};
#endif
