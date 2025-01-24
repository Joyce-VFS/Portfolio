/**
 * @file MainCourse.cpp
 * @brief This file contains the implementation of the `MainCourse` class, which represents a main course dish in a virtual bistro simulation.
 *
 * The `MainCourse` class provides implementations for the `display()` and `dietaryAccommodations()` methods, allowing the dish to be displayed
 * and modified based on dietary requirements such as vegetarian, low-sodium, and gluten-free requests. This includes replacing certain
 * ingredients and modifying the side dishes and cooking methods.
 *
 * The class also provides constructors to initialize `MainCourse` objects with default or parameterized values, along with accessor/mutator methods
 * to manage specific attributes like cooking method, protein type, and gluten-free status.
 *
 * @date 10/19/2024
 * @author of modifications: Joyce Vieira Ferreira Dos Santos
 */
#include "MainCourse.hpp"
// #include <iostream>
// #include <iomanip>
#include <algorithm>
#include <vector>
// #include <string>

/**
 * Default constructor.
 * Initializes all private members with default values.
 */
MainCourse::MainCourse()
    : Dish(), cooking_method_(GRILLED), protein_type_("UNKNOWN"), side_dishes_(), gluten_free_(false) {}

/**
 * Parameterized constructor.
 * @param name The name of the main course.
 * @param ingredients The ingredients used in the main course.
 * @param prep_time The preparation time in minutes.
 * @param price The price of the main course.
 * @param cuisine_type The cuisine type of the main course.
 * @param cooking_method The cooking method used for the main course.
 * @param protein_type The type of protein used in the main course.
 * @param side_dishes The side dishes served with the main course.
 * @param gluten_free Flag indicating if the main course is gluten-free.
 */
MainCourse::MainCourse(const std::string &name, const std::vector<std::string> &ingredients, const int &prep_time, const double &price, const CuisineType &cuisine_type, const CookingMethod &cooking_method, const std::string &protein_type, const std::vector<SideDish> &side_dishes, const bool &gluten_free)
    : Dish(name, ingredients, prep_time, price, cuisine_type), cooking_method_(cooking_method), protein_type_(protein_type), side_dishes_(side_dishes), gluten_free_(gluten_free) {}

/**
* Displays the main course's details.
* @post Outputs the main course's details, including name, ingredients,
preparation time, price, cuisine type, cooking method, protein type,
side dishes, and gluten-free status to the standard output.
* The information must be displayed in the following format:
*
* Dish Name: [Name of the dish]
* Ingredients: [Comma-separated list of ingredients
* Preparation Time: [Preparation time] minutes
* Price: $[Price, formatted to two decimal places]
* Cuisine Type: [Cuisine type]
* Cooking Method: [Cooking method: e.g., Grilled, Baked, etc.]
* Protein Type: [Type of protein: e.g., Chicken, Beef, etc.]
* Side Dishes: [Side dish name] (Category: [Category: e.g., Starches,
Vegetables])
* Gluten-Free: [Yes/No]
*/

void MainCourse::display() const
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
    std::cout << "Cooking Method: ";
    switch (cooking_method_)
    {
    case GRILLED:
        std::cout << "Grilled";
        break;
    case BAKED:
        std::cout << "Baked";
        break;
    case FRIED:
        std::cout << "Fried";
        break;
    case STEAMED:
        std::cout << "Steamed";
        break;
    case RAW:
        std::cout << "Raw";
        break;
    case BOILED:
        std::cout << "Boiled";
        break;
    }
    std::cout << std::endl;

    std::cout << "Protein Type: " << protein_type_ << std::endl;
    std::cout << "Side Dishes: ";
    for (size_t i = 0; i < side_dishes_.size(); i++)
    {
        std::cout << side_dishes_[i].name << " (Category: " << categoryTurnString(side_dishes_[i].category) << ")";

        if (i != side_dishes_.size() - 1)
        {
            std::cout << ", ";
        }
    }
    std::cout << std::endl;
    std::cout << "Gluten-Free: " << (gluten_free_ ? "Yes" : "No") << std::endl;
}

