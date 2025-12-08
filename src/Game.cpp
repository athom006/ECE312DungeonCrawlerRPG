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
//         
//     [Wizard Tower]          [Throne Room]
//          |                        |
//     [Grungy Lair] - [Armory] - [Hallway] - [Treasury] - [Chapel]
//                                   |
//                               [Entrance]
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
    Room* grungy_lair = new Room("Grungy Lair", "A dark cave filled with a rotting stench.");
    Room* chapel = new Room("Chapel", "A chilling chapel haunted by spirits.");
    Room* wizard_tower = new Room("Wizard Tower", "A tall tower filled with mysterious artifacts.");
    
    // TODO: Add rooms to world
    addRoom(entrance);
    addRoom(hallway);
    addRoom(armory);
    addRoom(treasury);
    addRoom(throne_room);
    addRoom(grungy_lair);
    addRoom(chapel);
    addRoom(wizard_tower);
    
    // TODO: Connect rooms bidirectionally
    connectRooms("Dungeon Entrance", "north", "Hallway");
    connectRooms("Hallway", "west", "Armory");
    connectRooms("Hallway", "east", "Treasury");
    connectRooms("Hallway", "north", "Throne Room");
    connectRooms("Armory", "west", "Grungy Lair");
    connectRooms("Treasury", "east", "Chapel");
    connectRooms("Grungy Lair", "north", "Wizard Tower");
    
    // TODO: Add monsters
    hallway->setMonster(new Goblin());
    armory->setMonster(new Skeleton());
    treasury->setMonster(new Skeleton());
    throne_room->setMonster(new Dragon());
    grungy_lair->setMonster(new Troll());
    chapel->setMonster(new Ghost());
    wizard_tower->setMonster(new Wizard());
    
    // TODO: Add items
    entrance->addItem(new Consumable("Small Potion", "Restores 10 HP", 10));
    armory->addItem(new Weapon("Iron Sword", "A sturdy iron sword", 7));
    armory->addItem(new Armor("Chain Mail", "Basic protective armor", 5));
    treasury->addItem(new Consumable("Health Potion", "Restores 25 HP", 25));
    wizard_tower->addItem(new Armor("Mystic Robe", "A robe imbued with magical protection", 15));
    grungy_lair->addItem(new Weapon("Club", "A crude wooden club", 4));
    chapel->addItem(new Weapon("Flaming Sword", "A holy symbol used to ward off evil", 30));
    
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
    player->addItem(new Consumable("Bread", "Restores 5 HP", 5));
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
    std::cout << "=== Welcome to Dungeon Crawler RPG ===" << std::endl;
    std::cout << "Enter your character's name: ";
    std::string name;
    std::getline(std::cin, name);
    player = new Player(name);
    initializeWorld();
    createStartingInventory();
    current_room->display();
    current_room->markVisited();
    game_over = false;
    while (!game_over) {
        std::cout << "> ";
        std::string command;
        std::getline(std::cin, command);
        std::transform(command.begin(), command.end(), command.begin(), ::tolower);
        processCommand(command);
        if (victory) {
            std::cout << "Congratulations! You have won the game!" << std::endl;
            game_over = true;
        }
        if (!player->isAlive()) {
            std::cout << "You have been defeated. Game over." << std::endl;
            game_over = true;
        }
    }

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
    std::istringstream iss(command); // Use istringstream to parse - Generated by Copilot
    std::string verb;
    iss >> verb;
    std::string object;
    std::getline(iss, object);
    object.erase(0, object.find_first_not_of(" ")); // Trim leading spaces
    if (verb == "go" || verb == "move") {
        move(object);
    } else if (verb == "look" || verb == "l") {
        look();
    } else if (verb == "attack" || verb == "fight") {
        attack();
    } else if (verb == "pickup" || verb == "get" || verb == "take") {
        pickupItem(object);
    } else if (verb == "inventory" || verb == "i") {
        inventory();
    } else if (verb == "use") {
        useItem(object);
    } else if (verb == "equip" || verb == "e") {
        equip(object);
    } else if (verb == "stats") {
        player->displayStats();
    } else if (verb == "help" || verb == "h" || verb == "?") {
        help();
    } else if (verb == "quit" || verb == "exit") {
        game_over = true;
    } else {
        std::cout << "Unknown command. Type 'help' for a list of commands." << std::endl;
    }
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
    if (current_room->hasMonster()) {
        std::cout << "A monster blocks your path! You must defeat it first." << std::endl;
        return;
    }
    Room* next_room = current_room->getExit(direction);
    if (next_room) {
        current_room = next_room;
        current_room->display();
        current_room->markVisited();
    } else {
        std::cout << "You can't go that way!" << std::endl;
    }
}


