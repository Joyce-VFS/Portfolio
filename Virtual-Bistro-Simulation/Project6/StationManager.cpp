/**
 * @file StationManager.cpp
 * @brief This file contains the implementation of the `StationManager` class, which manages a dish preparation queue, dietary accommodations, and ingredient replenishment for a kitchen simulation.
 *
 * The `StationManager` class implements functionalities to manage a queue of dishes, handle dietary adjustments (such as vegetarian, gluten-free, and low-sodium), and manage backup ingredient stocks. This file includes the methods for adding dishes to the queue, preparing dishes, replenishing ingredients from backup stock, and displaying or clearing the dish queue.
 *
 * Key Functions:
 * - `addDishToQueue`: Adds a dish to the preparation queue. One version adjusts the dish based on dietary accommodations (if provided), while the other simply adds the dish without modifications.
 * - `prepareNextDish`: Attempts to prepare the next dish in the queue. If the dish can’t be prepared due to missing ingredients, it remains in the queue.
 * - `displayDishQueue`: Displays the names of the dishes currently in the preparation queue, ensuring the order of preparation is clearly visible.
 * - `clearDishQueue`: Empties the preparation queue and frees the dynamically allocated memory associated with the dishes.
 * - `replenishStationIngredientFromBackup`: Replenishes an ingredient in a station's stock from the backup ingredients, ensuring the ingredient exists and has enough quantity in backup.
 * - `addBackupIngredients`: Sets or replaces the backup ingredients stock with the provided list.
 * - `addBackupIngredient`: Adds a single ingredient to the backup stock, either increasing its quantity if it already exists or adding a new entry.
 * - `clearBackupIngredients`: Clears all backup ingredients from the stock, removing any items stored.
 * - `processAllDishes`: Processes all dishes in the queue, attempting to prepare them one by one and providing detailed output regarding each dish's preparation, including ingredient replenishment.
 *
 * The implementation also ensures that dynamic memory management is handled efficiently, with memory allocated for dishes when added to the queue and freed when no longer needed.
 *
 * @date 11/18/2024
 * @author: Joyce Vieira Ferreira Dos Santos
 */

#include "StationManager.hpp"
#include <iostream>
#include <queue>

// Default Constructor
StationManager::StationManager()
{
    // Initializes an empty station manager
}

// Adds a new station to the station manager
bool StationManager::addStation(KitchenStation *station)
{
    return insert(item_count_, station);
}

// Removes a station from the station manager by name
bool StationManager::removeStation(const std::string &station_name)
{
    for (int i = 0; i < item_count_; ++i)
    {
        if (getEntry(i)->getName() == station_name)
        {
            return remove(i);
        }
    }
    return false;
}

// Finds a station in the station manager by name
KitchenStation *StationManager::findStation(const std::string &station_name) const
{
    Node<KitchenStation *> *searchptr = getHeadNode();
    while (searchptr != nullptr)
    {
        if (searchptr->getItem()->getName() == station_name)
        {
            return searchptr->getItem();
        }
        searchptr = searchptr->getNext();
    }
    return nullptr;
}

// Moves a specified station to the front of the station manager list
bool StationManager::moveStationToFront(const std::string &station_name)
{
    // First, make sure the station exists
    if (findStation(station_name) == nullptr)
    {
        return false;
    }

    // If it's already at the front, return true
    if (getHeadNode()->getItem()->getName() == station_name)
    {
        return true;
    }

    Node<KitchenStation *> *searchptr = getHeadNode();
    while (searchptr != nullptr)
    {
        if (searchptr->getItem()->getName() == station_name)
        {
            // Make a copy of the station
            KitchenStation *station = searchptr->getItem();

            // Remove the station from its current position
            int pos = getStationIndex(searchptr->getItem()->getName());
            remove(pos);

            // Insert the station at the front
            insert(0, station);

            return true; // Exit after moving the station
        }

        searchptr = searchptr->getNext(); // Move to the next node
    }

    return false;
}

int StationManager::getStationIndex(const std::string &name) const
{
    Node<KitchenStation *> *searchptr = getHeadNode();
    int index = 0;
    while (searchptr != nullptr)
    {
        if (searchptr->getItem()->getName() == name)
        {
            return index;
        }
        searchptr = searchptr->getNext();
        index++;
    }
    return -1;
}

