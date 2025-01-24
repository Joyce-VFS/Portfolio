/**
 * @file Kitchen.hpp
 * @brief This file contains the declaration of the `Kitchen` class, which manages the preparation and serving of dishes
 * in a virtual bistro simulation.
 *
 * The `Kitchen` class acts as a central point for handling various dish types, including appetizers, main courses, and
 * desserts. It provides methods for placing new orders, serving dishes, and managing dietary accommodations across
 * different types of dishes.
 *
 * The class includes constructors for initializing a `Kitchen` object with specific attributes, as well as methods
 * for calculating average preparation times and displaying menus. It manages a collection of dishes and facilitates
 * interactions between different dish classes.
 *
 * @date 10/20/2024
 * @author of modifications: Joyce Vieira Ferreira Dos Santos
 */
#ifndef KITCHEN_HPP
#define KITCHEN_HPP

#include "ArrayBag.hpp"
#include "Dish.hpp"
// for round
#include <fstream>
#include <cmath>
#include <iostream>

class Kitchen : public ArrayBag<Dish *>
{
public:
    Kitchen();
    /**
     * Parameterized constructor.
     * @param filename The name of the input CSV file containing dish information.
     * @pre The CSV file must be properly formatted.
     * @post Initializes the kitchen by reading dishes from the CSV file and
       storing them as `Dish*`.
    */
    Kitchen(const std::string &filename);
    /**
     * Destructor.
     * @post Deallocates all dynamically allocated dishes to prevent memory
     leaks.
     */
    ~Kitchen();
    bool newOrder(Dish *new_dish);
    bool serveDish(Dish *dish_to_remove);
    int getPrepTimeSum() const;
    int calculateAvgPrepTime() const;
    int elaborateDishCount() const;
    double calculateElaboratePercentage() const;
    int tallyCuisineTypes(const std::string &cuisine_type) const;
    int releaseDishesBelowPrepTime(const int &prep_time);
    int releaseDishesOfCuisineType(const std::string &cuisine_type);
    void kitchenReport() const;
    /**
     * Adjusts all dishes in the kitchen based on the specified dietary
     accommodation.
     * @param request A DietaryRequest structure specifying the dietary
     accommodations.
     * @post Calls the `dietaryAccommodations()` method on each dish in the
     kitchen to adjust them accordingly.
     */
    void dietaryAdjustment(const Dish::DietaryRequest &dietary_request);
    /**
     * Displays all dishes currently in the kitchen.
     * @post Calls the `display()` method of each dish.
     */
    void displayMenu() const;

private:
    int total_prep_time_;
    int count_elaborate_;
};

#endif // KITCHEN_HPP