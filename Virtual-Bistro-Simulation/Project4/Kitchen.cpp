/**
 * @file Kitchen.cpp
 * @brief This file contains the implementation of the `Kitchen` class, which orchestrates the preparation and serving
 * of various dishes in a virtual bistro simulation.
 *
 * The `Kitchen` class implements methods to handle new orders, serve dishes, and apply dietary accommodations.
 * It utilizes various dish classes, including `Appetizer`, `MainCourse`, and `Dessert`, to ensure proper
 * management and presentation of each dish type.
 *
 * The implementation includes details on how the kitchen processes requests, manages dish attributes, and handles
 * specific dietary requirements. It also includes error handling and input validation to ensure smooth operation
 * during dish preparation and serving.
 *
 * @date 10/20/2024
 * @author of modifications: Joyce Vieira Ferreira Dos Santos
 */
#include "Kitchen.hpp"
#include "Appetizer.hpp"
#include "MainCourse.hpp"
#include "Dessert.hpp"
#include <fstream>
// #include <sstream>
// #include <string>
// #include <algorithm>
// #include <iostream>
// #include <stdexcept>

// DEFAULT
// Constructor start here
/**
 * Default constructor.
 * Default-initializes all private members.
 */
Kitchen::Kitchen() : ArrayBag<Dish *>(), total_prep_time_(0), count_elaborate_(0)
{
}

// IMPLEMENTING PARAMETERIZED CONSTRUCTOR HERE
/**
 * Parameterized constructor.
 * @param filename The name of the input CSV file containing dish information.
 * @pre The CSV file must be properly formatted.
 * @post Initializes the kitchen by reading dishes from the CSV file and storing them as `Dish*`.
 */
