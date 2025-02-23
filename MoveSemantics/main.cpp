/**
 * @file main.cpp
 * @brief Main program file for testing the Player, Inventory, and Item classes.
 *
 * This file demonstrates the functionality of the Player, Inventory, and Item classes.
 * It creates items, stores them in an inventory, assigns the inventory to a player,
 * and demonstrates moving and copying players between guilds. It also tests error handling
 * for invalid operations, such as moving non-existent players or storing items in invalid locations.
 *
 * @details Key features demonstrated:
 * - Creating items with specific names, weights, and types.
 * - Storing items in a 2D inventory grid.
 * - Creating players with inventories and managing their membership in guilds.
 * - Moving and copying players between guilds.
 * - Testing error handling for invalid operations.
 *
 * @author Joyce Vieira Ferreira Dos Santos
 * @date 2/23/2025
 */

#include <iostream>
#include "Player.hpp"
#include "Guild.hpp"

int main()
{
    // item creation
    Item sword("Sword", 5.0f, ItemType::WEAPON);
    Item shield("Shield", 10.0f, ItemType::ARMOR);
    Item potion("Potion", 1.0f, ItemType::ACCESSORY);

    // inventory creation and adding items to it
    Inventory inventory;
    inventory.store(0, 0, sword);
    inventory.store(1, 1, shield);
    inventory.store(2, 2, potion);

    // Creating a player with the inventory
    Player player1("Player1", inventory);
    std::cout << "Player1 created with name: " << player1.getName() << std::endl;
    std::cout << "Player1's inventory weight: " << player1.getInventoryRef().getWeight() << std::endl;

    // Creating another player with a default inventory
    Player player2("Player2");
    std::cout << "Player2 created with name: " << player2.getName() << std::endl;

    // Creating two guilds
    Guild guild1;
    Guild guild2;

    // listing players into guild1
    guild1.enlistPlayer(player1);
    guild1.enlistPlayer(player2);

    std::cout << "Players enlisted in Guild1." << std::endl;

    // Moving Player1 from Guild1 to Guild2
    bool moveSuccess = guild1.movePlayerTo("Player1", guild2);
    if (moveSuccess)
    {
        std::cout << "Player1 moved from Guild1 to Guild2." << std::endl;
    }
    else
    {
        std::cout << "Failed to move Player1." << std::endl;
    }

    // Copying Player2 from Guild1 to Guild2
    bool copySuccess = guild1.copyPlayerTo("Player2", guild2);
    if (copySuccess)
    {
        std::cout << "Player2 copied from Guild1 to Guild2." << std::endl;
    }
    else
    {
        std::cout << "Failed to copy Player2." << std::endl;
    }

    // Trying to move a player that doesn't exist
    bool invalidMove = guild1.movePlayerTo("NonExistentPlayer", guild2);
    if (!invalidMove)
    {
        std::cout << "Failed to move NonExistentPlayer (as expected)." << std::endl;
    }

    // Testing the Inventory's store method
    bool invalidStore = inventory.store(10, 10, potion);
    if (!invalidStore)
    {
        std::cout << "Failed to store item at invalid location (as expected)." << std::endl;
    }

    return 0;
}