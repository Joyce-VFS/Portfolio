/**
 * @file Appetizer.cpp
 * @brief This file contains the implementation of the `Appetizer` class, which represents an appetizer dish in a virtual bistro simulation.
 *
 * The `Appetizer` class provides implementations for the `display()` and `dietaryAccommodations()` functions, allowing the dish to be displayed
 * and modified based on dietary requirements. This includes replacing non-vegetarian ingredients, reducing spiciness for low-sodium requests,
 * and removing gluten-containing ingredients for gluten-free requests.
 *
 * The class also provides constructors to initialize appetizer objects with default or parameterized values, and accessor/mutator methods
 * to manage its specific attributes such as serving style, spiciness level, and vegetarian status.
 *
 * @date 10/19/2024
 * @author of modification: Joyce Vieira Ferreira Dos Santos
 */

#include "Appetizer.hpp"
// #include <iostream>
// #include <iomanip>
#include <algorithm>
#include <vector>
// #include <string>

/**
 * Default constructor.
 * Initializes all private members with default values.
 */
Appetizer::Appetizer()
    : Dish(), serving_style_(PLATED), spiciness_level_(0), vegetarian_(false) {}

/**
 * Parameterized constructor.
 * @param name The name of the appetizer.
 * @param ingredients The ingredients used in the appetizer.
 * @param prep_time The preparation time in minutes.
 * @param price The price of the appetizer.
 * @param cuisine_type The cuisine type of the appetizer.
 * @param serving_style The serving style of the appetizer.
 * @param spiciness_level The spiciness level of the appetizer.
 * @param vegetarian Flag indicating if the appetizer is vegetarian.
 */
Appetizer::Appetizer(const std::string &name, const std::vector<std::string> &ingredients, const int &prep_time, const double &price, const CuisineType &cuisine_type, const ServingStyle &serving_style, const int &spiciness_level, const bool &vegetarian)
    : Dish(name, ingredients, prep_time, price, cuisine_type), serving_style_(serving_style), spiciness_level_(spiciness_level), vegetarian_(vegetarian) {}

/*Overriding the display function here to print appetizer's details.
*Displays information including inherited attributes and Appetizer-specific details.
* Displays the appetizer's details.
* @post Outputs the appetizer's details, including name, ingredients,
preparation time, price, cuisine type, serving style, spiciness level, and
vegetarian status, to the standard output.
* The information must be displayed in the following format:
*
* Dish Name: [Name of the dish]
* Ingredients: [Comma-separated list of ingredients]
* Preparation Time: [Preparation time] minutes
* Price: $[Price, formatted to two decimal places]
* Cuisine Type: [Cuisine type]
* Serving Style: [Serving style: Plated, Family Style, or Buffet]
* Spiciness Level: [Spiciness level]
* Vegetarian: [Yes/No]
*/

