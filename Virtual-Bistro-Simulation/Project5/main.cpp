/**
 * @file main.cpp
 * @brief This file contains the main entry point for the virtual bistro simulation application.
 *
 * The main function sets up the bistro environment by creating various dishes, initializing kitchen stations, and managing orders.
 * It demonstrates the use of the `Dish`, `KitchenStation`, and `StationManager` classes by simulating a realistic bistro operation,
 * including dish preparation and ingredient management.
 *
 * The program interacts with the user through console input and output, providing a simple interface to test and showcase the functionality
 * of the implemented classes.
 *
 * @date 11/10/2024
 * @author: Joyce Vieira Ferreira Dos Santos
 */

#include "Dish.hpp"
#include "KitchenStation.hpp"
#include "StationManager.hpp"
#include <iostream>
#include <vector>

int main()
{
    // Creating ingredients
    Ingredient tomato = {"Tomato", 10, 2, 0.5};
    Ingredient pasta = {"Pasta", 8, 3, 1.5};

    // Creating a dish with Ingredient objects instead of just names
    Dish *lasagna = new Dish("Lasagna", {tomato, pasta}, 30, 10.4, Dish::CuisineType::ITALIAN);

    // // Setting required ingredients for lasagna
    lasagna->setIngredients({tomato, pasta});

    // // Making a KitchenStation and assigning lasagna to it
    KitchenStation pastaStation("Pasta Station");
    pastaStation.assignDishToStation(lasagna);
    // std::cout << "here3";
    pastaStation.replenishStationIngredients(tomato);
    pastaStation.replenishStationIngredients(pasta);

    // Checking if station can complete the order
    std::cout << "Can lasagna be completed? : " << (pastaStation.canCompleteOrder("Lasagna") ? "Yes" : "No") << std::endl;

    // // Preparing the dish
    // bool prepared = pastaStation.prepareDish("Lasagna");
    // std::cout << "Lasagna prep: " << (prepared ? "Yes" : "No") << std::endl;

    // // Checking quantities after preparation
    // std::vector<Ingredient> leftIngredients = pastaStation.getIngredientsStock();
    // std::cout << "The remaining ingredients in Pasta Station after making lasagna are: " << std::endl;
    // for (std::size_t i = 0; i < leftIngredients.size(); i++)
    // {
    //     std::cout << "- " << leftIngredients[i].name << ": " << leftIngredients[i].quantity << std::endl;
    // }

    // // Trying to find and prepare the dish from StationManager
    // StationManager stationManager;
    // stationManager.addStation(&pastaStation);

    // std::cout << "\nCheck from StationManager:" << std::endl;
    // KitchenStation *foundStation = stationManager.findStation("Pasta Station");
    // if (foundStation != nullptr)
    // {
    //     std::cout << "Pasta Station found" << std::endl;
    //     bool prepedAgain = foundStation->prepareDish("Lasagna");
    //     std::cout << "Lasagna prepped again: " << (prepedAgain ? "Yes" : "No") << std::endl;
    // }
    // else
    // {
    //     std::cout << "Pasta Station not found" << std::endl;
    // }

    // Clean up and exit
    // stationManager.clear();
    return 0;
}
