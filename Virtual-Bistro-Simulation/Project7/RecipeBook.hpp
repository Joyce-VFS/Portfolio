/**
 * @file RecipeBook.hpp
 * @brief Header file for the RecipeBook class, which extends the BinarySearchTree class
 *        to manage and organize Recipe objects.
 *
 * This file defines the Recipe struct and the RecipeBook class. The RecipeBook class provides
 * functionality to store, search, add, remove, balance, and display recipes in a binary search tree.
 *
 * @details The RecipeBook class:
 * - Uses inheritance from the BinarySearchTree class to leverage tree operations.
 * - Supports operations like finding a recipe by name, adding or removing recipes, clearing the tree,
 *   calculating mastery points, balancing the tree, and displaying recipes.
 *
 * @author Joyce Vieira Ferreira Dos Santos
 * @date 12/13/2024
 */

#ifndef RECIPEBOOK_HPP
#define RECIPEBOOK_HPP
#include "BinarySearchTree.hpp"
#include <string>
#include <fstream>
#include <sstream>

// TASK 1

// Recipe Struct Def HERE
struct Recipe
{
    std::string name_;
    int difficulty_level_;
    std::string description_;
    bool mastered_;

    // Default Contructor
    /**
     * Default constructor.
     * @post: Initializes name_ and description_ to empty strings,
    difficulty_level_ to 0, and mastered_ to false.
     */
    Recipe();

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
    Recipe(const std::string &name, int difficulty_level, const std::string &description, bool mastered = false);

    // Operator Overloading
    // Operator ==
    /**
     * Equality operator.
     * @param other A const reference to another Recipe.
     * @return True if name_ is equal to other’s name_; false otherwise.
     */
    bool operator==(const Recipe &other) const;

    // Operator<
    /**
     * Less-than operator.
     * @param other A const reference to another Recipe.
     * @return True if name_ is lexicographically less than other's name_; false
    otherwise.
    */
    bool operator<(const Recipe &other) const;
    // Operator>
    /**
     * Greater-than operator.
     * @param other A const reference to another Recipe.

     * @return True if name_ is lexicographically greater than other's name_;
    false otherwise.
    */
    bool operator>(const Recipe &other) const;
};

// TASK 2
class RecipeBook : public BinarySearchTree<Recipe>
{
public:
    // Default COnstructor
    /**
     * Default Constructor.
     * @post: Initializes an empty RecipeBook.
     */
    RecipeBook();

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
    RecipeBook(const std::string &filename);

    // TASK 3
    /**
    * Finds a Recipe in the tree by name.
    * @param name A const reference to a string representing the name of the
   Recipe.
    * @return A pointer to the node containing the Recipe with the given
   difficulty level, or nullptr if not found.
    */
    Recipe *findRecipe(const std::string &name) const;

    // TASK 4
    /**
     * Adds a Recipe to the tree.
     * @param recipe A const reference to a Recipe object.
     * @pre: The Recipe does not already exist in the tree (based on name).
     * @post: The Recipe is added to the tree in BST order (based on name).
     * @return: True if the Recipe was successfully added; false if a Recipe with the same name already exists.
     */
    bool addRecipe(const Recipe &recipe);

    // TASK 5
    /**
    * Removes a Recipe from the tree by name.
    * @param name A const reference to a string representing the name of the
   Recipe.
    * @post: If found, the Recipe is removed from the tree.
    * @return: True if the Recipe was successfully removed; false otherwise.
    */
    bool removeRecipe(const std::string &name);

    // TASK 6
    /**
     * Clears all Recipes from the tree.
     * @post: The tree is emptied, and all nodes are deallocated.
     */
    void clear();

    // TASK 7
    /**
     * Calculates the number of mastery points needed to master a Recipe.
     * @param name A const reference to a string representing the name of the Recipe.
     * @note: For a Recipe to be mastered, all Recipes with lower difficulty levels must also be mastered.
     * @return: An integer representing the number of mastery points needed, or -1 if the Recipe is not found.
     */
    int calculateMasteryPoints(const std::string &name) const;

    // TASK 8
    /**
     * Balances the tree.
     * @post: The tree is balanced such that for any node, the heights of its left and right subtrees differ by no more than 1.
     */
    void balance();

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
    void preorderDisplay() const;

private:
    // makig helper funtion findNode to use the items in our BinaryNode class
    std::shared_ptr<BinaryNode<Recipe>> findNode(const std::string &name, std::shared_ptr<BinaryNode<Recipe>> subtree_ptr) const;
    // Helper for preorder traversal
    void preorderDisplayHelper(std::shared_ptr<BinaryNode<Recipe>> node) const;
    // helper fundtion for mastery points calc
    void calculateMasteryPointsHelper(std::shared_ptr<BinaryNode<Recipe>> node, int target_difficulty, int &count) const;
    // Helper for building balanced tree from sorted recipes
    void buildBalancedTree(const std::vector<Recipe> &recipes, int start, int end);
    // Helper to perform inorder traversal that will collect recipes
    void inorderTraversal(std::shared_ptr<BinaryNode<Recipe>> node, std::vector<Recipe> &recipes) const;
};

#endif