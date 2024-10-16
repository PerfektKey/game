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

void test();

int main () {
	
//	test();
//	return 0;

	choosen = bs::Nothing;
	std::filesystem::path cwd = std::filesystem::current_path();
	std::cout << cwd << "\n";
	
	// creating window
	sf::RenderWindow window(sf::VideoMode(1000,800), "Bakteria Game");

	// create world object
	world WORLD(20, 20, TileSize);

	// Mouse Position	
	sf::Vector2i mouseP;
	sf::Vector2f previousMapP = sf::Vector2f(0,0);

	sf::Clock deltaClock;
	sf::Time dt;


	UI testUI;

	float time = 0;
	label l(sf::Vector2f(50,50), "Time: ", sf::Color::White, 24, "assets/arial.ttf");
	float FPS = 0;
	label labelFPS(sf::Vector2f(50,100), "FPS: ", sf::Color::White, 24, "assets/arial.ttf");
	testUI.add("Time Label", &l);
	testUI.add("FPS Label", &labelFPS);

	

	button SB(sf::Vector2f(400,700), sf::Vector2f(50,50), sf::Color::White, &selectBase);
	button SS(sf::Vector2f(460,700), sf::Vector2f(50,50), sf::Color::White, &selectSpawner);
	button SI(sf::Vector2f(520,700), sf::Vector2f(50,50), sf::Color::White, &selectInserter);
	button SV(sf::Vector2f(580,700), sf::Vector2f(50,50), sf::Color::White, &selectVault);
	testUI.add("button SB", &SB);
	testUI.add("button SS", &SS);
	testUI.add("button SI", &SI);
	testUI.add("button SV", &SV);

	testUI.setVisibility(true);
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
					testUI.action(event, sf::Vector2f(mouseP.x , mouseP.y));
					WORLD.printInfo(MapPosition);
					if (MapPosition != previousMapP || true) { // if the mouse was moved
						// if moved. then show info of the current building and hide the one of the previous
						building* b = WORLD.getBuilding(MapPosition.x , MapPosition.y);
						if (b != NULL) b->showUI(true);
						// hide previous building
//						b = WORLD.getBuilding(previousMapP.x , previousMapP.y);
//						if (b != NULL) b->showUI(false);
					}
				} else 
					PlaceTile(MapPosition,&WORLD );
				previousMapP = sf::Vector2f(0,0);
			} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				choosen = bs::Nothing;
			} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
				building* BF = WORLD.getBuilding(MapPosition);
				if (BF == NULL) break;
				std::cout << "Removing 99 copper from " << BF << "\n";
				uint16_t a = BF->getInventory()->remove(ItemType::Copper, 99);
				std::cout << "\tmanaged to remove " << a << "\n";
			} else {
				testUI.action(event, sf::Vector2f(mouseP.x , mouseP.y));
				WORLD.UIAction(event, sf::Vector2f(mouseP.x , mouseP.y));			
			}
		}

		previousMapP = MapPosition;
		//l.focusedMouse(sf::Vector2f(mouseP.x, mouseP.y));

		WORLD.update(dt.asSeconds()); // updating

		time += dt.asSeconds();
		FPS = 1000/dt.asSeconds();
		static_cast<label*>(testUI.getComponent("Time Label"))->setText("Time: " + std::to_string(time));
		static_cast<label*>(testUI.getComponent("FPS Label"))->setText("FPS: " + std::to_string((int)FPS));
		dt = deltaClock.restart();

		// updating the frame
		window.clear(sf::Color(180,180,180));
		WORLD.draw(&window);
		testUI.draw(&window);
		window.display();
	}
	
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