/**
* Modifies the main course based on dietary accommodations.
* @param request A DietaryRequest structure specifying the dietary
accommodations.
* @post Adjusts the main course's attributes to meet the specified
dietary needs.
* - If `request.vegetarian` is true:
* - Changes `protein_type_` to "Tofu".
* - Searches `ingredients_` for any non-vegetarian
ingredients and replaces the first occurrence with "Beans". If there are
other non-vegetarian ingredients, the next non-vegetarian ingredient is
replaced with "Mushrooms". If there are more, they will be removed
without substitution.
* Non-vegetarian ingredients are: "Meat", "Chicken",
"Fish", "Beef", "Pork", "Lamb", "Shrimp", "Bacon".
* - If `request.vegan` is true:
* - Changes `protein_type_` to "Tofu".
* - Removes dairy and egg ingredients from `ingredients_`.
* Dairy and egg ingredients are: "Milk", "Eggs", "Cheese",
"Butter", "Cream", "Yogurt".
* - If `request.gluten_free` is true:
* - Sets `gluten_free_` to true.
* - Removes side dishes from `side_dishes_` whose category
involves gluten.
* Gluten-containing side dish categories are: `GRAIN`,
`PASTA`, `BREAD`, `STARCHES`.
*/
void MainCourse::dietaryAccommodations(const DietaryRequest &dietary_request)
{
    // New vector to access the private 'ingredients_'
    std::vector<std::string> accessIngredients = getIngredients();

    if (dietary_request.vegetarian)
    {
        // Protein type
        setProteinType("Tofu");

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
                    // Next replacements will be removed
                    countReplacement++;
                }
                else
                {
                    // Next replacements will be removed
                    accessIngredients.erase(accessIngredients.begin() + i);
                    i--;
                }
            }
        }
    }

    // Lets handle the GLUTEN-FREE request here
    if (dietary_request.gluten_free)
    {
        setGlutenFree(true);
        for (size_t i = 0; i < side_dishes_.size(); i++)
        {
            if (side_dishes_[i].category == GRAIN || side_dishes_[i].category == BREAD || side_dishes_[i].category == STARCHES ||
                side_dishes_[i].category == PASTA)
            {
                side_dishes_.erase(side_dishes_.begin() + i);
                i--;
            }
        }
    }

    if (dietary_request.vegan)
    {
        // Protein type
        setProteinType("Tofu");

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
 * Sets the cooking method of the main course.
 * @param cooking_method The new cooking method.
 * @post Sets the private member `cooking_method_` to the value of the parameter.
 */
void MainCourse::setCookingMethod(const CookingMethod &cooking_method)
{
    cooking_method_ = cooking_method;
}

/**
 * @return The cooking method of the main course.
 */
MainCourse::CookingMethod MainCourse::getCookingMethod() const
{
    return cooking_method_;
}

/**
 * Sets the type of protein in the main course.
 * @param protein_type A string representing the type of protein.
 * @post Sets the private member `protein_type_` to the value of the parameter.
 */
void MainCourse::setProteinType(const std::string &protein_type)
{
    protein_type_ = protein_type;
}

/**
 * @return The type of protein in the main course.
 */
std::string MainCourse::getProteinType() const
{
    return protein_type_;
}

/**
 * Adds a side dish to the main course.
 * @param side_dish A SideDish struct containing the name and category of the side dish.
 * @post Adds the side dish to the `side_dishes_` vector.
 */
void MainCourse::addSideDish(const SideDish &side_dish)
{
    side_dishes_.push_back(side_dish);
}

/**
 * @return A vector of SideDish structs representing the side dishes served with the main course.
 */
std::vector<MainCourse::SideDish> MainCourse::getSideDishes() const
{
    return side_dishes_;
}

/**
 * Sets the gluten-free flag of the main course.
 * @param gluten_free A boolean indicating if the main course is gluten-free.
 * @post Sets the private member `gluten_free_` to the value of the parameter.
 */
void MainCourse::setGlutenFree(const bool &gluten_free)
{
    gluten_free_ = gluten_free;
}

/**
 * @return True if the main course is gluten-free, false otherwise.
 */
bool MainCourse::isGlutenFree() const
{
    return gluten_free_;
}
