//Name: Joyce Vieira Ferreira Dos Santos
//Date: 9/22/2024
//Description: This file (DISSERT HPP) will be used to define subclasses of Dish classes, public and private members used on the project 'Virtual Bistro', expanding for proj 2.
//CSCI 235

#ifndef DESSERT_HPP
#define DESSERT_HPP

#include "Dish.hpp"
#include <vector>
#include <string>

class Dessert :public Dish {
public:
	//Flavor enum definition
	enum FlavorProfile { SWEET, BITTER, SOUR, SALTY, UMAMI };

	//Constructors start here

	/**
	* Default constructor.
	* Initializes all private members with default values.
	*/
	Dessert();

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
	Dessert(const std::string& name, const std::vector<std::string>& ingredients, int prep_time, double price, CuisineType cuisine_type, FlavorProfile flavor_profile, int sweetness_level, bool contains_nuts);


		//Accessor and Mutators start here

	//Getters first (accessors)
	/**
	 * @return The flavor profile (as enum) of the dessert.
	 */
	FlavorProfile getFlavorProfile() const;

	/**
	 * @return The sweetness level of the dessert.
	 */
	int getSweetnessLevel() const;

	/**
	 * @return True if the dessert contain nuts.
	 */
	bool containsNuts() const;

	//Setters second (mutators)
	/**
	 * Sets the flavor profile of the dessert.
	 * @param flavor_profile A reference to the flavor profile.
	 * @post Sets the private member `flavor_profile_` to the value of the parameter.
	 */
	void setFlavorProfile(FlavorProfile flavor_profile);

	/**
	 * Sets the sweetness level of the dessert.
	 * @param sweetness_level An integer representing sweetness level of dessert..
	 * @post Sets the private member `sweetness_level_` to the value of the parameter.
	 */
	void setSweetnessLevel(int sweetness_level);

	/**
	 * Sets the contain_nuts flag of the dessert.
	 * @param contain_nuts A boolean indicating if the dessert contain nuts.
	 * @post Sets the private member `contain_nuts_` to the value of the parameter.
	 */
	void setContainsNuts(bool contains_nuts);

private:
	FlavorProfile flavor_profile_;
	int sweetness_level_;
	bool contains_nuts_;
};
#endif
