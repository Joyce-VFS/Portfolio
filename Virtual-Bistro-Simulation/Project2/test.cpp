//Name: Joyce Vieira Ferreira Dos Santos
//Date: 9/15/2024
//Description: Here I will write my test case to test functionality of Appetizer, MainCourse and Dessert, and check whether implementation behaves as expected.

#include "Dish.hpp"
#include "Appetizer.hpp"
#include "MainCourse.hpp"
#include "Dessert.hpp"
#include <iostream>
#include <iomanip> //Header required for price formatting (output to two decimal places).
#include <string>
#include <stdlib.h>
#include <vector>

//Main will test functionality of both constructors, accessors and mutators methods.
int main() {

	//1ST TEST (Appetizer) Instantiating an appetizer with the default constructor using SETTERS:
	Appetizer appetizer;
	appetizer.setName("UNKNOWN");
	appetizer.setIngredients({});
	appetizer.setPrepTime(0);
	appetizer.setPrice(0.00);
	appetizer.setCuisineType(Dish::CuisineType::OTHER);
	appetizer.setSpicinessLevel(7);
	appetizer.setServingStyle(Appetizer::FAMILY_STYLE);
	appetizer.setVegetarian(true);

	//Displaying appetizer details using GETTERS:
	std::cout << "Dish Name: " << appetizer.getName() << std::endl;
	std::cout << "Ingredients: ";
	for (const auto& ingredients : appetizer.getIngredients()) {
		std::cout << ingredients << " ";
	}std::cout << std::endl;
	std::cout << "Preparation Time: " << appetizer.getPrepTime() << " minutes" << std::endl;
	std::cout <<std::fixed<<std::setprecision(2) << "Price: $ " << appetizer.getPrice() << std::endl;
	std::cout << "Cuisine Type: " << appetizer.getCuisineType()<< std::endl;
	std::cout << "Spiciness Level: " << appetizer.getSpicinessLevel() << std::endl;
	std::cout << "Serving Style: " << appetizer.getServingStyle() << std::endl;
	std::cout << "Vegetarian: " << (appetizer.isVegetarian() ? "True" : "False") << std::endl;
	std::cout << "------------------------------------------\n\n";


	//2ND TEST (Main Course) Instantiating a main course with parameterized constructor and set values:
	MainCourse mainCourse;
	mainCourse.setName("Grilled Chicken");
	mainCourse.setIngredients({ "Chicken","Olive Oil","Garlic","Rosemary" });
	mainCourse.setPrepTime(30);
	mainCourse.setPrice(18.99);
	mainCourse.setCuisineType(Dish::CuisineType::AMERICAN);
	mainCourse.setCookingMethod(MainCourse::GRILLED);
	mainCourse.setProteinType("Chicken");
	
	//Setting side dishes
	MainCourse::SideDish mashedPotatoes = { "Mashed Potatoes", MainCourse::STARCHES };
	MainCourse::SideDish greenBeans = { "Green Beans", MainCourse::VEGETABLE };
	mainCourse.addSideDish(mashedPotatoes);
	mainCourse.addSideDish(greenBeans);
	mainCourse.setGlutenFree(true);

	//Displaying main course details using GETTERS:
	std::cout << "Dish Name: " << mainCourse.getName() << std::endl;
	std::cout << "Ingredients: ";
	int m = 0;
	for (const auto& ingredients : mainCourse.getIngredients()) {
		std::cout << ingredients;
		if (m != mainCourse.getIngredients().size() - 1) {
			std::cout << ", ";
		}
		m++;
	}std::cout << std::endl;
	std::cout << "Preparation Time: " << mainCourse.getPrepTime() << " minutes" << std::endl;
	std::cout << "Price: $ " << mainCourse.getPrice() << std::endl;
	std::cout << "Cuisine Type: " << mainCourse.getCuisineType() << std::endl;
	std::cout << "Cooking Method: " << mainCourse.getCookingMethod() << std::endl;
	std::cout << "Protein Type: " << mainCourse.getProteinType() << std::endl;
	std::cout << "Side Dishes: ";
	std::string separator = "";
	for (const auto& sideDish : mainCourse.getSideDishes()) {
		std::cout << separator << sideDish.name << " (" << sideDish.category << ")";
		separator = ", ";
	}std::cout << std::endl;
	std::cout << "Gluten-Free: " << (mainCourse.isGlutenFree() ? "True" : "False") << std::endl;
	std::cout << "------------------------------------------\n\n";



	//3RD TEST (Dessert) Instantiating a dessert with parameterized constructor:
	//Dessert dessert("Chocolate Cake", { "Flour","Sugar","Cocoa","Eggs" }, 45, 7.99, Dish::CuisineType::FRENCH, Dessert::SWEET, 9, false);
	Dessert dessert;
	dessert.setName("Chocolate Cake");
	dessert.setIngredients({"Flour", "Sugar", "Cocoa Powder", "Eggs"});
	dessert.setPrepTime(45);
	dessert.setPrice(7.99);
	dessert.setCuisineType(Dish::CuisineType::FRENCH);
	dessert.setFlavorProfile(Dessert::SWEET);
	dessert.setSweetnessLevel(9);
	dessert.setContainsNuts(false);


	//Displaying main course details using GETTERS:
	std::cout << "Dish Name: " << dessert.getName() << std::endl;
	std::cout << "Ingredients: ";
	int i = 0;
	for (const auto& ingredients : dessert.getIngredients()) {
		std::cout << ingredients;
		if (i != dessert.getIngredients().size() - 1) {
			std::cout << ", ";
		}
		i++;
	}
	std::cout << std::endl;
	std::cout << "Preparation Time: " << dessert.getPrepTime() << " minutes" << std::endl;
	std::cout << "Price: $ " << dessert.getPrice() << std::endl;
	std::cout << "Cuisine Type: " << dessert.getCuisineType() << std::endl;
	std::cout << "Flavor Profile: " << dessert.getFlavorProfile() << std::endl;
	std::cout << "Sweetness Level: " << dessert.getSweetnessLevel() << std::endl;
	std::cout << "Contains Nuts: " << (dessert.containsNuts() ? "True" : "False") << std::endl;
	std::cout << "------------------------------------------\n\n";

	return 0;

}