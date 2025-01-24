/**
 * @file Dish.hpp
 * @brief This file contains the declaration of the `Dish` class and the `Ingredient` struct, which form the core of the virtual bistro's dish system.
 *
 * The `Dish` class represents a generic dish with common attributes like name, ingredients, and preparation time. It is intended to be a base class
 * for specialized dish types (e.g., Appetizer, MainCourse, Dessert). The class provides methods to access and modify dish attributes, manage ingredients,
 * and retrieve information about the dish.
 *
 * The `Ingredient` struct represents an ingredient used in dishes, including its name, quantity in stock, required quantity for preparation, and price per unit.
 * This struct is used to track and manage ingredients for different dishes throughout the simulation.
 *
 * @date 11/10/2024
 * @autho: Joyce Vieira Ferreira Dos Santos
 */

#ifndef DISH_HPP
#define DISH_HPP

#include <string>
#include <vector>
#include <iostream>
#include <iomanip> // For std::fixed and std::setprecision
#include <cctype>  // For std::isalpha, std::isspace

//  Task 1: Implement the Ingredient Struct
/**
 * Struct representing an ingredient in the kitchen.
 * @param name: The name of the ingredient.
 * @param quantity: The amount available in stock.
 * @param required_quantity: The amount needed to prepare a dish.
 * @param price: The price per unit.
 */
struct Ingredient
{
    std::string name;
    int quantity;
    int required_quantity;
    double price;

    // COnstructors
    // Default here
    Ingredient();

    // Parameterized here
    Ingredient(const std::string &name, int quantity, int required_quantity, double price);
};
class Dish
{
public:
    /**
     * Structure to store dietary accommodation details.
     */
    struct DietaryRequest
    {
        bool vegetarian;
        bool vegan;
        bool gluten_free;
        bool nut_free;
        bool low_sodium;
        bool low_sugar;
    };
    // CuisineType enum definition
    enum CuisineType
    {
        ITALIAN,
        MEXICAN,
        CHINESE,
        INDIAN,
        AMERICAN,
        FRENCH,
        OTHER
    };

    // Constructors
    /**
     * Default constructor.
     * Initializes all private members with default values:
     * - name: "UNKNOWN"
     * - ingredients: Empty list
     * - prep_time: 0
     * - price: 0.0
     * - cuisine_type: OTHER
     */
    Dish();

    /**
     * Parameterized constructor.
     * @param name A reference to the name of the dish.
     * @param ingredients A reference to a list of ingredients (default is an empty list).
     * @param prep_time The preparation time in minutes (default is 0).
     * @param price The price of the dish (default is 0.0).
     * @param cuisine_type The cuisine type of the dish (a CuisineType enum) with default value OTHER.
     * @post The private members are set to the values of the corresponding parameters.
     */
    Dish(const std::string &name, const std::vector<Ingredient> &ingredients = {}, int prep_time = 0, double price = 0.0, CuisineType cuisine_type = CuisineType::OTHER);

    // Accessors
    /**
     * @return The name of the dish.
     */
    std::string getName() const;

    /**
     * @return The list of ingredients used in the dish.
     */
    std::vector<Ingredient> getIngredients() const;

    /**
     * @return The preparation time in minutes.
     */
    int getPrepTime() const;

    /**
     * @return The price of the dish.
     */
    double getPrice() const;

    /**
     * @return The cuisine type of the dish in string form.
     */
    std::string getCuisineType() const;

    // Mutators
    /**
     * Sets the name of the dish.
     * @param name A reference to the new name of the dish.
     * @post Sets the private member `name_` to the value of the parameter. If the name contains non-alphabetic characters, it is set to "UNKNOWN".
     */
    void setName(const std::string &name);

    /**
     * Sets the list of ingredients.
     * @param ingredients A reference to the new list of ingredients.
     * @post Sets the private member `ingredients_` to the value of the parameter.
     */
    void setIngredients(const std::vector<Ingredient> &ingredients);

    /**
     * Sets the preparation time.
     * @param prep_time The new preparation time in minutes.
     * @post Sets the private member `prep_time_` to the value of the parameter.
     */
    void setPrepTime(const int &prep_time);

    /**
     * Sets the price of the dish.
     * @param price The new price of the dish.
     * @post Sets the private member `price_` to the value of the parameter.
     */
    void setPrice(const double &price);

    /**
     * Sets the cuisine type of the dish.
     * @param cuisine_type The new cuisine type of the dish (a CuisineType enum).
     * @post Sets the private member `cuisine_type_` to the value of the parameter.
     */
    void setCuisineType(const CuisineType &cuisine_type);

private:
    std::string name_;
    std::vector<Ingredient> ingredients_;
    int prep_time_;
    double price_;
    CuisineType cuisine_type_;

    // Helper function to check if the name is valid
    /**
     * Checks if the name is valid.
     * @param name The name to be validated.
     * @return True if the name contains only alphabetic characters and spaces; false otherwise.
     */
    bool isValidName(const std::string &name) const;
};

#endif // DISH_HPP
