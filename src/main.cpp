#include "Game.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

/**
 * Main entry point for Dungeon Crawler RPG
 * 
 * This program demonstrates:
 * - C++ class hierarchies and inheritance
 * - STL containers (vector, map, string)
 * - Polymorphism with virtual functions
 * - Dynamic memory management with new/delete
 * - Resource management with destructors (RAII)
 * 
 * LEARNING OBJECTIVES:
 * - Complete object-oriented design
 * - Multi-file project organization
 * - Memory management patterns
 */

int main() {

    Weapon sword("Iron Sword", "A sturdy blade", 5);
    Armor shield("Wooden Shield", "Basic protection", 3);
    Consumable potion("Health Potion", "Restores health", 20);

    sword.displayInfo();
    shield.displayInfo();
    potion.displayInfo();

    Item* item_ptr = &sword;
    item_ptr->displayInfo();  // Should call Weapon version
    item_ptr = &shield;
    item_ptr->displayInfo();  // Should call Armor version
    item_ptr = &potion;
    item_ptr->displayInfo();  // Should call Consumable version 

    potion.use();  // Should work
    potion.use();  // Should print "already used"

    return 0;
}

/*int main() {
    // Seed random number generator for combat calculations
    // This ensures different random numbers each time the game runs
    srand(static_cast<unsigned int>(time(0)));
    
    try {
        // Create game object
        Game game;
        
        // Run main game loop
        // This doesn't return until game is over
        game.run();
    }
    catch (const std::exception& e) {
        // Catch any exceptions and print error message
        std::cerr << "Fatal error: " << e.what() << std::endl;
        return 1;
    }
    
    // Normal exit
    return 0;
}*/