void Appetizer::display() const
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
    // std::cout << "Serving Style: " << (serving_style_ == PLATED ? "Plated" : serving_style_ == FAMILY_STYLE ? "Family Style"
    //                                                                                                         : "Buffet")
    //           << std::endl;

    std::cout << "Serving Style: ";
    switch (serving_style_)
    {
    case PLATED:
        std::cout << "Plated";
        break;
    case FAMILY_STYLE:
        std::cout << "Family Style";
        break;
    case BUFFET:
        std::cout << "Buffet";
        break;
    }
    std::cout << std::endl;

    std::cout << "Spiciness Level: " << spiciness_level_ << std::endl;
    std::cout << "Vegetarian: " << (vegetarian_ ? "Yes" : "No") << std::endl;
}
/**
* Accomodating dietary requests by modifying the appetizer's ingredients and attributes.
*
* Modifies the appetizer based on dietary accommodations.
* @param request A DietaryRequest structure specifying the dietary
accommodations.
* @post Adjusts the appetizer's attributes to meet the specified
MainCourse Class
dietary needs.
* - If `request.vegetarian` is true:
* - Sets `vegetarian_` to true.
* - Searches `ingredients_` for any non-vegetarian
ingredients and replaces the first occurrence with "Beans". If there are
other non-vegetarian ingredients, the next non-vegetarian ingredient is
replaced with "Mushrooms". If there are more, they will be removed
without substitution.
* Non-vegetarian ingredients are: "Meat", "Chicken",
"Fish", "Beef", "Pork", "Lamb", "Shrimp", "Bacon".
* - If `request.low_sodium` is true:
* - Reduces `spiciness_level_` by 2 (minimum of 0).
* - If `request.gluten_free` is true:
* - Removes gluten-containing ingredients from
`ingredients_`.
* Gluten-containing ingredients are: "Wheat", "Flour",
"Bread", "Pasta", "Barley", "Rye", "Oats", "Crust".
*/
void Appetizer::dietaryAccommodations(const DietaryRequest &dietary_request)
{
    // New vector to access the private 'ingredients_'
    std::vector<std::string> accessIngredients = getIngredients();

    if (dietary_request.vegetarian)
    {

        // will mark dish as vegetarian
        setVegetarian(true);
        // Count variable
        int countReplacement = 0;
        // Modifying ingredients to accomodate veggies request
        for (size_t i = 0; i < accessIngredients.size(); i++)
        {
            if (accessIngredients[i] == "Meat" || accessIngredients[i] == "Chicken" || accessIngredients[i] == "Fish" || accessIngredients[i] == "Beef" || accessIngredients[i] == "Pork" || accessIngredients[i] == "Lamb" || accessIngredients[i] == "Shrimp" || accessIngredients[i] == "Bacon")
            {

                if (countReplacement == 0)
                {
                    // First replacement is beans
                    accessIngredients[i] = "Beans";
                    // Next replacement is mushrooms
                    countReplacement++;
                }
                else if (countReplacement == 1)
                {
                    // Next replacement is mushrooms
                    accessIngredients[i] = "Mushrooms";
                    countReplacement++;
                }
                else
                {
                    // Next 'replacements' will be removed
                    accessIngredients.erase(accessIngredients.begin() + i);
                    i--;
                }
            }
        }
        setIngredients(accessIngredients);
    }
    // Lets handle LOW SODIUM request here
    if (dietary_request.low_sodium)
    {
        // will reduce spiciness by 2 (minimum of 0)
        spiciness_level_ -= 2;
        if (spiciness_level_ < 0)
        {
            spiciness_level_ = 0;
        }

        // spiciness_level_ = std::max(0, spiciness_level_ - 2);
    }
    // Lets handle the GLUTEN-FREE request here
    if (dietary_request.gluten_free)
    {
        for (size_t i = 0; i < accessIngredients.size(); i++)
        {
            if (accessIngredients[i] == "Wheat" || accessIngredients[i] == "Flour" || accessIngredients[i] == "Bread" ||
                accessIngredients[i] == "Pasta" || accessIngredients[i] == "Barley" || accessIngredients[i] == "Rye" ||
                accessIngredients[i] == "Oats" || accessIngredients[i] == "Crust")
            {
                accessIngredients.erase(accessIngredients.begin() + i);
                i--;
            }
        }
    }
    setIngredients(accessIngredients);
}

/**
 * Sets the serving style of the appetizer.
 * @param serving_style The new serving style.
 * @post Sets the private member `serving_style_` to the value of the parameter.
 */
void Appetizer::setServingStyle(const ServingStyle &serving_style)
{
    serving_style_ = serving_style;
}

/**
 * @return The serving style of the appetizer.
 */
Appetizer::ServingStyle Appetizer::getServingStyle() const
{
    return serving_style_;
}

/**
 * Sets the spiciness level of the appetizer.
 * @param spiciness_level An integer representing the spiciness level of the appetizer.
 * @post Sets the private member `spiciness_level_` to the value of the parameter.
 */
void Appetizer::setSpicinessLevel(const int &spiciness_level)
{
    spiciness_level_ = spiciness_level;
}

/**
 * @return The spiciness level of the appetizer.
 */
int Appetizer::getSpicinessLevel() const
{
    return spiciness_level_;
}

/**
 * Sets the vegetarian flag of the appetizer.
 * @param vegetarian A boolean indicating if the appetizer is vegetarian.
 * @post Sets the private member `vegetarian_` to the value of the parameter.
 */
void Appetizer::setVegetarian(const bool &vegetarian)
{
    vegetarian_ = vegetarian;
}

/**
 * @return True if the appetizer is vegetarian, false otherwise.
 */
bool Appetizer::isVegetarian() const
{
    return vegetarian_;
}