/**
 * @file StationManager.hpp
 * @brief This file contains the declaration of the `StationManager` class, which manages a dish preparation queue, dietary accommodations, and ingredient replenishment for a kitchen simulation.
 *
 * The `StationManager` class uses a queue to manage dishes in a First-In-First-Out (FIFO) order, ensuring dishes are prepared in the sequence they were added. It provides functionalities for adding dishes to the queue, processing them, and handling dietary accommodations, such as vegetarian, gluten-free, and low-sodium options.
 *
 * Additionally, the class manages backup ingredients for replenishing station ingredients when stocks are low. It includes methods for handling ingredient replenishment from backup, as well as managing and displaying the dish preparation queue.
 *
 * The `StationManager` class also incorporates dynamic memory allocation to efficiently manage memory for dynamically allocated `Dish` objects and their ingredients. Functions are provided for adding dishes to the queue, preparing the next dish, and clearing the queue, as well as managing and replenishing backup ingredient stocks.
 *
 * Key Functions:
 * - `addDishToQueue`: Adds a dish to the queue with or without dietary accommodations.
 * - `prepareNextDish`: Prepares the next dish in the queue, if possible.
 * - `displayDishQueue`: Displays the names of all dishes in the queue.
 * - `clearDishQueue`: Clears the dish queue and frees allocated memory.
 * - `replenishStationIngredientFromBackup`: Replenishes a specific ingredient at a station from backup stock.
 * - `addBackupIngredients`: Sets the backup ingredients stock.
 * - `addBackupIngredient`: Adds a single ingredient to the backup stock.
 * - `clearBackupIngredients`: Clears the backup ingredients stock.
 * - `processAllDishes`: Processes all dishes in the queue and displays detailed results.
 *
 * @date 11/18/2024
 * @author: Joyce Vieira Ferreira Dos Santos
 */

#ifndef STATIONMANAGER_HPP
#define STATIONMANAGER_HPP

#include "LinkedList.hpp"
#include "KitchenStation.hpp"
#include "Dish.hpp"
#include <string>
#include <queue> //for dish_queue_
#include <vector>

class StationManager : public LinkedList<KitchenStation *>
{
public:
    /**
     * Default Constructor
     * @post: Initializes an empty station manager.
     */
    StationManager();

    /**
     * Adds a new station to the station manager.
     * @param station A pointer to a KitchenStation object.
     * @post: Inserts the station into the linked list.
     */
    bool addStation(KitchenStation *station);

    /**
     * Removes a station from the station manager by name.
     * @param station_name A string representing the station's name.
     * @post: Removes the station from the list and deallocates it.
     * @return: True if the station was found and removed; false otherwise.
     */
    bool removeStation(const std::string &station_name);

    /**
     * Finds a station in the station manager by name.
     * @param station_name A string representing the station's name.
     * @return: A pointer to the KitchenStation if found; nullptr otherwise.
     */
    KitchenStation *findStation(const std::string &station_name) const;

    /**
     * Moves a specified station to the front of the station manager list.
     * @param station_name A string representing the station's name.
     * @post: The station is moved to the front of the list if it exists.
     * @return: True if the station was found and moved; false otherwise.
     */
    bool moveStationToFront(const std::string &station_name);

    /**
     * Merges the dishes and ingredients of two specified stations.
     * @param station_name1 The name of the first station.
     * @param station_name2 The name of the second station.
     * @post: The second station is removed from the list, and its contents are added to the first station.
     * @return: True if both stations were found and merged; false otherwise.
     */
    bool mergeStations(const std::string &station_name1, const std::string &station_name2);

    /**
     * Assigns a dish to a specific station.
     * @param station_name A string representing the station's name.
     * @param dish A pointer to a Dish object.
     * @post: Assigns the dish to the specified station.
     * @return: True if the station was found and the dish was assigned; false otherwise.
     */
    bool assignDishToStation(const std::string &station_name, Dish *dish);

    /**
     * Replenishes an ingredient at a specific station.
     * @param station_name A string representing the station's name.
     * @param ingredient An Ingredient object.
     * @post: Replenishes the ingredient stock at the specified station.
     * @return: True if the station was found and the ingredient was replenished; false otherwise.
     */
    bool replenishIngredientAtStation(const std::string &station_name, const Ingredient &ingredient);

    /**
     * Checks if any station in the station manager can complete an order for a specific dish.
     * @param dish_name A string representing the name of the dish.
     * @return: True if any station can complete the order; false otherwise.
     */
    bool canCompleteOrder(const std::string &dish_name) const;

    /**
     * Prepares a dish at a specific station if possible.
     * @param station_name A string representing the station's name.
     * @param dish_name A string representing the name of the dish.
     * @post: If the dish can be prepared, reduces the quantities of the used ingredients at the station.
     * @return: True if the dish was prepared successfully; false otherwise.
     */
    bool prepareDishAtStation(const std::string &station_name, const std::string &dish_name);