Kitchen::Kitchen(const std::string &filename) : ArrayBag<Dish *>(), total_prep_time_(0), count_elaborate_(0)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        throw std::runtime_error("Not able to open file: " + filename);
    }
    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream ss(line);
        std::string dishType, name, ingredientsStr, cuisineTypeStr, uniqueAttributes;
        std::vector<std::string> ingredients;
        int prepTime;
        double price;

        // Splitting 'ingredientsStr' by semicolon (to build the vector ingredients) by parsing
        // First parsing CSV fields
        std::getline(ss, dishType, ',');
        std::getline(ss, name, ',');
        std::getline(ss, ingredientsStr, ',');

        // Now the ingredients
        std::istringstream ingredientStream(ingredientsStr);
        std::string ingredient;
        while (std::getline(ingredientStream, ingredient, ';'))
        {
            ingredients.push_back(ingredient);
        }
        ss >> prepTime;
        ss.ignore(); // to skip the comma
        ss >> price;
        ss.ignore();
        std::getline(ss, cuisineTypeStr, ',');
        std::getline(ss, uniqueAttributes, ',');

        // Need to convert cuisineTypeStr to CuisineType enum
        Dish::CuisineType cuisineType = (cuisineTypeStr == "ITALIAN") ? Dish::CuisineType::ITALIAN : (cuisineTypeStr == "MEXICAN") ? Dish::CuisineType::MEXICAN
                                                                                                 : (cuisineTypeStr == "CHINESE")   ? Dish::CuisineType::CHINESE
                                                                                                 : (cuisineTypeStr == "INDIAN")    ? Dish::CuisineType::INDIAN
                                                                                                 : (cuisineTypeStr == "AMERICAN")  ? Dish::CuisineType::AMERICAN
                                                                                                 : (cuisineTypeStr == "FRENCH")    ? Dish::CuisineType::FRENCH
                                                                                                                                   : Dish::CuisineType::OTHER;

        // Creating new dish for correct subclass and setting the attributes
        Dish *newDish = nullptr;
        // Parse off the dishType
        if (dishType == "APPETIZER")
        {
            std::string servingStyleStr;
            int spicinessLevel;
            bool vegetarian;
            std::istringstream attributeStream(uniqueAttributes);
            std::getline(attributeStream, servingStyleStr, ';');
            attributeStream >> spicinessLevel;
            attributeStream.ignore();
            attributeStream >> std::boolalpha >> vegetarian;

            // Need to convert servingStyle as well
            // Appetizer::ServingStyle servingStyle = (servingStyleStr == "PLATED") ? Appetizer::ServingStyle::PLATED : (servingStyleStr == "FAMILY_STYLE") ? Appetizer::ServingStyle::FAMILY_STYLE
            //
            // IF statement to convert                                                                                                                                          : Appetizer::ServingStyle::BUFFET;

            // IF statement of enum conversion
            Appetizer::ServingStyle servingStyle;

            if (servingStyleStr == "PLATED")
            {
                servingStyle = Appetizer::ServingStyle::PLATED;
            }
            else if (servingStyleStr == "FAMILY_STYLE")
            {
                servingStyle = Appetizer::ServingStyle::FAMILY_STYLE;
            }
            else
            {
                servingStyle = Appetizer::ServingStyle::BUFFET;
            }

            newDish = new Appetizer(name, ingredients, prepTime, price, cuisineType, servingStyle, spicinessLevel, vegetarian);
        }
        else if (dishType == "MAINCOURSE")
        {
            std::string cookingMethodStr, proteinType, glutenFreeStr, sideDishesStr;
            bool glutenFree;
            std::istringstream attributeSream(uniqueAttributes);
            std::getline(attributeSream, cookingMethodStr, ';');
            std::getline(attributeSream, proteinType, ';');
            std::getline(attributeSream, sideDishesStr, ';');
            attributeSream >> std::boolalpha >> glutenFree;

            // //Need to convert cooking method as well
            // MainCourse::CookingMethod cookingMethod = (cookingMethodStr == "GRILLED") ? MainCourse::CookingMethod::GRILLED : (cookingMethodStr == "FRIED") ? MainCourse::CookingMethod::FRIED
            //                                                                                                              : (cookingMethodStr == "BAKED")   ? MainCourse::CookingMethod::BAKED
            //                                                                                                              :(cookingMethodStr == "BOILED") ? MainCourse::CookingMethod::BOILED

            // IF statement of enum conversion
            MainCourse::CookingMethod cookingMethod;

            if (cookingMethodStr == "GRILLED")
            {
                cookingMethod = MainCourse::CookingMethod::GRILLED;
            }
            else if (cookingMethodStr == "FRIED")
            {
                cookingMethod = MainCourse::CookingMethod::FRIED;
            }
            else if (cookingMethodStr == "BAKED")
            {
                cookingMethod = MainCourse::CookingMethod::BAKED;
            }
            else if (cookingMethodStr == "BOILED")
            {
                cookingMethod = MainCourse::CookingMethod::BOILED;
            }
            else if (cookingMethodStr == "STEAMED")
            {
                cookingMethod = MainCourse::CookingMethod::STEAMED;
            }
            else
            {
                cookingMethod = MainCourse::CookingMethod::RAW;
            }

            // Fixing side dishes in this format (RICE:STARCHES|BEANS:VEGETABLE)
            std::vector<MainCourse::SideDish> sideDishes;
            std::istringstream sideDishStream(sideDishesStr);
            std::string side;
            while (std::getline(sideDishStream, side, '|'))
            {
                size_t pos = side.find(':');
                if (pos != std::string::npos)
                {
                    std::string name = side.substr(0, pos);
                    std::string categoryStr = side.substr(pos + 1);

                    // Need to convert category string here as well
                    MainCourse::Category category;
                    if (categoryStr == "STARCHES")
                    {
                        category = MainCourse::Category::STARCHES;
                    }
                    else if (categoryStr == "VEGETABLE")
                    {
                        category = MainCourse::Category::VEGETABLE;
                    }
                    else if (categoryStr == "SOUP")
                    {
                        category = MainCourse::Category::SOUP;
                    }
                    else if (categoryStr == "SALAD")
                    {
                        category = MainCourse::Category::SALAD;
                    }
                    else if (categoryStr == "BREAD")
                    {
                        category = MainCourse::Category::BREAD;
                    }
                    else if (categoryStr == "LEGUME")
                    {
                        category = MainCourse::Category::LEGUME;
                    }
                    else if (categoryStr == "PASTA")
                    {
                        category = MainCourse::Category::PASTA;
                    }
                    else if (categoryStr == "GRAIN")
                    {
                        category = MainCourse::Category::GRAIN;
                    }
                    sideDishes.push_back(MainCourse::SideDish{name, category});
                }
            }
            newDish = new MainCourse(name, ingredients, prepTime, price, cuisineType, cookingMethod, proteinType, sideDishes, glutenFree);
        }
        else if (dishType == "DESSERT")
        {
            std::string flavorProfileStr;
            int sweetnessLevel;
            bool containsNuts;
            std::istringstream attributeStream(uniqueAttributes);
            std::getline(attributeStream, flavorProfileStr, ';');
            attributeStream >> sweetnessLevel;
            attributeStream.ignore();
            attributeStream >> std::boolalpha >> containsNuts;

            // Need to convert FlavorProfile as well
            Dessert::FlavorProfile flavorProfile = (flavorProfileStr == "SWEET") ? Dessert::FlavorProfile::SWEET : (flavorProfileStr == "BITTER") ? Dessert::FlavorProfile::BITTER
                                                                                                               : (flavorProfileStr == "SOUR")     ? Dessert::FlavorProfile::SOUR
                                                                                                               : (flavorProfileStr == "SALTY")    ? Dessert::FlavorProfile::SALTY
                                                                                                                                                  : Dessert::FlavorProfile::UMAMI;

            newDish = new Dessert(name, ingredients, prepTime, price, cuisineType, flavorProfile, sweetnessLevel, containsNuts);
        }
        if (newDish && add(newDish))
        {
            total_prep_time_ += prepTime;
        }
    }
    file.close();
}

