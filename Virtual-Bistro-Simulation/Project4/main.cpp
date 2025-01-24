#include <iostream>
#include "Appetizer.hpp"
#include "MainCourse.hpp"
#include "Dish.hpp"
#include "Dessert.hpp"
#include "Kitchen.hpp"

int main()
{

	// Kitchen obj
	Kitchen kitchen("testingcsv.csv");
	Dish::DietaryRequest dietary_request{true, false, true, false, true};
	kitchen.dietaryAdjustment(dietary_request);
	kitchen.displayMenu();

	// Creating side dish here
	MainCourse::SideDish saladSideDish{"Greek Salad", MainCourse::Category::SALAD};
	MainCourse::SideDish breadstickSideDish{"Breadstick", MainCourse::Category::BREAD};
	// Instance for each dish type goes here

	Appetizer appetizer("Coxinha", {"Cheese", "Catupiry", "Dough", "Olive Oil", "Chicken", "Meat", "Beef"}, 30, 9.99, Dish::CuisineType::OTHER, Appetizer::ServingStyle::FAMILY_STYLE, 3, true);
	MainCourse mainCourse("Pizza", {"Burrata", "Fresh Tomato Sauce", "Dough", "Basil"}, 15, 17.99, Dish::CuisineType::ITALIAN, MainCourse::CookingMethod::BAKED, "Burrata", {saladSideDish, breadstickSideDish}, false);
	Dessert dessert("Brigadeiro", {"Condensed milk", "Eggs", "Almonds", "Milk", "Cocoa Powder", "Butter", "Chocolate Chips"}, 20, 2.990, Dish::CuisineType::OTHER, Dessert::FlavorProfile::SWEET, 5, true);

	// Dietary accomodations here
	Dish::DietaryRequest dietaryRequest;
	dietaryRequest.vegetarian = true;
	dietaryRequest.low_sodium = true;
	dietaryRequest.gluten_free = true;
	dietaryRequest.nut_free = true;
	dietaryRequest.low_sugar = true;
	dietaryRequest.vegan = true;

	// Applying accomodations here
	appetizer.dietaryAccommodations(dietaryRequest);
	mainCourse.dietaryAccommodations(dietaryRequest);
	dessert.dietaryAccommodations(dietaryRequest);

	// Displaying here
	std::cout << "Appetizer: " << std::endl;
	appetizer.display();

	std::cout << "\nMain Course: " << std::endl;
	mainCourse.display();

	std::cout << "\nDessert: " << std::endl;
	dessert.display();

	return 0;
}
