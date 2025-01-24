/**
 * @file MainCourse.hpp
 * @brief This file contains the declaration of the `MainCourse` class, which represents a main course dish in a virtual bistro simulation.
 *
 * The `MainCourse` class inherits from the abstract `Dish` class and provides specific attributes such as cooking method, protein type, prep time
 * and whether the dish is vegetarian. It also includes implementations of the pure virtual functions `display()` and `dietaryAccommodations()`.
 *
 * The class provides accessor and mutator methods for managing appetizer-specific attributes and handles dietary accommodations like
 * vegetarian, gluten-free, and low-sodium requests by modifying the dish's ingredients and attributes accordingly.
 *
 * @date 10/19/2024
 * @author of modification: Joyce Vieira Ferreira Dos Santos
 */
#ifndef MAINCOURSE_HPP
#define MAINCOURSE_HPP

#include "Dish.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
/**
 * @class MainCourse
 * @brief Represents a main course dish, inheriting from Dish.
 */
class MainCourse : public Dish
{
public:
    /**
     * @enum CookingMethod
     * @brief Describes the method used to cook the main course.
     */
    enum CookingMethod
    {
        GRILLED,
        BAKED,
        BOILED,
        FRIED,
        STEAMED,
        RAW
    };

    /**
     * @enum Category
     * @brief Describes the category of the side dish.
     */
    enum Category
    {
        GRAIN,
        PASTA,
        LEGUME,
        BREAD,
        SALAD,
        SOUP,
        STARCHES,
        VEGETABLE
    };

    /**
     * @struct SideDish
     * @brief Represents a side dish associated with the main course.
     */
    struct SideDish
    {
        std::string name;  ///< The name of the side dish.
        Category category; ///< The category of the side dish.
        // adding default constructor here
        // SideDish() : name(""), category(GRAIN) {}

        // adding a parameterized constructor to initialize SideDish
        // SideDish(const std::string &name, const Category &category) : name(name), category(category) {}
    };

    // Category to string helper function
    static std::string categoryTurnString(Category category)
    {
        switch (category)
        {
        case Category::VEGETABLE:
            return "Vegetable";
        case Category::GRAIN:
            return "Grain";
        case Category::PASTA:
            return "Pasta";
        case Category::SALAD:
            return "Salad";
        case Category::SOUP:
            return "Soup";
        case Category::STARCHES:
            return "Starches";
        case Category::LEGUME:
            return "Legume";
        case Category::BREAD:
            return "Bread";
        }
    }

    /**
     * Default constructor.
     * Initializes all private members with default values.
     */
    MainCourse();

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
    MainCourse(const std::string &name, const std::vector<std::string> &ingredients, const int &prep_time, const double &price, const CuisineType &cuisine_type, const CookingMethod &cooking_method, const std::string &protein_type, const std::vector<SideDish> &side_dishes, const bool &gluten_free);

    /**
     * Sets the cooking method of the main course.
     * @param cooking_method The new cooking method.
     * @post Sets the private member `cooking_method_` to the value of the parameter.
     */
    void setCookingMethod(const CookingMethod &cooking_method);

    /**
     * @return The cooking method of the main course.
     */
    CookingMethod getCookingMethod() const;

    /**
     * Sets the type of protein in the main course.
     * @param protein_type A string representing the type of protein.
     * @post Sets the private member `protein_type_` to the value of the parameter.
     */
    void setProteinType(const std::string &protein_type);

    /**
     * @return The type of protein in the main course.
     */
    std::string getProteinType() const;

    /**
     * Adds a side dish to the main course.
     * @param side_dish A SideDish struct containing the name and category of the side dish.
     * @post Adds the side dish to the `side_dishes_` vector.
     */
    void addSideDish(const SideDish &side_dish);

    /**
     * @return A vector of SideDish structs representing the side dishes served with the main course.
     */
    std::vector<SideDish> getSideDishes() const;

    /**
     * Sets the gluten-free flag of the main course.
     * @param gluten_free A boolean indicating if the main course is gluten-free.
     * @post Sets the private member `gluten_free_` to the value of the parameter.
     */
    void setGlutenFree(const bool &gluten_free);

    /**
     * @return True if the main course is gluten-free, false otherwise.
     */
    bool isGlutenFree() const;

    /**
     *Modifying main course based on dietary accomodations.
     * @param dietary_request A DietaryRequest struct containing dietary preferences.
     * @post Adjust the dietary accommodations for the main course.
     */
    void dietaryAccommodations(const DietaryRequest &dietary_request);

    /**
     * Displaying details of main course
     * @post Output the main course's details as expected.
     */
    void display() const;

private:
    CookingMethod cooking_method_;      ///< The cooking method used for the main course.
    std::string protein_type_;          ///< The type of protein used in the main course.
    std::vector<SideDish> side_dishes_; ///< The side dishes served with the main course.
    bool gluten_free_;                  ///< Flag indicating if the main course is gluten-free.
};

#endif // MAINCOURSE_HPP