// TODO: Implement look
// HINTS:
// - Simply display current room
//
void Game::look() {
    // TODO: Display current room
    current_room->display();
}


// TODO: Implement attack
// HINTS:
// - Check if monster in room
// - If no monster, print message and return
// - If monster present, call combat()
//
void Game::attack() {
    // TODO: Attack monster in room
    Monster* monster = current_room->getMonster();
    if (!monster || !monster->isAlive()) {
        std::cout << "There is no monster here to attack." << std::endl;
        return;
    }
    combat(monster);
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
    std::cout << "=== COMBAT BEGINS ===" << std::endl;
    while (player->isAlive() && monster->isAlive()) {
        std::cout << "Choose action (attack/use <item>/flee): ";
        std::string action;
        std::getline(std::cin, action);
        std::istringstream iss(action);
        std::string verb;
        iss >> verb;
        std::string object;
        std::getline(iss, object);
        object.erase(0, object.find_first_not_of(" ")); // Trim leading spaces - Generated by Copilot
        if (verb == "attack") {
            int damage = player->calculateDamage();
            monster->takeDamage(damage);
            if (!monster->isAlive()) {
                std::cout << "You have defeated the " << monster->getName() << "!" << std::endl;
                player->gainExperience(monster->getExperienceReward());
                player->addGold(monster->getGoldReward());
                std::vector<Item*> loot = monster->dropLoot();
                for (size_t i = 0; i < loot.size(); i++) {
                    current_room->addItem(loot[i]);
                    std::cout << "The " << monster->getName() << " dropped: " << loot[i]->getName() << std::endl;
                }
                if (monster->getName() == "Dragon") {
                    victory = true; // Player wins the game
                }
                current_room->clearMonster();
                break;
            }
        } else if (verb == "use") {
            player->useItem(object);
        } else if (verb == "flee") {
            std::cout << "You fled from the " << monster->getName() << "." << std::endl;
            break;
        } else {
            std::cout << "Invalid action. Please choose attack, use <item>, or flee." << std::endl;
        }
        if (monster->isAlive()) {
            std::cout << "The " << monster->getName() << " attacks you!" << std::endl;
            int damage = monster->calculateDamage();
            player->takeDamage(damage);
        }
    }
    std::cout << "=== COMBAT ENDS ===" << std::endl;
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
    Item* item = current_room->getItem(item_name);
    if (item) {
        player->addItem(item);
        current_room->removeItem(item_name);
    } else {
        std::cout << "There is no item named '" << item_name << "' here." << std::endl;
    }   
}


// TODO: Implement inventory
//
void Game::inventory() {
    // TODO: Display player inventory
    player->displayInventory();
}


// TODO: Implement useItem
// HINTS:
// - Call player->useItem(item_name)
//
void Game::useItem(const std::string& item_name) {
    // TODO: Use item from inventory
    player->useItem(item_name);
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
    Item* item = player->getItem(item_name);
    if (!item) {
        std::cout << "You don't have an item named '" << item_name << "'." << std::endl;
        return;
    }
    if (item->getType() == "Weapon") {
        player->equipWeapon(item_name);
    } else if (item->getType() == "Armor") {
        player->equipArmor(item_name);
    } else {
        std::cout << "You can't equip that type of item." << std::endl;
    }
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
    std::cout << "=== Available Commands ===" << std::endl;
    std::cout << "go <direction>  - Move in specified direction (north, south, east, west)" << std::endl;
    std::cout << "look            - Look around the current room" << std::endl;
    std::cout << "attack          - Attack the monster in the room" << std::endl;
    std::cout << "pickup <item>   - Pick up an item from the room" << std::endl;
    std::cout << "inventory       - Show your inventory" << std::endl;
    std::cout << "use <item>      - Use a consumable item from your inventory" << std::endl;
    std::cout << "equip <item>    - Equip a weapon or armor from your inventory" << std::endl;
    std::cout << "stats           - Show your character stats" << std::endl;
    std::cout << "help            - Show this help message" << std::endl;
    std::cout << "quit            - Exit the game" << std::endl;
    std::cout << "==========================" << std::endl;
}
