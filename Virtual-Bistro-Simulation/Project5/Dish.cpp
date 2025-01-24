/**
 * @file Dish.cpp
 * @brief This file contains the implementation of the `Dish` class and the `Ingredient` struct, which are used to represent and manage dishes and their ingredients
 * in the virtual bistro simulation.
 *
 * The `Dish` class includes methods for setting and retrieving dish details such as name, preparation time, and ingredient list. The class also provides
 * functions to add ingredients, check ingredient requirements, and retrieve a list of ingredients needed for the dish.
 *
 * The `Ingredient` struct is implemented to hold information about each ingredient, including its name, available quantity, required quantity for a dish,
 * and the price per unit. This allows for accurate tracking of ingredient usage and stock levels in the kitchen stations.
 *
 * @date 11/10/2024
 * @author: Joyce Vieira Ferreira Dos Santos
 */

#include "Dish.hpp"
#include <string>
#include <vector>

// Ingredient Default Constructor
Ingredient::Ingredient() : name(), quantity(0), required_quantity(0), price(0) {}

// Ingredient Parameterized Constructor
Ingredient::Ingredient(const std::string &name, int quantity, int required_quantity, double price)
    : name(name), quantity(quantity), required_quantity(required_quantity), price(price) {}

// Default Constructor
Dish::Dish()
    : name_("UNKNOWN"), ingredients_({}), prep_time_(0), price_(0.0), cuisine_type_(CuisineType::OTHER)
{
}

// Parameterized Constructor
// Task 2  Modify the Dish Class
/**
 * Sets the ingredients for the dish.
 * @param ingredients: A vector of Ingredient objects representing the ingredients needed.
 * @post The `ingredients_` member is updated with the provided ingredients.
 */
Dish::Dish(const std::string &name, const std::vector<Ingredient> &ingredients, int prep_time, double price, CuisineType cuisine_type)
    : ingredients_(ingredients), prep_time_(prep_time), price_(price), cuisine_type_(cuisine_type)
{
    setName(name); // Use setName to validate the name
}

// Accessor Functions
std::string Dish::getName() const
{
    return name_;
}

// Task 2 Updating Accessor Function for ingredients_
std::vector<Ingredient> Dish::getIngredients() const
{
    return ingredients_;
}

int Dish::getPrepTime() const
{
    return prep_time_;
}

double Dish::getPrice() const
{
    return price_;
}

std::string Dish::getCuisineType() const
{
    switch (cuisine_type_)
    {
    case CuisineType::ITALIAN:
        return "ITALIAN";
    case CuisineType::MEXICAN:
        return "MEXICAN";
    case CuisineType::CHINESE:
        return "CHINESE";
    case CuisineType::INDIAN:
        return "INDIAN";
    case CuisineType::AMERICAN:
        return "AMERICAN";
    case CuisineType::FRENCH:
        return "FRENCH";
    default:
        return "OTHER";
    }
}

// Mutator Functions
void Dish::setName(const std::string &name)
{
    if (isValidName(name))
    {
        name_ = name;
    }
    else
    {
        name_ = "UNKNOWN";
    }
}

// Task 2 Updating Mutator Function for ingredients_
void Dish::setIngredients(const std::vector<Ingredient> &ingredients)
{
    ingredients_ = ingredients;
}

void Dish::setPrepTime(const int &prep_time)
{
    prep_time_ = prep_time;
}

void Dish::setPrice(const double &price)
{
    price_ = price;
}

void Dish::setCuisineType(const CuisineType &cuisine_type)
{
    cuisine_type_ = cuisine_type;
}

// Helper function to check if the name is valid
bool Dish::isValidName(const std::string &name) const
{
    for (char c : name)
    {
        if (!std::isalpha(c) && !std::isspace(c))
        {                 // Check if each character is a letter or space
            return false; // Name contains non-alphabetic characters other than spaces
        }
    }
    return true; // Name is valid
}

// bool Dish::operator==(const Dish &rhs) const
// {
//     return name_ == rhs.name_ && prep_time_ == rhs.prep_time_ &&
//            price_ == rhs.price_ && cuisine_type_ == rhs.cuisine_type_;
// }

// bool Dish::operator!=(const Dish &rhs) const
// {
//     return !(*this == rhs);
// }