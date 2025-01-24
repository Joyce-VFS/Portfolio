//Name: Joyce Vieira Ferreira Dos Santos
//Date: 10/04/2024
//Description: Here I will write my test case to test functionality of Kitchen, and check whether implementation behaves as expected.

#include "Kitchen.hpp"
#include "Dish.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

//Main to test all unique methods of Kitchen subclass.
int main() {

	//1st TEST will be responsible for testing the newOrder and kitchenReport methods

	//creating a kitchen obj here
	Kitchen kitchen;
	//creating Dish obj here (parameterized constructor)
	Dish dish1("Coxinha", { "Cheese","Catupiry","Dough", "Olive Oil" }, 30, 9.99, Dish::CuisineType::OTHER);
	Dish dish2("Pizza", { "Burrata","Fresh Tomato Sauce", "Dough", "Basil" }, 15, 17.99, Dish::CuisineType::ITALIAN);
	Dish dish3("Duck a l'Orange", { "Duck","Onion","Carrot","Thyme","Flour", "Orange Juice", "Orange Marmalade" }, 130, 50, Dish::CuisineType::FRENCH);
	Dish dish4("Merica", { "Beef","Onion","Carrot","Bacon", "Peanut Butter","Jelly"}, 65, 25.78, Dish::CuisineType::AMERICAN);


	//adding the dishes to the kitchen
	kitchen.newOrder(dish1);
	kitchen.newOrder(dish2);
	kitchen.newOrder(dish4);
	
	//displaying dishes currently in the kitchen (kitchenReport)
	kitchen.kitchenReport();
	
	//serveDish to serve (remove) a dish (Coxinha)
	kitchen.serveDish(dish1);
	
	//displaying dishes after serving coxinha
	kitchen.kitchenReport();
	
	//removing dishes with prep time < 16 minutes)
	int removedBelow16 = kitchen.releaseDishesBelowPrepTime(16);
	//std::cout << "Number of dishes removed: " << removedBelow16 << std::endl;
	
	//displaying dishes after releasing dish with prep time < 16
	kitchen.kitchenReport();

	//releaseDishesOfCuisineType (removing all ITALIAN dishes)
	int removedItalian = kitchen.releaseDishesOfCuisineType("ITALIAN");
	//std::cout << "Number of ITALIAN dishes removed: " << removedItalian << std::endl;

	//displaying dishes after releasing all ITALIAN dishes
	kitchen.kitchenReport();

	//Adding a more elaborate dish (Duck dish3) to test elaborateDishCount and getPrepTimeSum
	kitchen.newOrder(dish3);

	//testing total preparation time sum
	std::cout << "\nTotal Preparation Time Sum: " << kitchen.getPrepTimeSum() << " minutes\n";

	//testing number of elaborate dishes (prep time >= 60 and 5+ ingredients)
	std::cout << "Number of elaborate dishes: " << kitchen.elaborateDishCount() << std::endl;

	//testing average time preparation
	std::cout << "Average Prep Time: " << kitchen.calculateAvgPrepTime() << " minutes\n";

	//testing percentage of elaborate dishes
	std::cout << "Percentage of elaborate dishes: " << kitchen.calculateElaboratePercentage() << std::endl;

	//displaying dishes after adding more elaborate dish (Duck)
	kitchen.kitchenReport();

	return 0;
}