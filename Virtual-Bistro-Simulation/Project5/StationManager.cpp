/**
 * @file StationManager.cpp
 * @brief This file contains the implementation of the `StationManager` class, which manages a collection of kitchen stations
 * using a linked list structure.
 *
 * The `StationManager` class provides functionality for managing multiple `KitchenStation` objects, including adding new stations,
 * removing stations by name, moving stations within the list, and merging stations. It utilizes linked list methods for efficient traversal
 * and management.
 *
 * @date 11/10/2024
 * @author: Joyce Vieira Ferreira Dos Santos
 */

#include "StationManager.hpp"
#include <iostream>

/**
 * Default Constructor
 * @post: Initializes an empty station manager.
 */
StationManager::StationManager()
{
}

/**
 * Destructor
 * @post: Deallocates all kitchen stations and clears the list.
 */
StationManager::~StationManager()
{
    // for (int i = 0; i < getLength(); i++)
    // {
    //     delete getEntry(i);
    // }
    // clear();
}

/**
* Adds a new station to the station manager.
* @param station A pointer to a KitchenStation object.
* @post: Inserts the station into the linked list.
* @return: True if the station was successfully added; false
otherwise.
*/
bool StationManager::addStation(KitchenStation *station)
{
    // Checking if station is not null and adding to the end of the list
    if (!station)
        return false;
    insert(getLength(), station);
    return true;
}

/**
* Removes a station from the station manager by name.
* @param station_name A string representing the station's name.
* @post: Removes the station from the list and deallocates it.
* @return: True if the station was found and removed; false
otherwise.
*/
bool StationManager::removeStation(const std::string &station_name)
{
    for (int i = 0; i < getLength(); i++)
    {
        KitchenStation *station = getEntry(i);
        if (station->getName() == station_name)
        {
            delete station;
            remove(i);
            return true;
        }
    }
    return false;
}

/**
 * Finds a station in the station manager by name.
 * @param station_name A string representing the station's name.
 * @return: A pointer to the KitchenStation if found; nullptr
otherwise.
 */
KitchenStation *StationManager::findStation(const std::string &station_name) const
{
    for (int i = 0; i < getLength(); i++)
    {
        KitchenStation *station = getEntry(i);
        if (station->getName() == station_name)
        {
            return station;
        }
    }
    return nullptr;
}

/**
* Moves a specified station to the front of the station manager
list.
* @param station_name A string representing the station's name.
* @post: The station is moved to the front of the list if it
exists.
* @return: True if the station was found and moved; false
otherwise.
*/
bool StationManager::moveStationToFront(const std::string &station_name)
{
    for (int i = 0; i < getLength(); i++)
    {
        KitchenStation *station = getEntry(i);
        if (station->getName() == station_name)
        {
            remove(i);
            insert(0, station);
            return true;
        }
    }
    return false;
}

/**
* Merges the dishes and ingredients of two specified stations.
* @param station_name1 The name of the first station.
* @param station_name2 The name of the second station.
* @post: The second station is removed from the list, and its
contents are added to the first station.
* @return: True if both stations were found and merged; false
otherwise.
*/
bool StationManager::mergeStations(const std::string &station_name1, const std::string &station_name2)
{
    KitchenStation *station1 = findStation(station_name1);
    KitchenStation *station2 = findStation(station_name2);

    // When one or both stations not found
    if (!station1 || !station2)
        return false;

    // adding all dishes from station2 to station1
    std::vector<Dish *> dishesIn2 = station2->getDishes();
    for (std::size_t i = 0; i < dishesIn2.size(); i++)
    {
        Dish *dish = dishesIn2[i];
        station1->assignDishToStation(dish);
    }

    // adding all ingredients from station2 to station1
    std::vector<Ingredient> ingredientsIn2 = station2->getIngredientsStock();
    for (std::size_t i = 0; i < ingredientsIn2.size(); i++)
    {
        Ingredient ingredient = ingredientsIn2[i];
        station1->replenishStationIngredients(ingredient);
    }

    removeStation(station_name2);
    return true;
}

/**
 * Assigns a dish to a specific station.
* @param station_name A string representing the station's name.
 * @param dish A pointer to a Dish object.
 * @post: Assigns the dish to the specified station.
 * @return: True if the station was found and the dish was assigned;
false otherwise.
 */
bool StationManager::assignDishToStation(const std::string &station_name, Dish *dish)
{
    KitchenStation *station = findStation(station_name);
    if (!station)
        return false;
    return station->assignDishToStation(dish);
}

/**
 * Replenishes an ingredient at a specific station.
 * @param station_name A string representing the station's name.
 * @param ingredient An Ingredient object.
 * @post: Replenishes the ingredient stock at the specified station.
 * @return: True if the station was found and the ingredient was
replenished; false otherwise.
 */
bool StationManager::replenishIngredientAtStation(const std::string &station_name, const Ingredient &ingredient)
{
    KitchenStation *station = findStation(station_name);
    if (!station)
        return false;
    return station->replenishStationIngredients(ingredient);
}

/**
 * Checks if any station in the station manager can complete an
order for a specific dish.
 * @param dish_name A string representing the name of the dish.
 * @return: True if any station can complete the order; false
otherwise.
 */
bool StationManager::canCompleteOrder(const std::string &dish_name) const
{
    for (int i = 0; i < getLength(); i++)
    {
        KitchenStation *station = getEntry(i);
        if (station->canCompleteOrder(dish_name))
        {
            return true;
        }
    }
    return false;
}

/**
 * Prepares a dish at a specific station if possible.
 * @param station_name A string representing the station's name.
 * @param dish_name A string representing the name of the dish.
 * @post: If the dish can be prepared, reduces the quantities of the
used ingredients at the station.
 * @return: True if the dish was prepared successfully; false
otherwise.
 */
bool StationManager::prepareDishAtStation(const std::string &station_name, const std::string &dish_name)
{
    KitchenStation *station = findStation(station_name);
    if (!station)
        return false;
    return station->prepareDish(dish_name);
}
