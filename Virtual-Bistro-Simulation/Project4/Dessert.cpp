/**
 * @file Dessert.cpp
 * @brief This file contains the implementation of the `Dessert` class, which represents a dessert dish in a virtual bistro simulation.
 *
 * The `Dessert` class provides implementations for the `display()` method, allowing the dish to be displayed
 * with its details. It also includes methods for dietary accommodations to adjust the dessert based on specific
 * dietary requirements, such as gluten-free options.
 *
 * The class provides constructors to initialize `Dessert` objects with default or parameterized values, along with
 * accessor/mutator methods to manage specific attributes like dessert type and any unique characteristics of the dessert.
 *
 * @date 10/20/2024
 * @author of modifications: Joyce Vieira Ferreira Dos Santos
 */

#include "Dessert.hpp"
// #include <iostream>
// #include <iomanip>
// #include <algorithm>
// #include <vector>
// #include <string>

/**
 * Default constructor.
 * Initializes all private members with default values.
 */
Dessert::Dessert()
    : Dish(), flavor_profile_(SWEET), sweetness_level_(0), contains_nuts_(false) {}

/**
 * Parameterized constructor.
 * @param name The name of the dessert.
 * @param ingredients The ingredients used in the dessert.
 * @param prep_time The preparation time in minutes.
 * @param price The price of the dessert.
 * @param cuisine_type The cuisine type of the dessert.
 * @param flavor_profile The flavor profile of the dessert.
 * @param sweetness_level The sweetness level of the dessert.
 * @param contains_nuts Flag indicating if the dessert contains nuts.
 */
Dessert::Dessert(const std::string &name, const std::vector<std::string> &ingredients, const int &prep_time, const double &price, const CuisineType &cuisine_type, const FlavorProfile &flavor_profile, const int &sweetness_level, const bool &contains_nuts)
    : Dish(name, ingredients, prep_time, price, cuisine_type), flavor_profile_(flavor_profile), sweetness_level_(sweetness_level), contains_nuts_(contains_nuts) {}

/**
* Displays the dessert's details.
* @post Outputs the dessert's details, including name, ingredients,
preparation time, price, cuisine type, flavor profile, sweetness level, and
whether it contains nuts.
* The information must be displayed in the following format:
*
* Dish Name: [Name of the dish]
* Ingredients: [Comma-separated list of ingredients]
Note for all subclasses: When multiple ingredients are removed, at most two replacement
ingredients should be added, and they should replace the first and second (when applicable)
occurrences of the ingredients to be removed.
Step 3: Modify the Kitchen Class
* Preparation Time: [Preparation time] minutes
* Price: $[Price, formatted to two decimal places]
* Cuisine Type: [Cuisine type]
* Flavor Profile: [Flavor profile: Sweet, Bitter, Sour, Salty, or Umami]
* Sweetness Level: [Sweetness level]
* Contains Nuts: [Yes/No]
*/
void Dessert::display() const
{
    // New vector to access 'ingredients_'
    std::vector<std::string> accessIngredients = getIngredients();
    std::cout << "Dish Name: " << getName() << std::endl;
    std::cout << "Ingredients: ";
    for (size_t i = 0; i < accessIngredients.size(); i++)
    {
        std::cout << accessIngredients[i];
        if (i != accessIngredients.size() - 1)
        {
            std::cout << ", ";
        }
    }
    std::cout << std::endl;
    std::cout << "Preparation Time: " << getPrepTime() << " minutes" << std::endl;
    std::cout << std::fixed << std::setprecision(2) << "Price: $" << getPrice() << std::endl;
    std::cout << "Cuisine Type: " << getCuisineType() << std::endl;
    std::cout << "Flavor Profile: ";
    switch (flavor_profile_)
    {
    case SWEET:
        std::cout << "Sweet";
        break;
    case BITTER:
        std::cout << "Bitter";
        break;
    case SOUR:
        std::cout << "Sour";
        break;
    case SALTY:
        std::cout << "Salty";
        break;
    case UMAMI:
        std::cout << "UMAMI";
        break;
    }
    std::cout << std::endl;
    std::cout << "Sweetness Level: " << sweetness_level_ << std::endl;
    std::cout << "Contains Nuts: " << (containsNuts() ? "Yes" : "No") << std::endl;
}

