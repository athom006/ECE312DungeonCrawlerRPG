#include "Game.h"
#include <iostream>
#include <sstream>
#include <algorithm>

// TODO: Implement Game constructor
Game::Game() : player(NULL), current_room(NULL), 
               game_over(false), victory(false) {
}


// TODO: Implement Game destructor
Game::~Game() {
    // TODO: Clean up player and all rooms
    if (player) {
        delete player;
        player = NULL;
    }
    for (std::map<std::string, Room*>::iterator it = world.begin(); it != world.end(); ++it) {
        delete it->second;
    }
    world.clear();  
}


// TODO: Implement initializeWorld
// HINTS:
// - Create all rooms with new
// - Add each room to world using addRoom()
// - Connect rooms using connectRooms()
// - Add monsters to appropriate rooms using room->setMonster()
// - Add items to rooms using room->addItem()
// - Set current_room to starting room (entrance)
//
// SUGGESTED WORLD LAYOUT:
//                [Throne Room]
//                     |
//     [Armory] - [Hallway] - [Treasury]
//                     |
//                 [Entrance]
//
// MONSTERS:
// - Hallway: Goblin
// - Armory: Skeleton
// - Treasury: Skeleton
// - Throne Room: Dragon (boss!)
//
// ITEMS:
// - Entrance: Small Potion
// - Armory: Iron Sword, Chain Mail
// - Treasury: Health Potion
//
void Game::initializeWorld() {
    // TODO: Create rooms
    Room* entrance = new Room("Dungeon Entrance", "A dark stone corridor...");
    Room* hallway = new Room("Hallway", "A long hallway with flickering torches.");
    Room* armory = new Room("Armory", "Filled with racks of old weapons and armor.");
    Room* treasury = new Room("Treasury", "Glittering gold and jewels.");
    Room* throne_room = new Room("Throne Room", "An imposing chamber with a grand throne.");
    
    // TODO: Add rooms to world
    addRoom(entrance);
    addRoom(hallway);
    addRoom(armory);
    addRoom(treasury);
    addRoom(throne_room);
    
    // TODO: Connect rooms bidirectionally
    connectRooms("Dungeon Entrance", "north", "Hallway");
    connectRooms("Hallway", "west", "Armory");
    connectRooms("Hallway", "east", "Treasury");
    connectRooms("Hallway", "north", "Throne Room");
    
    // TODO: Add monsters
    hallway->setMonster(new Goblin());
    armory->setMonster(new Skeleton());
    treasury->setMonster(new Skeleton());
    throne_room->setMonster(new Dragon());
    
    // TODO: Add items
    entrance->addItem(new Consumable("Small Potion", "Heals 10 HP", 10));
    armory->addItem(new Weapon("Iron Sword", "A sturdy iron sword", 7));
    armory->addItem(new Armor("Chain Mail", "Basic protective armor", 5));
    treasury->addItem(new Consumable("Health Potion", "Heals 25 HP", 25));
    
    // TODO: Set starting room
    current_room = entrance;
    current_room->markVisited();
}


// TODO: Implement createStartingInventory
// HINTS:
// - Give player starting weapon: Rusty Dagger (damage +2)
// - Give player starting food: Bread (heals 5 HP)
// - Use: player->addItem(new Weapon(...))
//
void Game::createStartingInventory() {
    // TODO: Give player starting items
    player->addItem(new Weapon("Rusty Dagger", "A worn but usable dagger", 2));
    player->addItem(new Consumable("Bread", "Heals 5 HP", 5));
}


// TODO: Implement addRoom
// HINTS:
// - Check if room pointer is not NULL
// - Add to world map using room's name as key
// - Use: world[room->getName()] = room
//
void Game::addRoom(Room* room) {
    // TODO: Add room to world map
    if (room) {
        world[room->getName()] = room;
    }
}


// TODO: Implement connectRooms
// HINTS:
// - Look up both rooms in world map
// - If both exist:
//   - Add forward direction: room1->addExit(direction, room2)
//   - Determine reverse direction:
//     * north ↔ south
//     * east ↔ west
//   - Add reverse direction: room2->addExit(reverse, room1)
//
void Game::connectRooms(const std::string& room1_name, const std::string& direction,
                       const std::string& room2_name) {
    // TODO: Connect rooms bidirectionally
    Room* room1 = NULL;
    Room* room2 = NULL;
    std::map<std::string, Room*>::iterator it1 = world.find(room1_name);
    std::map<std::string, Room*>::iterator it2 = world.find(room2_name);
    if (it1 != world.end()) {
        room1 = it1->second;    
    }
    if (it2 != world.end()) {
        room2 = it2->second;
    }
    if (room1 && room2) {
        room1->addExit(direction, room2);
        std::string reverse;
        if (direction == "north") reverse = "south";
        else if (direction == "south") reverse = "north";
        else if (direction == "east") reverse = "west";
        else if (direction == "west") reverse = "east";
        if (!reverse.empty()) {
            room2->addExit(reverse, room1);
        }
    }
}


