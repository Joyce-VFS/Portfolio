/**
 * @file Inventory.cpp
 * @brief Implementation file for the Invetory class.
 *
 * This file contains the definitions of the member functions declared in Inventory.hpp.
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

#include "Inventory.hpp"
#include <vector>

/***
 *      PARAMETERIZED CONSTRUCTOR STARTS HERE
 * @brief constructing the inventory with the given items and an equipped item.
 * initializing the inventory grid and calculating total weight and item count.
 * using a 2D grid (vector) to store items.
 */
Inventory::Inventory(const std::vector<std::vector<Item>> &items, Item *equipped) : inventory_grid_(items), equipped_(equipped), weight_(0.0f), item_count_(0)
{
    for (const auto &row : inventory_grid_)
    {
        for (const auto &item : row)
        {
            if (item.type_ != ItemType::NONE)
            {
                weight_ += item.weight_;
                item_count_++;
            }
        }
    }
    // let me deep copy the equipped item
    if (equipped)
    {
        equipped_ = new Item(*equipped);
    }
}

/***1
 *      COPY CONSTRUCTOR STARTS HERE
 * @brief Creating another Inventory with same contents as new Inventory.
 */
Inventory::Inventory(const Inventory &rhs) : inventory_grid_(rhs.inventory_grid_), weight_(rhs.weight_), item_count_(rhs.item_count_)
{
    if (rhs.equipped_)
    {
        equipped_ = new Item(*rhs.equipped_);
    }
    else
    {
        equipped_ = nullptr;
    }
}

/***2
 *      MOVE CONSTRUCTOR STARTS HERE
 * @brief Transfering, in a efficient way, the contents of another Invetory to this one without copying it.
 */
Inventory::Inventory(Inventory &&rhs) : inventory_grid_(std::move(rhs.inventory_grid_)), weight_(rhs.weight_), item_count_(rhs.item_count_), equipped_(rhs.equipped_)
{
    rhs.equipped_ = nullptr;
    rhs.weight_ = 0;
    rhs.item_count_ = 0;
}

/***3
 *     COPY ASSIGNMENT OPERATOR STARTS HERE
 * @brief A deep copying to be called when new Inventory obj is created.
 */
Inventory &Inventory::operator=(const Inventory &rhs)
{
    if (this != &rhs)
    {
        inventory_grid_ = rhs.inventory_grid_;
        weight_ = rhs.weight_;
        item_count_ = rhs.item_count_;
        delete equipped_;
        equipped_ = rhs.equipped_ ? new Item(*rhs.equipped_) : nullptr;
    }
    return *this;
}

/***4
 *     MOVE ASSIGNMENT OPERATOR STARTS HERE
 * @brief Move assignment for efficiently transferring ownership of resources, like move constructor but for assignment.
 */
Inventory &Inventory::operator=(Inventory &&rhs)
{
    if (this != &rhs)
    {
        inventory_grid_ = std::move(rhs.inventory_grid_);
        weight_ = rhs.weight_;
        item_count_ = rhs.item_count_;
        delete equipped_;
        equipped_ = rhs.equipped_;
        rhs.equipped_ = nullptr;
        rhs.weight_ = 0;
        rhs.item_count_ = 0;
    }
    return *this;
}

/***5
 *     DESTRUCTOR STARTS HERE
 * @brief Cleaning up dynamically allocated equipped item.
 */
Inventory::~Inventory()
{
    delete equipped_;
}

/***   METHODS STARTING HERE
 * @brief returning a pointer to the equipped item
 */
Item *Inventory::getEquipped() const
{
    return equipped_;
}

/***
 * @brief equipping an item by deep copying it.
 */
void Inventory::equip(Item *itemToEquip)
{
    // gonna remove the old equipped item.
    delete equipped_;
    equipped_ = itemToEquip ? new Item(*itemToEquip) : nullptr;
}

/***
 * @brief Discarting the current equipped item.
 */
void Inventory::discardEquipped()
{
    delete equipped_;
    equipped_ = nullptr;
}

/***
 * @brief Retrieving item from specific position in the inventory grid.
 */
Item Inventory::at(const size_t &row, const size_t &col) const
{
    if (row >= inventory_grid_.size() || col >= inventory_grid_[row].size())
    {
        // to return default item if out of bound
        return Item();
    }
    return inventory_grid_[row][col];
}

/***
 * @brief Storing an item at sepcific position in inventory grid.
 * checking if position is valid and if slot is empty before storing item.
 */
bool Inventory::store(const size_t &row, const size_t &col, const Item &pickup)
{
    if (row >= inventory_grid_.size() || col >= inventory_grid_[row].size())
    {
        return false;
    }
    if (inventory_grid_[row][col].type_ != ItemType::NONE)
    {
        // if slot is occupied return false
        return false;
    }
    if (pickup.type_ != ItemType::NONE)
    {
        weight_ += pickup.weight_;
        item_count_++;
    }
    inventory_grid_[row][col] = pickup;
    return true;
}

/***
 * @brief Returning inventory grid.
 */
std::vector<std::vector<Item>> Inventory::getItems() const
{
    return inventory_grid_;
}

/***
 * @brief Returning total weight of stored items.
 */
float Inventory::getWeight() const
{
    return weight_;
}

/***
 * @brief Returning total count of stored items.
 */
size_t Inventory::getCount() const
{
    return item_count_;
}
