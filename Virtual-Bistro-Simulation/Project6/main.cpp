#include "StationManager.hpp"
#include "Dish.hpp"
#include "MainCourse.hpp"
#include <iostream>

int main()
{

    // Create StationManager
    StationManager manager;

    // Create Kitchen Stations
    KitchenStation pastaStation("Pasta Station");
    KitchenStation saladStation("Salad Station");
    KitchenStation grillStation("Grill Station");
    KitchenStation ovenStation("Oven Station");
    KitchenStation seafoodStation("Seafood Station");

    // Add stations to manager
    manager.addStation(&pastaStation);
    manager.addStation(&saladStation);
    manager.addStation(&grillStation);
    manager.addStation(&ovenStation);
    manager.addStation(&seafoodStation);

    // Initialize backup ingredients using the helper function
    std::vector<Ingredient> backupIngredients = {
        {"Tomato", 10, 3, 0.6},
        {"Cheese", 5, 2, 1.5},
        {"Lettuce", 8, 1, 0.75},
        {"Pasta", 6, 1, 0.5}};
    manager.setBackupIngredients(backupIngredients);

    // Display backup ingredients
    // std::cout << "\nGot backup ingredients successfully!\n";
    // for (const auto &ingredient : manager.getBackupIngredients())
    // {
    //     std::cout << "- " << ingredient.name << ": " << ingredient.quantity << " units\n";
    // }

    // Create dishes and side dishes to add to the queue
    std::vector<MainCourse::SideDish> sideDishes = {
        {"Garlic Bread", MainCourse::BREAD},
        {"Veggies", MainCourse::VEGETABLE}};

    MainCourse *spaghetti = new MainCourse("Spaghetti Bolognese",
                                           {{"Pasta", 5, 1, 0.2}}, // Ingredients
                                           15,                     // Prep time
                                           12.0,                   // Price
                                           Dish::CuisineType::ITALIAN,
                                           MainCourse::CookingMethod::BOILED,
                                           "Beef",     // Protein
                                           sideDishes, // Side dishes
                                           false);     // Gluten-free

    MainCourse *salad = new MainCourse("Salad",
                                       {{"Lettuce", 3, 1, 0.3}},
                                       10,
                                       7.3,
                                       Dish::CuisineType::AMERICAN,
                                       MainCourse::CookingMethod::RAW,
                                       "Chicken",
                                       {},
                                       true);

    MainCourse *grilledChicken = new MainCourse("Grilled Chicken", {{"Chicken", 3, 1, 0.5}}, 20,
                                                15.0,
                                                Dish::CuisineType::AMERICAN,
                                                MainCourse::CookingMethod::GRILLED,
                                                "Chicken",
                                                {},
                                                false);

    // Add dishes to the StationManager's queue
    manager.addDishToQueue(spaghetti);
    manager.addDishToQueue(salad);
    manager.addDishToQueue(grilledChicken);

    // Process all dishes
    manager.processAllDishes();

    // Clean up dynamically allocated memory
    delete spaghetti;
    delete salad;
    delete grilledChicken;

    // // // initializing backupIngredients using the helper function (setter)
    // std::vector<Ingredient> backupIngredients = {
    //     {"Tomato", 10, 3, 0.6}, {"Cheese", 5, 2, 1.5}, {"Lettuce", 8, 1, 0.75}, {"Pasta"}};
    // manager.setBackupIngredients(backupIngredients);

    // // Getting the Backup Ingredient and Displaying
    // std::vector<Ingredient> gettingBackup = manager.getBackupIngredients();
    // std::cout << "\nGot backup ingredients sucessfully yay \n";
    // for (const auto &ingredient : gettingBackup)
    // {
    //     std::cout << "- " << ingredient.name << ": " << ingredient.quantity << " units\n";
    // }

    // // creating the dishes and sidedishes to add to queueeueueue
    // std::vector<MainCourse::SideDish> sideDishes = {
    //     {"Garlic Bread", MainCourse::BREAD},
    //     {"Veggies", MainCourse::VEGETABLE}};
    // MainCourse *spaghetti = new MainCourse("Spaghetti", {{"Pasta", 5, 1, 0.2}}, 15, 12.0, Dish::CuisineType::ITALIAN, MainCourse::CookingMethod::BOILED, "Beef", sideDishes, false);
    // MainCourse *salad = new MainCourse("Salad", {{"Lettuce", 3, 1, 0.3}}, 10, 7.3, Dish::CuisineType::AMERICAN, MainCourse::RAW, "Chicken", {}, true);

    // // testing task 3
    // std::cout << "Can it prep next dish in queue?\n";
    // if (manager.prepareNextDish())
    // {
    //     std::cout << "Yas queen\n";
    // }
    // else
    // {
    //     std::cout << "Can't prep\n";
    // }

    // // testing task 4
    // std::cout << "\nDisplay all dishes\n";
    // manager.displayDishQueue();

    // // testing task 5
    // std::cout << "\nClearing the dish queue\n";
    // manager.clearDishQueue();

    // // lets see if queueueue is empty
    // std::cout << "\nDisplaying dishes after clearing, is it empty?\n";
    // manager.displayDishQueue();

    // // testing task 6
    // bool result = manager.replenishStationIngredientFromBackup("Pasta Station", "Tomato", 5);
    // if (result)
    // {
    //     std::cout << "Yay replenish back up works\n";
    // }
    // else
    // {
    //     std::cout << "Nah, didnt replenish\n";
    // }

    // // testing task 7
    // std::vector<Ingredient> newBackupIngredients = {
    //     {"Onion", 15, 2, 0.7},
    //     {"Garlic", 20, 3, 0.2}};
    // result = manager.addBackupIngredients(newBackupIngredients);
    // if (result)
    // {
    //     std::cout << "\nTask 7 works\n";
    // }
    // else
    // {
    //     std::cout << "\nTask 7 sucks\n";
    // }

    // // testing task 8
    // Ingredient newIngredient1 = {"Rosemary", 13, 5, 0.3};
    // Ingredient newIngredient2 = {"Cilantro", 5, 2, 1.0};

    // bool result1 = manager.addBackupIngredient(newIngredient1);
    // bool result2 = manager.addBackupIngredient(newIngredient2);
    // bool result3 = manager.addBackupIngredient({"Rosemary", 7, 2, 0.3});

    // if (result1 && result2 && result3)
    // {
    //     std::cout << "\nYES task 8 works";
    // }
    // else
    // {
    //     std::cout << "\nCheck where you messed up";
    // }

    // // testing task 9
    // std::cout << "\nTesting clearBackupIngredients...\n";
    // manager.clearBackupIngredients();
    // std::vector<Ingredient> emptyBackup = manager.getBackupIngredients();
    // if (emptyBackup.empty())
    // {
    //     std::cout << "\nTask 9 works";
    // }
    // else
    // {
    //     std::cout << "\nTask 9 not working girl";
    // }

    // // testing task 10
    // std::cout << "\nTesting processAllDishes...\n";
    // manager.addDishToQueue(spaghetti);
    // manager.addDishToQueue(salad);
    // manager.processAllDishes();

    // // clean up dynamically allocated memory
    // delete pastaStation;
    // delete grillStation;
    // delete spaghetti;
    // delete salad;
    // std::cout << "\nTest good!\n";

    return 0;
}