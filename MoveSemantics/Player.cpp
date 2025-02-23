/**
 * @file Player.cpp
 * @brief Implementation file for the Player class.
 *
 * This file contains the definitions of the member functions declared in Player.hpp.
 * It implements functionality for managing a player in an MMORPG, including their name
 * and inventory. The class supports both copy and move semantics for efficient resource management.
 *
 * @details Key features implemented:
 * - Constructing a player with a name and an optional inventory.
 * - Providing access to the player's inventory for modification.
 * - Supporting deep copy and move semantics for proper resource management.
 * - Ensuring the player's name and inventory are correctly copied or moved during assignment.
 *
 * @author Joyce Vieira Ferreira Dos Santos
 * @date 2/23/2025
 */

#include "Player.hpp"

/***
 * @brief Constructor Player obj with name and optional inventory.
 */
Player::Player(const std::string &name, const Inventory &inventory) : inventory_(inventory), name_(name)
{
}

/***
 * @brief Returning name string.
 */
std::string Player::getName() const
{
    return name_;
}

/***
 * @brief Returning inventory reference for modification.
 */
Inventory &Player::getInventoryRef()
{
    return inventory_;
}

/***1
 * @brief COPY CONSTRUCTOR STARTS HERE
 */
Player::Player(const Player &rhs) : inventory_(rhs.inventory_), name_(rhs.name_) {}

/***2
 * @brief MOVE CONSTRUCTOR STARTS HERE
 */
Player::Player(Player &&rhs) noexcept : inventory_(std::move(rhs.inventory_)), name_(std::move(rhs.name_))
{
}

/***3
 * @brief COPY ASSIGNMENT OPERATOR STARTS HERE
 */
Player &Player::operator=(const Player &rhs)
{
    if (this != &rhs)
    {
        name_ = rhs.name_;
        inventory_ = rhs.inventory_;
    }
    return *this;
}

/***4
 * @brief MOVE ASSIGNMENT OPERATOR STARTS HERE
 */
Player &Player::operator=(Player &&rhs) noexcept
{
    if (this != &rhs)
    {
        name_ = std::move(rhs.name_);
        inventory_ = std::move(rhs.inventory_);
    }
    return *this;
}