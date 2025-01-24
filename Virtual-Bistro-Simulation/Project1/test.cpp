//Name: Joyce Vieira Ferreira Dos Santos
//Date: 9/15/2024
//Description: Here I will write my test case to test functionality of Dish class, and check whether implementation behaves as expected.

#include "Dish.hpp"
#include <iostream>
#include <iomanip> //Header required for price formatting (output to two decimal places).
#include <string>
#include <stdlib.h>
#include <vector>

//Main will test functionality of both constructors, accessors and mutators methods.
int main() {
	//1ST TEST (Default Const)
	//std::cout << "1st Test: Default constructor\n";
	Dish defaultDish;				//Creating a dish obj using default constructor
	defaultDish.setPrepTime(30);	//Setting prep time using mutator method
	defaultDish.setPrice(9.99);	//Setting price using mutator method
	//Displaying default dish details:
	//std::cout << "Expected Output:\n";
	//std::cout << "Dish Name: UNKNOWN\nIngredients: \nPreparation Time: 45 minutes\nPrice: $12.75\nCuisine Type: OTHER\n";
	//std::cout << "Actual Output:\n";
	defaultDish.display();			//Using dispaly function to print details of the dish.
	std::cout << "------------------------------------------\n\n";



	//2ND TEST (Parameterized Const)
	//std::cout << "2nd Test: Parameterized Constructor\n";
	Dish carbonaraDish("Pasta Carbonara", { "Pasta", "Eggs", "Pancetta", "Parmesan", "Pepper" }, 20, 12.50, Dish::ITALIAN);
	//Display parameterized dish
	//std::cout << "Expected Output\n";
	//std::cout << "Dish Name: Pasta Carbonara\nIngredients: Pasta, Eggs, Pancetta, Parmesan, Pepper\nPreparation Time: 20 minutes\nPrice: $12.50\nCuisine Type: ITALIAN\n";
	//std::cout << "Actual Output:\n";
	carbonaraDish.display();		//Using display function to print parameterized dish details.
	std::cout << "------------------------------------------------\n\n";


	/*
	//3RD TEST (Accessors and Mutators)
	std::cout << "3rd Test: Accessor and Mutator Methods\n";
	Dish customDish;
	//Using mutator here (Setters)
	customDish.setName("Feijoada");
	customDish.setIngredients({ "Black Beans", "Kale", "Yuka", "Pork", "Cumin", "Bay Leave", "Onions", "Garlic", "Thyme" });
	customDish.setPrepTime(45);
	customDish.setPrice(48.50);
	customDish.setCuisineType(Dish::OTHER);		//Brazilian cuisine (setting to OTHER since the actual cuisine its not defined)
	//Using accessor here (Getters)
	std::cout << "Dish Name: " << customDish.getName() << "\n";
	std::cout << "Ingredients: ";
	int i = 0;
	for (const std::string& ingredients : customDish.getIngredients()) {
		std::cout << ingredients;
		if (i != customDish.getIngredients().size() - 1) {
			std::cout << ", ";
		} 
		i++;
	}
	std::cout << "\nPreparation Time: " << customDish.getPrepTime() << " minutes\n";
	std::cout << "Price: $" << customDish.getPrice() << "\n";
	std::cout << "Cuisine Type: " << customDish.getCuisineType() << "\n";
	*/
	return 0;

}