// DIETARY ACCOM. HERE
/**
 *Adjusts all dishes in the kitchen based on the specified dietary accommodation.
 * @param request A DietaryRequest structure specifying the dietary accommodations.
 * @post Calls the `dietaryAccommodations()` method on each dish in the kitchen to adjust them accordingly.
 */
void Kitchen::dietaryAdjustment(const Dish::DietaryRequest &dietary_request)
{
    for (int i = 0; i < getCurrentSize(); i++)
    {
        items_[i]->dietaryAccommodations(dietary_request);
    }
}

// DISPLAY MENU HERE
/**
 * Displays all dishes currently in the kitchen.
 * @post Calls the `display()` method of each dish.
 */
void Kitchen::displayMenu() const
{
    for (int i = 0; i < item_count_; i++)
    {
        items_[i]->display();
    }
}

// DESTRUCTOR HERE

/**
 * Destructor.
 * @post Deallocates all dynamically allocated dishes to prevent memory leaks.
 */
Kitchen::~Kitchen()
{
    for (int i = 0; i < item_count_; ++i)
    {
        delete items_[i];
        items_[i] = nullptr;
    }
    clear();
}

// Fixing this to handle pointer correctly
bool Kitchen::newOrder(Dish *new_dish)
{

    if (add(new_dish))
    {
        total_prep_time_ += new_dish->getPrepTime();
        // std::cout<< "Dish added: "<<new_dish.getName() << std::endl;
        // if the new dish has 5 or more ingredients AND takes an hour or more to prepare, increment count_elaborate_
        if (new_dish->getIngredients().size() >= 5 && new_dish->getPrepTime() >= 60)
        {
            // std::cout << "Elaborate dish added: "<<new_dish.getName() << std::endl;
            count_elaborate_++;
        }
        return true;
    }

    return false;
}
bool Kitchen::serveDish(Dish *dish_to_remove)
{
    if (getCurrentSize() == 0)
    {
        return false;
    }

    if (remove(dish_to_remove))
    {
        total_prep_time_ -= dish_to_remove->getPrepTime();
        if (dish_to_remove->getIngredients().size() >= 5 && dish_to_remove->getPrepTime() >= 60)
        {
            count_elaborate_--;
        }
        return true;
    }
    return false;
}

