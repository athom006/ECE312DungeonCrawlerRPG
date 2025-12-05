#include <vector>
#include "Item.h"

int main() {
    std::vector<Item*> inventory;
    
    // Add items
    inventory.push_back(new Weapon("Sword", "Sharp blade", 5));
    inventory.push_back(new Armor("Shield", "Wooden shield", 2));
    inventory.push_back(new Consumable("Potion", "Heals", 20));
    
    // Display all
    for (int i = 0; i < inventory.size(); i++) {
        inventory[i]->displayInfo();
    }
    
    // Clean up - VERY IMPORTANT!
    for (int i = 0; i < inventory.size(); i++) {
        delete inventory[i];
    }
    inventory.clear();
    
    return 0;
}