#include "RecipeBook.hpp"
#include <iostream>

int main()
{
    try
    {
        // Creating a RecipeBook
        RecipeBook book;

        // Add some recipes
        book.addRecipe(Recipe("Pasta", 5, "Delicious pasta with marinara sauce", false));
        book.addRecipe(Recipe("Salad", 2, "Fresh garden salad", true));
        book.addRecipe(Recipe("Cake", 7, "Chocolate cake", false));
        book.addRecipe(Recipe("Soup", 3, "Warm chicken soup", false));

        // Displaying the tree
        std::cout << "Preorder Display of Recipes:" << std::endl;
        book.preorderDisplay();

        // Find a recipe
        std::string findName = "Cake";
        Recipe *foundRecipe = book.findRecipe(findName);
        if (foundRecipe)
        {
            std::cout << "\nFound Recipe: " << foundRecipe->name_ << std::endl;
            std::cout << "Description: " << foundRecipe->description_ << std::endl;
            std::cout << "Difficulty Level: " << foundRecipe->difficulty_level_ << std::endl;
            std::cout << "Mastered: " << (foundRecipe->mastered_ ? "Yes" : "No") << std::endl;
        }
        else
        {
            std::cout << "\nRecipe not found: " << findName << std::endl;
        }

        // Remove a recipe
        std::cout << "\nRemoving Recipe: Salad" << std::endl;
        bool removed = book.removeRecipe("Salad");
        std::cout << "Remove operation successful: " << (removed ? "Yes" : "No") << std::endl;

        // Display the tree again
        std::cout << "\nPreorder Display After Removal:" << std::endl;
        book.preorderDisplay();

        // Calculate mastery points
        std::string masteryTarget = "Cake";
        int masteryPoints = book.calculateMasteryPoints(masteryTarget);
        std::cout << "\nMastery Points Needed for " << masteryTarget << ": " << masteryPoints << std::endl;

        // Balance the tree
        std::cout << "\nBalancing the tree..." << std::endl;
        book.balance();

        // Display the tree after balancing
        std::cout << "\nPreorder Display After Balancing:" << std::endl;
        book.preorderDisplay();

        // Clear the tree
        std::cout << "\nClearing the tree..." << std::endl;
        book.clear();

        // Display the tree after clearing
        std::cout << "\nPreorder Display After Clearing:" << std::endl;
        book.preorderDisplay();
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}