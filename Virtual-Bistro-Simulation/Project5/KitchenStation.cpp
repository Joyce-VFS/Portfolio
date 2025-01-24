/**
 * @file KitchenStation.cpp
 * @brief This file contains the implementation of the `KitchenStation` class, which simulates a kitchen station in the virtual bistro.
 *
 * The `KitchenStation` class manages a list of assigned dishes and the ingredient stock. It implements functions for replenishing stock,
 * checking if an order can be completed, and preparing dishes while updating ingredient quantities.
 *
 * @date 11/10/2024
 * @author: Joyce Vieira Ferreira Dos Santos
 */

#include "KitchenStation.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

// TASK 3 END
/**
 * Default Constructor
 * @post: Initializes an empty kitchen station with default values.
 */
KitchenStation::KitchenStation() : station_name_("UNKNOWN") {}

/**
 * Parameterized Constructor
 * @param station_name A string representing the station's name.
 * @post: Initializes a kitchen station with the given name.
 */
KitchenStation::KitchenStation(const std::string &station_name) : station_name_(station_name) {}

/**
 * Destructor
 * @post: Deallocates all dynamically allocated dishes in the
station.
 */
KitchenStation::~KitchenStation()
{
    for (Dish *dish : dishes_)
    {
        delete dish;
        dish = nullptr;
    }
    // dishes_.clear();
}

/**
 * Retrieves the name of the kitchen station.
 * @return: The name of the station.
 */
std::string KitchenStation::getName() const
{
    return station_name_;
}

/**
 * Sets the name of the kitchen station.
 * @param name A string representing the new station name.
 * @post: Updates the station's name.
 */
void KitchenStation::setName(const std::string &name)
{
    station_name_ = name;
}

/**
 * Retrieves the list of dishes assigned to the kitchen station.
 * @return A vector of pointers to Dish objects assigned to the station.
 */
std::vector<Dish *> KitchenStation::getDishes() const
{
    return dishes_;
}

/**
 * Retrieves the ingredient stock available at the kitchen station.
* @return A vector of Ingredient objects representing the station's
ingredient stock.
 */
std::vector<Ingredient> KitchenStation::getIngredientsStock() const
{
    return ingredients_stock_;
}

// Assigning dish to station HERE
/**
* Assigns a dish to the station.
* @param dish A pointer to a Dish object.
* @post: Adds the dish to the station's list of dishes if not
already present.
* @return: True if the dish was added successfully; false
otherwise.
*/
bool KitchenStation::assignDishToStation(Dish *dish)
{
    for (std::size_t i = 0; i < dishes_.size(); i++)
    {
        // current Dish pointer
        Dish *existing_dish = dishes_[i];

        // gonna compare names of dishes to check for duplicates
        if (existing_dish->getName() == dish->getName())
        {
            // std::cout << "assign4";
            return false; // If dish with same name exist then return false
        }
    }

    // when no matching dish is found, add the new dish to the station
    dishes_.push_back(dish);
    // std::cout << "assign5";
    return true; // new dish added
}

// Replenishing station's ingredients HERE
/**
 * Replenishes the station's ingredient stock.
 * @param ingredient An Ingredient object.
 * @post: Adds the ingredient to the station's stock or updates the
quantity if it already exists.
 */
bool KitchenStation::replenishStationIngredients(const Ingredient &ingredient)
{
    // Gonna look through ingredients_stock_ vector for matching ingredient
    for (Ingredient &stock : ingredients_stock_)
    {
        // If name match
        if (stock.name == ingredient.name)
        {
            // Update quantity
            stock.quantity += ingredient.quantity;
            // std::cout << "here";
            return true; // replenished
        }
    }
    // if no match, add new ingredient to stock
    ingredients_stock_.push_back(ingredient);
    // std::cout << "here2";
    return true; // new ingredient added
}

// Can Complete Order HERE
/**
* Checks if the station can complete an order for a specific dish.
* @param dish_name A string representing the name of the dish.
* @return: True if the station has the dish assigned and all
required ingredients are in stock; false otherwise.
*/
bool KitchenStation::canCompleteOrder(const std::string &dish_name) const
{
    // Looking through each dish assigned
    // Checking if all required ingredients are in stock
    // checking if each required ingredient is in stock
    // Checking if stock has enough of the required ingredients
    // if required ingredient is not found or not enough, then false
    // Everything available and good, then true
    // No matching dish, then false
    for (Dish *dish : dishes_)
    {
        if (dish->getName() == dish_name)
        {
            for (const Ingredient &required : dish->getIngredients())
            {
                const Ingredient *stock_ingredient = findIngredient(required.name);
                if (!stock_ingredient || stock_ingredient->quantity < required.required_quantity)
                {
                    return false;
                }
            }
            return true;
        }
    }
    return false;
}

/**
* Prepares a dish if possible.
* @param dish_name A string representing the name of the dish.
* @post: If the dish can be prepared, reduce the quantities of the
used ingredients accordingly. If the stock ingredient is depleted to
0, remove the ingredient from the Kitchen Station.
* @return: True if the dish was prepared successfully; false
otherwise.
*/
bool KitchenStation::prepareDish(const std::string &dish_name)
{
    // Lets check whether the station can complete the order for specific dish
    if (!canCompleteOrder(dish_name))
    {
        return false;
    }
    // finding the sidh to be prep by looping through the assigned dishes
    for (Dish *dish : dishes_)
    {
        // if matching dish is found
        if (dish->getName() == dish_name)
        {
            // then loop through each ingredient
            for (const Ingredient &required : dish->getIngredients())
            {
                // finding the correponding ingredient in stock
                const Ingredient *stock_ingredient = findIngredient(required.name);
                if (stock_ingredient != nullptr)
                {
                    // manually reducing the quantity in stock
                    for (Ingredient &stock : ingredients_stock_)
                    {
                        if (stock.name == required.name)
                        {
                            stock.quantity -= required.required_quantity;
                            break;
                        }
                    }
                }
            }

            // removing ingredient from stock if now the quantity is zero
            ingredients_stock_.erase(std::remove_if(ingredients_stock_.begin(), ingredients_stock_.end(), [](const Ingredient &ingredient)
                                                    { return ingredient.quantity <= 0; }),
                                     ingredients_stock_.end());
            // when dish is sucessfully preped
            return true;
        }
    }
    // dish not found in station
    return false;
}

// Helper function findIngredient
const Ingredient *KitchenStation::findIngredient(const std::string &ingredient_name) const
{
    for (const Ingredient &ingredient : ingredients_stock_)
    {

        if (ingredient.name == ingredient_name)
        {
            // return pointer to ingredient found
            return &ingredient;
        }
    }
    // return nullptr if no matching ingredient found
    return nullptr;
}
