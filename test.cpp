#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include "header/world.h"
#include <stdint.h>

// blocks
#include "header/building.h"
#include "blocks/spawner.h"
#include "blocks/inserter.h"
#include "blocks/vault.h"

#include <filesystem>

uint16_t TileSize = 50;



void test();

int main () {
	test();
	
	return 0;
}


void test() {

	world WORLD(20, 30, TileSize);

	// set spawner in world
	sf::Vector2f SMP(10,10);
	building* b = new spawner(SMP*(float)50, &WORLD, 5,5, ItemType::Copper);
	WORLD.setBuilding(SMP.x, SMP.y, b);
	
	// set inserter
	sf::Vector2f IMP(11,10);
	b = new inserter(IMP*(float)50, &WORLD, 1, 1);
	WORLD.setBuilding(IMP.x, IMP.y, b);
	
	// set Vault
	sf::Vector2f VMP(12,10);
	b = new vault(VMP*(float)50, &WORLD, 10, 10);
	WORLD.setBuilding(VMP.x, VMP.y, b);
	
	// print inventory of VAULT
	std::cout << "Break Point 1\n";
	WORLD.printInfo(VMP);
	std::cout << "Break Point 2\n";
	// Update 5 times and print inventory again
	for (int i = 0; i < 5; i++) {
		std::cout << "Break Point " << std::to_string(3+i) << "\n";;
		WORLD.update(1.5);
		std::cout << "Break Point " << std::to_string(3+i) << ".5\n";;
	}
	//print again
	std::cout << "\033[31m !! \033[37m\n"; 
	WORLD.printInfo(SMP);
	WORLD.printInfo(IMP);
	WORLD.printInfo(VMP);
}
