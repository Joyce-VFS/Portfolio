/**
 * @file RecipeBook.cpp
 * @brief Implementation file for the RecipeBook class.
 *
 * This file contains the definitions of the member functions declared in RecipeBook.hpp.
 * It implements functionality for managing recipes in a binary search tree, including
 * adding, removing, balancing, and displaying recipes, as well as calculating mastery points.
 *
 * @details Key features implemented:
 * - Parsing recipes from a CSV file and constructing the tree.
 * - Balancing the tree using an inorder traversal.
 * - Displaying recipes in a formatted preorder traversal.
 * - Ensuring recipes are unique and mastering is calculated based on difficulty level.
 * @author Joyce Vieira Ferreira Dos Santos
 * @date 12/13/2024
 * */

#include "RecipeBook.hpp"
#include <iostream>

// TASK 1
// Default Contructor
/**
 * Default constructor.
 * @post: Initializes name_ and description_ to empty strings,
difficulty_level_ to 0, and mastered_ to false.
 */
Recipe::Recipe() : name_(""), difficulty_level_(0), description_(""), mastered_(false) {}

// Parameterized Constructor
/**
 * Parameterized Constructor.
 * @param name The name of the recipe.
* @param difficulty_level The difficulty level of the recipe.
 * @param description A brief description of the recipe.
 * @param mastered Indicates whether the recipe has been mastered (default is
false).
 * @post: Initializes the Recipe with the provided values.
 */
Recipe::Recipe(const std::string &name, int difficulty_level, const std::string &description, bool mastered)
    : name_(name), difficulty_level_(difficulty_level), description_(description), mastered_(mastered) {}

// Operator Overloading
// Operator ==
/**
 * Equality operator.
 * @param other A const reference to another Recipe.
 * @return True if name_ is equal to other’s name_; false otherwise.
 */
bool Recipe::operator==(const Recipe &other) const
{
    return name_ == other.name_;
}

// Operator<
/**
 * Less-than operator.
 * @param other A const reference to another Recipe.
 * @return True if name_ is lexicographically less than other's name_; false
otherwise.
*/
bool Recipe::operator<(const Recipe &other) const
{
    return name_ < other.name_;
}

// Operator>
/**
 * Greater-than operator.
 * @param other A const reference to another Recipe.

 * @return True if name_ is lexicographically greater than other's name_;
false otherwise.
*/
bool Recipe::operator>(const Recipe &other) const
{
    return name_ > other.name_;
}

// TASK 2
// Default COnstructor
/**
 * Default Constructor.
 * @post: Initializes an empty RecipeBook.
 */
RecipeBook::RecipeBook() : BinarySearchTree<Recipe>() {}

// Parameterized Constructor
/**
 * Parameterized Constructor.
 * @param filename A const reference to a string representing the name of a
CSV file.
 * @post: The RecipeBook is populated with Recipes from the CSV file.
 * The file format is as follows:
 * name,difficulty_level,description,mastered
 * Ignore the first line. Each subsequent line represents a Recipe to be
added to the RecipeBook.
 */
RecipeBook::RecipeBook(const std::string &filename) : BinarySearchTree<Recipe>()
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        throw std::runtime_error("Unable to open file: " + filename);
    }
    std::string line;
    bool is_first_line = true;

    // To read the file
    while (std::getline(file, line))
    {
        if (is_first_line)
        {
            is_first_line = false;
            continue;
        }
        std::istringstream line_stream(line);
        std::string name, difficulty, description, mastered;

        // Parsing the lines
        std::getline(line_stream, name, ',');
        std::getline(line_stream, difficulty, '.');
        std::getline(line_stream, description, '.');
        std::getline(line_stream, mastered, '.');

        // converting and adding
        int difficulty_level = std::stoi(difficulty);
        bool mastered_flag = (mastered == "1" || mastered == "true");

        Recipe recipe(name, difficulty_level, description, mastered_flag);
        this->add(recipe);
    }
    file.close();
}

// TASK 3
/**
* Finds a Recipe in the tree by name.
* @param name A const reference to a string representing the name of the
Recipe.
* @return A pointer to the node containing the Recipe with the given
difficulty level, or nullptr if not found.
*/
// Helper for findNode
std::shared_ptr<BinaryNode<Recipe>> RecipeBook::findNode(const std::string &name, std::shared_ptr<BinaryNode<Recipe>> subtree_ptr) const
{
    if (subtree_ptr == nullptr)
    {
        return nullptr;
    }
    if (subtree_ptr->getItem().name_ == name)
    {
        return subtree_ptr;
    }
    // // recursively seraching on the left side (left child)
    auto leftRes = findNode(name, subtree_ptr->getLeftChildPtr());
    if (leftRes)
    {
        return leftRes;
    }
    return findNode(name, subtree_ptr->getRightChildPtr());
    // std::shared_ptr<BinaryNode<Recipe>> leftRes = findNode(name, subtree_ptr->getLeftChildPtr());
    // if (leftRes != nullptr)
    // {
    //     return leftRes;
    // }
    // // same for right side (right child)
    // std::shared_ptr<BinaryNode<Recipe>> rightRes = findNode(name, subtree_ptr->getRightChildPtr());
    // return rightRes;
}