// Merges the dishes and ingredients of two specified stations
bool StationManager::mergeStations(const std::string &station_name1, const std::string &station_name2)
{
    KitchenStation *station1 = findStation(station_name1);
    KitchenStation *station2 = findStation(station_name2);
    if (station1 && station2)
    {
        // take all the dishes from station2 and add them to station1
        for (Dish *dish : station2->getDishes())
        {
            station1->assignDishToStation(dish);
        }
        // take all the ingredients from station2 and add them to station1
        for (Ingredient ingredient : station2->getIngredientsStock())
        {
            station1->replenishStationIngredients(ingredient);
        }
        // remove station2 from the list
        removeStation(station_name2);
        return true;
    }
    return false;
}

// Assigns a dish to a specific station
bool StationManager::assignDishToStation(const std::string &station_name, Dish *dish)
{
    KitchenStation *station = findStation(station_name);
    if (station)
    {
        return station->assignDishToStation(dish);
    }
    return false;
}

// Replenishes an ingredient at a specific station
bool StationManager::replenishIngredientAtStation(const std::string &station_name, const Ingredient &ingredient)
{
    KitchenStation *station = findStation(station_name);
    // debugging here lets see
    if (station)
    {
        for (Ingredient &stock_ingredient : station->getIngredientsStock())
        {
            if (stock_ingredient.name == ingredient.name)
            {
                stock_ingredient.quantity += ingredient.required_quantity;
                std::cout << "Updated" << stock_ingredient.name << "to" << stock_ingredient.quantity << " units.\n";
                return true;
            }
        }
        station->replenishStationIngredients(ingredient);
        std::cout << "Added" << ingredient.name << " to stock with" << ingredient.required_quantity << " units.\n";
        return true;
    }
    return false;
    // if (station)
    // {
    //     station->replenishStationIngredients(ingredient);
    //     return true;
    // }
    // return false;
}

// Checks if any station in the station manager can complete an order for a specific dish
bool StationManager::canCompleteOrder(const std::string &dish_name) const
{
    Node<KitchenStation *> *searchptr = getHeadNode();
    while (searchptr != nullptr)
    {
        if (searchptr->getItem()->canCompleteOrder(dish_name))
        {
            return true;
        }
        searchptr = searchptr->getNext();
    }
    return false;
}

// Prepares a dish at a specific station if possible
bool StationManager::prepareDishAtStation(const std::string &station_name, const std::string &dish_name)
{
    KitchenStation *station = findStation(station_name);
    if (station && station->canCompleteOrder(dish_name))
    {
        return station->prepareDish(dish_name);
    }
    return false;
}

// Task 1 Setters and Getters
// Implementation
/**
 * Retrieves the current dish preparation queue.
 * @return A copy of the queue containing pointers to Dish objects.
 * @post: The dish preparation queue is returned unchanged.
 */
std::queue<Dish *> StationManager::getDishQueue() const
{
    return dish_queue_;
}

/**
 * Sets the current dish preparation queue.
 * @param dish_queue A queue containing pointers to Dish objects.
 * @pre: The dish_queue contains valid pointers to dynamically allocated Dish objects.
 * @post: The dish preparation queue is replaced with the provided queue.
 */
void StationManager::setDishQueue(const std::queue<Dish *> &dish_queue)
{
    dish_queue_ = dish_queue;
}

/**
 * Retrieves the list of backup ingredients.
 * @return A vector containing Ingredient objects representing backup supplies.
 * @post: The list of backup ingredients is returned unchanged.
 */
std::vector<Ingredient> StationManager::getBackupIngredients() const
{
    return backup_ingredients_;
}

// helper function to access private member backup_ingredients_
/**
 * Sets the backup ingredients stock with the provided list of ingredients.
 * @param ingredients A vector of Ingredient objects to set as the backup stock.
 * @pre: None.
 * @post: The backup_ingredients_ vector is replaced with the provided ingredients.
 */
void StationManager::setBackupIngredients(const std::vector<Ingredient> &ingredients)
{
    backup_ingredients_ = ingredients;
}

// Task 2
// Implementation of the 2 overload functions
// the first adds dish to queue without any adjustment
// the second handles dietary accomodations
/**
 * Adds a dish to the preparation queue without dietary accommodations.
 * @param dish A pointer to a dynamically allocated Dish object.
 * @pre: The dish pointer is not null.
 * @post: The dish is added to the end of the queue.
 */
void StationManager::addDishToQueue(Dish *dish)
{
    if (dish != nullptr)
    {
        dish_queue_.push(dish);
    }
}

/**
 * Adds a dish to the preparation queue with dietary accommodations.
 * @param dish A pointer to a dynamically allocated Dish object.
 * @param request A DietaryRequest object specifying dietary accommodations.
 * @pre: The dish pointer is not null.
 * @post: The dish is adjusted for dietary accommodations and added to the end of the queue.
 */
