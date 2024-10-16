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

void PlaceTile(sf::Vector2f, world*);
void printTileInfo(sf::Vector2f, world*);

// enum for block types
enum bs {
	Nothing,
	Base,
	Spawner,
	Inserter,
	Vault
};
bs choosen;
building* bFactorie(sf::Vector2f, world*);

// The functions for the buttons that select the building
void selectBase();
void selectSpawner();
void selectInserter();
void selectVault();

int main () {
	choosen = bs::Spawner;
	std::filesystem::path cwd = std::filesystem::current_path();
	std::cout << cwd << "\n";
	
	// creating window
	sf::RenderWindow window(sf::VideoMode(1000,800), "Bakteria Game");

	// create world object
	world WORLD(20, 20, TileSize);

	// Mouse Position	
	sf::Vector2i mouseP;
	sf::Vector2f previousMapP = sf::Vector2f(0,0);
	sf::Vector2f mapPosition= sf::Vector2f(0,0);

	sf::Clock deltaClock;
	sf::Time dt;


	// Game loop
	while (window.isOpen()) {
	
		// get mouse position and convert it to world position	
		mouseP = sf::Mouse::getPosition(window);
		sf::Vector2f MapPosition = sf::Vector2f( std::floor(mouseP.x/TileSize) , std::floor(mouseP.y/TileSize) ); 

		//- checking for events 
		sf::Event event;
		while (window.pollEvent(event)) {
			// check if window/game closed
			if (event.type == sf::Event::Closed)
				window.close();
			// Check if building is placed
			else if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				if (choosen == bs::Nothing){ 
					WORLD.printInfo(MapPosition);
				} else { 
					PlaceTile(MapPosition,&WORLD );
			//		previousMapP = sf::Vector2f(0,0);
				}
			} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				choosen = bs::Nothing;
			} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
				building* BF = WORLD.getBuilding(MapPosition);
				if (BF == NULL) break;
				std::cout << "Removing 99 copper from " << BF << "\n";
				uint16_t a = BF->getInventory()->remove(ItemType::Copper, 99);
				std::cout << "\tmanaged to remove " << a << "\n";
			} else {
			}
		}

		previousMapP = MapPosition;
		//l.focusedMouse(sf::Vector2f(mouseP.x, mouseP.y));

		WORLD.update(dt.asSeconds()); // updating

		//time += dt.asSeconds();
		dt = deltaClock.restart();

		// updating the frame
		window.clear(sf::Color(180,180,180));
		WORLD.draw(&window);
		window.display();
	}
	
	return 0;
}


void selectBase() {
	choosen = bs::Base;	
}
void selectSpawner() {
	choosen = bs::Spawner;
}
void selectInserter() {
	choosen = bs::Inserter;
}
void selectVault() {
	choosen = bs::Vault;
}
building* bFactorie(sf::Vector2f WP, world* w) {
	switch (choosen) {
		case bs::Nothing:
			return NULL;
		case bs::Base:
			return new building(WP, w, 5, 5);
		case bs::Spawner:
			return new spawner(WP, w, 5 , 5, ItemType::Copper);
		case bs::Inserter:
			return new inserter(WP, w, 2, 2);
		case bs::Vault:
			return new vault(WP, w, 10, 50);
	}

	return NULL;
}


void PlaceTile(sf::Vector2f MapPosition, world* w)
{
	// change the map coordinates to world positioni
	sf::Vector2f WorldPosition = sf::Vector2f(MapPosition.x*TileSize , MapPosition.y*TileSize );
	building* b = bFactorie(WorldPosition, w);
	if (b == NULL) return;
	if (w->setBuilding(MapPosition.x, MapPosition.y, b) == NULL) 
		std::cout << "Placed new tile at: " << MapPosition.x << ", " << MapPosition.y << "\n";
	else {
		std::cout << "Tile: " << MapPosition.x << ", " << MapPosition.y << " is already in use\n";
		w->printInfo(MapPosition);
		delete b;
	}
}


void printTileInfo(sf::Vector2f MapP, world* w) 
{
	w->printInfo(MapP);
}