Recipe *RecipeBook::findRecipe(const std::string &name) const
{
    auto node = findNode(name, this->getRoot());
    if (node)
    {
        return new Recipe(node->getItem());
    }
    return nullptr;
    // std::shared_ptr<BinaryNode<Recipe>> node = findNode(name, this->getRoot());
    // if (node != nullptr)
    // {
    //     const Recipe &item = node->getItem();
    //     return const_cast<Recipe *>(&item);
    // }
    // return nullptr;
}
// // Helper for findNode
// std::shared_ptr<BinaryNode<Recipe>> RecipeBook::findNode(std::shared_ptr<BinaryNode<Recipe>> subtree_ptr, const Recipe &target) const
// {
//     if (!subtree_ptr)
//     {
//         return nullptr;
//     }
//     else if (subtree_ptr->getItem() == target)
//     {
//         return subtree_ptr;
//     }
//     else if (subtree_ptr->getItem() > target)
//     {
//         return findNode(subtree_ptr->getLeftChildPtr(), target);
//     }
//     else
//     {
//         return findNode(subtree_ptr->getRightChildPtr(), target);
//     }
// }

// TASK 4
/**
 * Adds a Recipe to the tree.
 * @param recipe A const reference to a Recipe object.
 * @pre: The Recipe does not already exist in the tree (based on name).
 * @post: The Recipe is added to the tree in BST order (based on name).
 * @return: True if the Recipe was successfully added; false if a Recipe with the same name already exists.
 */
bool RecipeBook::addRecipe(const Recipe &recipe)
{
    if (findRecipe(recipe.name_) != nullptr)
    {
        return false;
    }
    this->add(recipe);
    return true;
    // Recipe *existing = findRecipe(recipe.name_);
    // // if recipe with same name exist return false
    // if (existing)
    // {
    //     return false;
    // }
    // this->add(recipe);
    // return true;
}

// TASK 5
/**
* Removes a Recipe from the tree by name.
* @param name A const reference to a string representing the name of the
Recipe.
* @post: If found, the Recipe is removed from the tree.
* @return: True if the Recipe was successfully removed; false otherwise.
*/
bool RecipeBook::removeRecipe(const std::string &name)
{
    Recipe target(name, 0, "", false);
    return this->remove(target);
}

// TASK 6
/**
 * Clears all Recipes from the tree.
 * @post: The tree is emptied, and all nodes are deallocated.
 */
void RecipeBook::clear()
{
    this->setRoot(nullptr);
}

// TASK 7
/**
 * Calculates the number of mastery points needed to master a Recipe.
 * @param name A const reference to a string representing the name of the Recipe.
 * @note: For a Recipe to be mastered, all Recipes with lower difficulty levels must also be mastered.
 * @return: An integer representing the number of mastery points needed, or -1 if the Recipe is not found.
 */
int RecipeBook::calculateMasteryPoints(const std::string &name) const
{
    Recipe *target = findRecipe(name);
    if (!target)
    {
        return -1;
    }
    if (target->mastered_)
    {
        return 0;
    }
    int mastery_points = 0;
    calculateMasteryPointsHelper(this->getRoot(), target->difficulty_level_, mastery_points);
    return mastery_points + 1;
}
// helper fundtion for mastery points calc
void RecipeBook::calculateMasteryPointsHelper(std::shared_ptr<BinaryNode<Recipe>> node, int target_difficulty, int &count) const
{
    if (!node)
        return;
    const Recipe &recipe = node->getItem();
    if (recipe.difficulty_level_ < target_difficulty && !recipe.mastered_)
    {
        count++;
    }

    calculateMasteryPointsHelper(node->getLeftChildPtr(), target_difficulty, count);
    calculateMasteryPointsHelper(node->getRightChildPtr(), target_difficulty, count);
}

// TASK 8
/**
 * Balances the tree.
 * @post: The tree is balanced such that for any node, the heights of its left and right subtrees differ by no more than 1.
 */
void RecipeBook::balance()
{
    std::vector<Recipe> recipes;
    inorderTraversal(this->getRoot(), recipes);
    this->clear();
    buildBalancedTree(recipes, 0, recipes.size() - 1);
}
// Helper to perform inorder traversal that will collect recipes
void RecipeBook::inorderTraversal(std::shared_ptr<BinaryNode<Recipe>> node, std::vector<Recipe> &recipes) const
{
    if (!node)
        return;

    inorderTraversal(node->getLeftChildPtr(), recipes);
    recipes.push_back(node->getItem());
    inorderTraversal(node->getRightChildPtr(), recipes);
}
// Helper for building balanced tree from sorted recipes
void RecipeBook::buildBalancedTree(const std::vector<Recipe> &recipes, int start, int end)
{
    if (start > end)
        return;

    int mid = start + (end - start) / 2;
    this->add(recipes[mid]);
    buildBalancedTree(recipes, start, mid - 1);
    buildBalancedTree(recipes, mid + 1, end);
}

// TASK 9
/**
 * Displays the tree in preorder traversal.
 * @post: Outputs the Recipes in the tree in preorder, formatted as:
 * Name: [name_]
 * Difficulty Level: [difficulty_level_]
 * Description: [description_]
 * Mastered: [Yes/No]
 * (Add an empty line between Recipes)
 */
void RecipeBook::preorderDisplay() const
{
    preorderDisplayHelper(this->getRoot());
}
// Helper for preorder traversal
void RecipeBook::preorderDisplayHelper(std::shared_ptr<BinaryNode<Recipe>> node) const
{
    if (!node)
        return;

    const Recipe &recipe = node->getItem();
    std::cout << "Name: " << recipe.name_ << std::endl;
    std::cout << "Difficulty Level: " << recipe.difficulty_level_ << std::endl;
    std::cout << "Description: " << recipe.description_ << std::endl;
    std::cout << "Mastered: " << (recipe.mastered_ ? "Yes" : "No") << std::endl;
    std::cout << std::endl;

    preorderDisplayHelper(node->getLeftChildPtr());
    preorderDisplayHelper(node->getRightChildPtr());
}