    // Task 1 Setters and Getters
    // Declaration
    /**
     * Retrieves the current dish preparation queue.
     * @return A copy of the queue containing pointers to Dish objects.
     * @post: The dish preparation queue is returned unchanged.
     */
    std::queue<Dish *> getDishQueue() const;

    /**
     * Retrieves the list of backup ingredients.
     * @return A vector containing Ingredient objects representing backup supplies.
     * @post: The list of backup ingredients is returned unchanged.
     */
    std::vector<Ingredient> getBackupIngredients() const;

    // helper function to access private member backup_ingredients_
    /**
     * Sets the backup ingredients stock with the provided list of ingredients.
     * @param ingredients A vector of Ingredient objects to set as the backup stock.
     * @pre: None.
     * @post: The backup_ingredients_ vector is replaced with the provided ingredients.
     */
    void setBackupIngredients(const std::vector<Ingredient> &ingredients);

    /**
    * Sets the current dish preparation queue.
    * @param dish_queue A queue containing pointers to Dish objects.
    * @pre: The dish_queue contains valid pointers to dynamically allocated
    Dish objects.
    * @post: The dish preparation queue is replaced with the provided
    queue.
    */
    void setDishQueue(const std::queue<Dish *> &dish_queue);

    // Task 2
    // Declaring 2 overload functions
    /**
     * Adds a dish to the preparation queue without dietary accommodations.
     * @param dish A pointer to a dynamically allocated Dish object.
     * @pre: The dish pointer is not null.
     * @post: The dish is added to the end of the queue.
     */
    void addDishToQueue(Dish *dish);

    /**
     * Adds a dish to the preparation queue with dietary accommodations.
     * @param dish A pointer to a dynamically allocated Dish object.
     * @param request A DietaryRequest object specifying dietary accommodations.
     * @pre: The dish pointer is not null.
     * @post: The dish is adjusted for dietary accommodations and added to the end of the queue.
     */
    void addDishToQueue(Dish *dish, const Dish::DietaryRequest &request);

    // Task 3  Implement the prepareNextDish function in StationManager

    /**
     * Prepares the next dish in the queue if possible.
     * @pre: The dish queue is not empty.
     * @post: The dish is processed and removed from the queue.
     * If the dish cannot be prepared, it stays in the queue
     * @return: True if the dish was prepared successfully; false otherwise.
     */
    bool prepareNextDish();

    // Task 4 Implement the displayDishQueue function in StationManager
    /**
    * Displays all dishes in the preparation queue.
    * @pre: None.
    * @post: Outputs the names of the dishes in the queue in order (each name
   is on its own line).
    */
    void displayDishQueue() const;

    // Task 5  Implement the clearDishQueue function in StationManager
    /**
     * Clears all dishes from the preparation queue.
     * @pre: None.
     * @post: The dish queue is emptied and all allocated memory is freed.
     */
    void clearDishQueue();

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
    bool replenishStationIngredientFromBackup(const std::string &station_name, const std::string &ingredient_name, int quantity);

    // Task 7 implement addBackupIngredients Function
    /**
     * Sets the backup ingredients stock with the provided list of ingredients.
     * @param ingredients A vector of Ingredient objects to set as the backup stock.
     * @pre: None.
     * @post: The backup_ingredients_ vector is replaced with the provided ingredients.
     * @return: True if the ingredients were added successfully.
     */
    bool addBackupIngredients(const std::vector<Ingredient> &ingredients);

    // Task 8 implement addBackupIngredient Function ///////<NO 'S'
    /**
     * Adds a single ingredient to the backup ingredients stock.
     * @param ingredient An Ingredient object to add to the backup stock.
     * @pre: None.
     * @post: If the ingredient already exists, its quantity is increased. Otherwise, it is added to the backup stock.
     * @return: True if the ingredient was added or updated successfully.
     */
    bool addBackupIngredient(const Ingredient &ingredient);

    // Task 9 Implement clearBackupIngredients Function
    /**
     * Empties the backup ingredients vector.
     * @pre: None.
     * @post: The `backup_ingredients_` vector is empty.
     */
    void clearBackupIngredients();

    // Task 10 Declare procesAllDishes Function
    /**
     * Processes all dishes in the queue and displays detailed results.
     * @pre: None.
     * @post: All dishes are processed, and detailed information is displayed.
     *        If a dish cannot be prepared even after replenishing ingredients, it stays in the queue.
     */
    void processAllDishes();

private:
    // helper function to get index of a station by name
    int getStationIndex(const std::string &station_name) const;
    // adding dish_queue_ member variable
    // will store pointers to Dish objs in FIFO order
    std::queue<Dish *> dish_queue_;

    // adding backup_ingredients_ member variable
    // to backup stock of ingredients that can be used to replenish station ingredients when needed.
    std::vector<Ingredient> backup_ingredients_;
};

#endif // STATIONMANAGER_HPP