void StationManager::addDishToQueue(Dish *dish, const Dish::DietaryRequest &request)
{
    if (dish != nullptr)
    {
        // then adjust based on the request
        dish->dietaryAccommodations(request);
        // add the adjusted dish to the queue
        dish_queue_.push(dish);
    }
}

// Task 3  Implement the prepareNextDish function in StationManager

/**
 * Prepares the next dish in the queue if possible.
 * @pre: The dish queue is not empty.
 * @post: The dish is processed and removed from the queue.
 * If the dish cannot be prepared, it stays in the queue
 * @return: True if the dish was prepared successfully; false otherwise.
 */
bool StationManager::prepareNextDish()
{
    // checking if its not empty first
    if (!dish_queue_.empty())
    {
        // getting next dish from queueueue
        Dish *next_dish = dish_queue_.front();

        // trying to prep the dish at an appropriate station
        bool prepared = false;

        // looping through all stations to see which can prepare the dish
        Node<KitchenStation *> *searchptr = getHeadNode();
        while (searchptr != nullptr && !prepared)
        {
            KitchenStation *station = searchptr->getItem();
            // checking if station can prep the dish
            if (station->canCompleteOrder(next_dish->getName()))
            {
                prepared = station->prepareDish(next_dish->getName());
            }
            searchptr = searchptr->getNext();
        }
        if (prepared)
        {
            // removing dish from queueueue
            dish_queue_.pop();
            return true; // dish prepared yay
        }
    }
    return false; // oh no dish not prepared
}

// Task 4 Implement the displayDishQueue function in StationManager
/**
* Displays all dishes in the preparation queue.
* @pre: None.
* @post: Outputs the names of the dishes in the queue in order (each name
is on its own line).
*/
void StationManager::displayDishQueue() const
{
    // Gonna copy the queue to iterate without modifying original
    std::queue<Dish *> copied_queue = dish_queue_;
    // Out the names of dishes in it
    while (!copied_queue.empty())
    {
        Dish *dish = copied_queue.front();
        std::cout << dish->getName() << std::endl;
        copied_queue.pop();
    }
}

// Task 5  Implement the clearDishQueue function in StationManager
/**
 * Clears all dishes from the preparation queue.
 * @pre: None.
 * @post: The dish queue is emptied and all allocated memory is freed.
 */
void StationManager::clearDishQueue()
{
    // clearing all dishes
    while (!dish_queue_.empty())
    {
        // free memory
        delete dish_queue_.front();
        // remove dish from queueueue
        dish_queue_.pop();
    }
}

// Task 6 Implement the replenishStationIngredientFromBackup function in StationManager
/**
 * Replenishes a specific ingredient at a given station from the backup
 ingredients stock by a specified quantity.
 * @param station_name A string representing the name of the station.
 * @param ingredient_name A string representing the name of the ingredient
 to replenish.
 * @param quantity An integer representing the amount to replenish.
 * @pre None.
 * @post If the ingredient is found in the backup ingredients stock and has
 sufficient quantity, it is added to the station's ingredient stock by the
 specified amount, and the function returns true.
 *       The quantity of the ingredient in the backup stock is decreased by
 the specified amount.
 *       If the ingredient in backup stock is depleted (quantity becomes
 zero), it is removed from the backup stock.
 *       If the ingredient does not have sufficient quantity in backup
 stock, or the ingredient or station is not found, returns false.
 * @return True if the ingredient was replenished from backup; false
 otherwise.
*/
bool StationManager::replenishStationIngredientFromBackup(const std::string &station_name, const std::string &ingredient_name, int quantity)
{
    // Going to find station by name
    KitchenStation *station = findStation(station_name);
    if (station == nullptr)
    {
        // when station not found
        return false;
    } // Finding the ingredient in backup stock
    for (size_t i = 0; i < backup_ingredients_.size(); i++)
    {
        Ingredient &backup_ingredient = backup_ingredients_[i];
        if (backup_ingredient.name == ingredient_name)
        {
            // checking if theres enough quantity
            if (backup_ingredient.quantity >= quantity)
            {
                Ingredient ingredient_to_replenish = {ingredient_name, quantity, 0, backup_ingredient.price};
                station->replenishStationIngredients(ingredient_to_replenish);

                // now gonna decrease quantity
                backup_ingredient.quantity -= quantity;

                // remove ingredient if there nothing left
                if (backup_ingredient.quantity == 0)
                {
                    backup_ingredients_.erase(backup_ingredients_.begin() + i);
                }
                return true;
            }
            else
            {
                return false;
            }
        }
    }
    return false;
}