/**
*Modifies the dessert based on dietary accommodations.
* @param request A DietaryRequest structure specifying the dietary
accommodations.
* @post Adjusts the dessert's attributes to meet the specified dietary
needs.
* -If `request.nut_free` is true:
*-Sets `contains_nuts_` to false.
* -Removes nuts from `ingredients_`.
* Nuts are : "Almonds", "Walnuts", "Pecans", "Hazelnuts",
"Peanuts", "Cashews", "Pistachios".
* -If `request.low_sugar` is true:
*-Reduces `sweetness_level_` by 3 (minimum of 0).
* -If `request.vegan` is true:
*-Removes dairy and egg ingredients from `ingredients_`.
* Dairy and egg ingredients are : "Milk", "Eggs", "Cheese",
"Butter", "Cream", "Yogurt".
**/
void Dessert::dietaryAccommodations(const DietaryRequest &dietary_request)
{
    // New vector to access 'ingredients_'
    std::vector<std::string> accessIngredients = getIngredients();
    // Will handle nut-free req here
    if (dietary_request.nut_free)
    {
        setContainsNuts(false);
        for (size_t i = 0; i < accessIngredients.size(); i++)
        {
            if (accessIngredients[i] == "Almonds" || accessIngredients[i] == "Walnuts" || accessIngredients[i] == "Pecans" || accessIngredients[i] == "Hazelnut" || accessIngredients[i] == "Peanuts" || accessIngredients[i] == "Cashews" || accessIngredients[i] == "Pistachios")
            {
                accessIngredients.erase(accessIngredients.begin() + i);
                i--;
            }
        }
        setIngredients(accessIngredients);
    }

    // Will handle low-sugar req here
    if (dietary_request.low_sugar)
    {
        sweetness_level_ = std::max(0, sweetness_level_ - 3); // Reduce sweetness by 3
    }

    // Will handle vegan req here
    if (dietary_request.vegan)
    {

        for (size_t i = 0; i < accessIngredients.size(); i++)
        {
            if (accessIngredients[i] == "Milk" || accessIngredients[i] == "Eggs" || accessIngredients[i] == "Cheese" || accessIngredients[i] == "Butter" || accessIngredients[i] == "Cream" || accessIngredients[i] == "Yogurt")
            {
                accessIngredients.erase(accessIngredients.begin() + i);
                i--;
            }
        }
    }
    setIngredients(accessIngredients);
}

/**
 * Sets the flavor profile of the dessert.
 * @param flavor_profile The new flavor profile.
 * @post Sets the private member `flavor_profile_` to the value of the parameter.
 */
void Dessert::setFlavorProfile(const FlavorProfile &flavor_profile)
{
    flavor_profile_ = flavor_profile;
}

/**
 * @return The flavor profile of the dessert.
 */
Dessert::FlavorProfile Dessert::getFlavorProfile() const
{
    return flavor_profile_;
}

/**
 * Sets the sweetness level of the dessert.
 * @param sweetness_level An integer representing the sweetness level of the dessert.
 * @post Sets the private member `sweetness_level_` to the value of the parameter.
 */
void Dessert::setSweetnessLevel(const int &sweetness_level)
{
    sweetness_level_ = sweetness_level;
}

/**
 * @return The sweetness level of the dessert.
 */
int Dessert::getSweetnessLevel() const
{
    return sweetness_level_;
}

/**
 * Sets the contains_nuts flag of the dessert.
 * @param contains_nuts A boolean indicating if the dessert contains nuts.
 * @post Sets the private member `contains_nuts_` to the value of the parameter.
 */
void Dessert::setContainsNuts(const bool &contains_nuts)
{
    contains_nuts_ = contains_nuts;
}

/**
 * @return True if the dessert contains nuts, false otherwise.
 */
bool Dessert::containsNuts() const
{
    return contains_nuts_;
}