int Kitchen::getPrepTimeSum() const
{
    if (getCurrentSize() == 0)
    {
        return 0;
    }
    return total_prep_time_;
}
int Kitchen::calculateAvgPrepTime() const
{
    if (getCurrentSize() == 0)
    {
        return 0;
    }
    double total_prep_time_ = 0;
    for (int i = 0; i < getCurrentSize(); i++)
    {
        total_prep_time_ += items_[i]->getPrepTime();
    }
    total_prep_time_ = total_prep_time_ / getCurrentSize();
    // std::cout<< "Total prep time: "<<total_prep_time_ << std::endl;
    // std::cout<<"rounded: "<<round(total_prep_time_)<<std::endl;
    return round(total_prep_time_);
}
int Kitchen::elaborateDishCount() const
{
    if (getCurrentSize() == 0 || count_elaborate_ == 0)
    {
        return 0;
    }
    return count_elaborate_;
}
double Kitchen::calculateElaboratePercentage() const
{
    // //Computes the percentage of vegetarian dishes in the kitchen rounded up to 2 decimal places.
    // double elaborate_dish = count_elaborate_;
    // std::cout << elaborate_dish << std::endl;

    // double total_dish = getCurrentSize();
    // std::cout << total_dish << std::endl;

    // double percentage = (elaborate_dish / total_dish) * 10000;
    // std::cout << percentage << std::endl;
    // percentage = round(percentage);
    // std::cout << percentage << std::endl;
    // percentage = percentage / 100;
    // std::cout << percentage << std::endl;

    // return percentage;
    if (getCurrentSize() == 0 || count_elaborate_ == 0)
    {
        return 0;
    }
    return round(double(count_elaborate_) / double(getCurrentSize()) * 10000) / 100;

    // return count_elaborate_ / getCurrentSize();
}
int Kitchen::tallyCuisineTypes(const std::string &cuisine_type) const
{
    int count = 0;
    for (int i = 0; i < getCurrentSize(); i++)
    {
        if (items_[i]->getCuisineType() == cuisine_type)
        {
            count++;
        }
    }
    return count;
}
int Kitchen::releaseDishesBelowPrepTime(const int &prep_time)
{
    int count = 0;
    int num = getCurrentSize();
    for (int i = 0; i < num; i++)
    {
        if (items_[i]->getPrepTime() < prep_time)
        {
            count++;
            serveDish(items_[i]);
        }
    }
    return count;
}

int Kitchen::releaseDishesOfCuisineType(const std::string &cuisine_type)
{
    int count = 0;
    for (int i = 0; i < getCurrentSize(); i++)
    {
        if (items_[i]->getCuisineType() == cuisine_type)
        {
            count++;
            serveDish(items_[i]);
        }
    }
    return count;
}
void Kitchen::kitchenReport() const
{
    std::cout << "ITALIAN: " << tallyCuisineTypes("ITALIAN") << std::endl;
    std::cout << "MEXICAN: " << tallyCuisineTypes("MEXICAN") << std::endl;
    std::cout << "CHINESE: " << tallyCuisineTypes("CHINESE") << std::endl;
    std::cout << "INDIAN: " << tallyCuisineTypes("INDIAN") << std::endl;
    std::cout << "AMERICAN: " << tallyCuisineTypes("AMERICAN") << std::endl;
    std::cout << "FRENCH: " << tallyCuisineTypes("FRENCH") << std::endl;
    std::cout << "OTHER: " << tallyCuisineTypes("OTHER") << std::endl
              << std::endl;
    std::cout << "AVERAGE PREP TIME: " << calculateAvgPrepTime() << std::endl;
    std::cout << "ELABORATE DISHES: " << calculateElaboratePercentage() << "%" << std::endl;
}