// Task 7 implement addBackupIngredients Function
/**
 * Sets the backup ingredients stock with the provided list of ingredients.
 * @param ingredients A vector of Ingredient objects to set as the backup stock.
 * @pre: None.
 * @post: The backup_ingredients_ vector is replaced with the provided ingredients.
 * @return: True if the ingredients were added successfully.
 */
bool StationManager::addBackupIngredients(const std::vector<Ingredient> &ingredients)
{
    // First things first, let me replace backup ingredients with the list given
    backup_ingredients_ = ingredients;
    // if successful true
    return true;
}

// Task 8 implement addBackupIngredient Function ///////<NO 'S'
/**
 * Adds a single ingredient to the backup ingredients stock.
 * @param ingredient An Ingredient object to add to the backup stock.
 * @pre: None.
 * @post: If the ingredient already exists, its quantity is increased. Otherwise, it is added to the backup stock.
 * @return: True if the ingredient was added or updated successfully.
 */
bool StationManager::addBackupIngredient(const Ingredient &ingredient)
{
    // First things first again, lets check if ingredient exist in the stock
    for (auto &backup_ingredient : backup_ingredients_)
    {
        if (backup_ingredient.name == ingredient.name)
        {
            // Increase qnt if exist
            backup_ingredient.quantity += ingredient.quantity;
            return true;
        }
    }
    // Now if it doesnt exist is another story
    backup_ingredients_.push_back(ingredient);
    return true;
}

// Task 9
/**
 * Empties the backup ingredients vector.
 * @pre: None.
 * @post: The `backup_ingredients_` vector is empty.
 */
void StationManager::clearBackupIngredients()
{
    backup_ingredients_.clear();
}

// Task 10
/**
 * Processes all dishes in the queue and displays detailed results.
 * @pre: None.
 * @post: All dishes are processed, and detailed information is displayed.
 *        If a dish cannot be prepared even after replenishing ingredients, it stays in the queue.
 */
void StationManager::processAllDishes()
{
    // Gonna make a temp queue to hold dishes
    std::queue<Dish *> temporaryQueue;
    // Iterate through it
    while (!dish_queue_.empty())
    {
        Dish *currentDish = dish_queue_.front();
        dish_queue_.pop();
        std::cout << "PREPARING DISH: " << currentDish->getName() << "\n";

        bool prepared = false;
        Node<KitchenStation *> *searchptr = getHeadNode();

        while (searchptr != nullptr)
        {
            KitchenStation *station = searchptr->getItem();
            std::cout << station->getName() << " attempting to prepare " << currentDish->getName() << "...\n";
            if (station->canCompleteOrder(currentDish->getName()))
            {
                if (station->prepareDish(currentDish->getName()))
                {

                    // // testting something real quick
                    // std::cout << "-- STATION CAN PREP DISH.\n";
                    std::cout << station->getName() << ": Successfully prepared " << currentDish->getName() << ".\n\n";
                    prepared = true;
                    break;
                }
                else
                {
                    std::cout << station->getName() << ": Insufficient ingredients. Replenishing ingredients...\n";
                    bool replenished = true;
                    // Lets try to replenish
                    for (const auto &ingredient : currentDish->getIngredients())
                    {
                        // debbuging here
                        std::cout << "               trying to replenish this:" << ingredient.name << ", required: " << ingredient.required_quantity << ", available: " << ingredient.quantity << std::endl;
                        // trying to handle Ingredient obj
                        Ingredient replenishingIngredient(ingredient.name, ingredient.required_quantity, ingredient.required_quantity, ingredient.price);
                        if (!replenishIngredientAtStation(station->getName(), replenishingIngredient))
                        {
                            replenished = false;
                            break;
                        }
                    }
                    if (replenished)
                    {
                        std::cout << station->getName() << ": Ingredients replenished.\n";
                        if (station->prepareDish(currentDish->getName()))
                        {
                            std::cout << station->getName() << ": Successfully prepared " << currentDish->getName() << ".\n\n";
                            prepared = true;
                            break;
                        }
                    }
                    else
                    {
                        std::cout << station->getName() << ": Unable to replenish ingredients. Failed to prepare " << currentDish->getName() << ".\n";
                    }
                }
            }
            else
            {
                std::cout << station->getName() << ": Dish not available. Moving to next station...\n";
            }
            searchptr = searchptr->getNext();
        }
        // If dish was not prep, add back to temporaryQueue
        if (!prepared)
        {
            std::cout << currentDish->getName() << " was not prepared.\n\n";
            temporaryQueue.push(currentDish);
        }
        else
        {
            delete currentDish;
        }
    }
    dish_queue_ = temporaryQueue;
    std::cout << "\nAll dishes have been processed.\n";
}