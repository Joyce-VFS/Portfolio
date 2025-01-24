//Name: Joyce Vieira Ferreira Dos Santos
//Date: 9/22/2024
//Description:  This file (MAINCOURSE HPP) will be used to define subclasses of Dish classes, public and private members used on the project 'Virtual Bistro', expanding for proj 2.
//CSCI 235

#ifndef MAINCOURSE_HPP
#define MAINCOURSE_HPP

#include "Dish.hpp"
#include <vector>
#include <string>

class MainCourse : public Dish {
public:
	//Cooking method enum definition
	enum CookingMethod { GRILLED, BAKED, FRIED, STEAMED, RAW};
	enum Category { GRAIN, PASTA, LEGUME, BREAD, SALAD, SOUP, STARCHES, VEGETABLE };
	//Struct for the SideDish containing name as string and category as enum members
	struct SideDish {
		std::string name;
		Category category;
	};

	//Constructors start here

	/**
	* Default constructor.
	* Initializes all private members with default values.
	*/
	MainCourse();

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
	MainCourse(const std::string& name, const std::vector<std::string>& ingredients, int prep_time, double price, CuisineType cuisine_type,
		CookingMethod cooking_method, const std::string& protein_type, const std::vector<SideDish>& side_dishes, bool gluten_free);


		//Accessor and Mutators start here

	//Getters first (accessors)
	/**
	 * @return The cooking method of the dish.
	 */
	CookingMethod getCookingMethod() const;

	/**
	 * @return The protein type of the dish.
	 */
	std::string getProteinType() const;

	/**
	 * @return The side dish of the dish.
	 */
	std::vector<SideDish> getSideDishes() const;

	// Gluten Free flag
	/**
	 * @return Gluten Free flag for the dish if appropriate.
	 */
	bool isGlutenFree() const;


	//Setters second (mutators)
	/**
	 * Sets the cooking method of the dish.
	 * @param cooking_method A reference to the cooking method of the dish.
	 * @post Sets the private member `cooking_method_` to the value of the parameter.
	 */
	void setCookingMethod(CookingMethod cooking_method);

	/**
	 * Sets the protein type of the dish.
	 * @param protein_type A reference to the cooking method of the dish.
	 * @post Sets the private member `protein_type_` to the value of the parameter.
	 */
	void setProteinType(const std::string &protein_type);

	/**
	 * Adds a side dish to the main course.
	 * @param side_dish A SideDish struct containing the name ad category of the side dish..
	 * @post Adds the side dish to the 'Side_dishes_' vector.
	 */
	void addSideDish(const SideDish &side_dish);

	/**
	 * Sets the gluten-free flag of the main course.
	 * @param gluten_free A boolean indicating if the main course is glutenfree.
	 * @post Sets the private member `gluten_free_` to the value of the parameter.
	 */
	void setGlutenFree(bool gluten_free);

private:
	CookingMethod cooking_method_;
	std::string protein_type_;
	std::vector<SideDish> side_dishes_;
	bool gluten_free_;
};

#endif