// TODO: Implement run - main game loop
// HINTS:
// - Print welcome message and game title
// - Get player name from input 
// - Create player: player
// - Call initializeWorld()
// - Call createStartingInventory()
// - Display starting room
// - Mark starting room as visited
// - Main loop: 
//   - Print prompt: "> "
//   - Get command (use std::getline)
//   - Convert to lowercase (use std::transform)
//   - Call processCommand()
//   - Check victory condition
//   - Check defeat condition (player dead)
//
void Game::run() {
    // TODO: Implement main game loop
}


// TODO: Implement processCommand
// HINTS:
// - Parse command into verb and object
// - Extract first word as verb
// - Rest of line is object
// - Dispatch to appropriate method based on verb:
//   * "go" or "move" → move(object)
//   * "look" or "l" → look()
//   * "attack" or "fight" → attack()
//   * "pickup" or "get" or "take" → pickupItem(object)
//   * "inventory" or "i" → inventory()
//   * "use" → useItem(object)
//   * "equip" or "e" → equip(object)
//   * "stats" → player->displayStats()
//   * "help" or "h" or "?" → help()
//   * "quit" or "exit" → set game_over to true
//
void Game::processCommand(const std::string& command) {
    // TODO: Parse and dispatch command
}


// TODO: Implement move
// HINTS:
// - Check if monster blocks path (current_room->hasMonster())
// - If blocked, print message and return
// - Get exit in specified direction
// - If exit exists:
//   - Update current_room
//   - Display new room
//   - Mark as visited
// - Otherwise print error: "You can't go that way!"
//
void Game::move(const std::string& direction) {
    // TODO: Move to adjacent room
}


// TODO: Implement look
// HINTS:
// - Simply display current room
//
void Game::look() {
    // TODO: Display current room
}


// TODO: Implement attack
// HINTS:
// - Check if monster in room
// - If no monster, print message and return
// - If monster present, call combat()
//
void Game::attack() {
    // TODO: Attack monster in room
}


// TODO: Implement combat
// HINTS:
// - Print "=== COMBAT BEGINS ==="
// - Combat loop: while both player and monster are alive
//   - Prompt for player action: attack/use <item>/flee
//   - If attack:
//     * Calculate player damage
//     * Monster takes damage
//     * If monster dead:
//       - Print victory
//       - Player gains exp and gold
//       - Get loot from monster
//       - Add loot to current room
//       - Check if Dragon 
//       - Clear monster from room
//       - Break from loop
//   - If use:
//     * Extract item name from command
//     * Call player->useItem()
//   - If flee:
//     * Print message and break
//   - Monster turn (if alive):
//     * Print attack message
//     * Calculate monster damage
//     * Player takes damage
// - Print "=== COMBAT ENDS ==="
//
void Game::combat(Monster* monster) {
    // TODO: Implement turn-based combat
}


// TODO: Implement pickupItem
// HINTS:
// - Get item from current room
// - If exists:
//   - Add to player inventory
//   - Remove from room (ownership transfer!)
// - Otherwise print error
//
void Game::pickupItem(const std::string& item_name) {
    // TODO: Pick up item from room
}


// TODO: Implement inventory
//
void Game::inventory() {
    // TODO: Display player inventory
}


// TODO: Implement useItem
// HINTS:
// - Call player->useItem(item_name)
//
void Game::useItem(const std::string& item_name) {
    // TODO: Use item from inventory
}


// TODO: Implement equip
// HINTS:
// - Get item from player inventory
// - Check if item exists
// - Check item type:
//   - If "Weapon": call player->equipWeapon()
//   - If "Armor": call player->equipArmor()
//   - Otherwise: print error (can't equip consumables)
//
void Game::equip(const std::string& item_name) {
    // TODO: Equip weapon or armor
}


// TODO: Implement help
// HINTS:
// - Print all available commands with descriptions
// - Format nicely with headers
// - Commands:
//   * go <direction> - Move
//   * look - Look around
//   * attack - Attack monster
//   * pickup <item> - Pick up item
//   * inventory - Show inventory
//   * use <item> - Use consumable
//   * equip <item> - Equip weapon/armor
//   * stats - Show character stats
//   * help - Show this help
//   * quit - Exit game
//
void Game::help() {
    // TODO: Display help message
}
