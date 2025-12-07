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
    // Test polymorphism - base class pointers to derived objects
    Monster* monsters[3];
    monsters[0] = new Goblin();
    monsters[1] = new Skeleton();
    monsters[2] = new Dragon();
    
    for (int i = 0; i < 6; i++) {
        monsters[i%3]->displayStats();
        std::cout << monsters[i%3]->getAttackMessage() << std::endl;
        int dmg = monsters[i%3]->calculateDamage();
        std::cout << "Damage: " << dmg << std::endl;
        std::cout << std::endl;
    }
    
    // Clean up
    for (int i = 0; i < 3; i++) {
        delete monsters[i];
    }
    
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
