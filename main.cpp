#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include "header/building.h"
#include "header/world.h"
#include <stdint.h>
#include "blocks/spawner.h"
#include "UI/component.h"

#include <filesystem>

uint16_t TileSize = 50;

void PlaceTile(sf::Vector2f, world*);
void printTileInfo(sf::Vector2f, world*);

int main () {


	std::filesystem::path cwd = std::filesystem::current_path();
	std::cout << cwd << "\n";
	
	// creating window
	sf::RenderWindow window(sf::VideoMode(1000,800), "Bakteria Game");

	// create world object
	world WORLD(20, 20, TileSize);

	// Mouse Position	
	sf::Vector2i mouseP;

	sf::Clock deltaClock;
	sf::Time dt;

	component l;
	l.setText("Test Text");
	l.setPosition(sf::Vector2f(50,50));

	// Game loop
	while (window.isOpen()) {
	
		// get mouse position and convert it to world position	
		mouseP = sf::Mouse::getPosition(window);
		sf::Vector2f MapPosition = sf::Vector2f( std::floor(mouseP.x/TileSize) , std::floor(mouseP.y/TileSize) ); 


		// checking for events 
		sf::Event event;
		while (window.pollEvent(event)) {
			// check if window/game closed
			if (event.type == sf::Event::Closed)
				window.close();
			// Check if building is placed
			else if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				PlaceTile(MapPosition,&WORLD );
			} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::U)) {
				std::cout << "Update\n";
			} else {
				l.action(event, sf::Vector2f(mouseP.x , mouseP.y));
			}
		}

		l.focusedMouse(sf::Vector2f(mouseP.x, mouseP.y));

		WORLD.update(dt.asSeconds()); // updating
		dt = deltaClock.restart();


		// updating the frame
		window.clear(sf::Color(180,180,180));
		l.draw(&window);
		WORLD.draw(&window);
		window.display();
	}
	
	return 0;
}



void PlaceTile(sf::Vector2f MapPosition, world* world)
{
	// change the map coordinates to world positioni
	sf::Vector2f WorldPosition = sf::Vector2f(MapPosition.x*TileSize , MapPosition.y*TileSize );
	building* b = new spawner(WorldPosition.x, WorldPosition.y, world, 5 , 5, ItemType::Copper);
	if (world->setBuilding(MapPosition.x, MapPosition.y, b) == NULL) 
		std::cout << "Placed new tile at: " << MapPosition.x << ", " << MapPosition.y << "\n";
	else {
		std::cout << "Tile: " << MapPosition.x << ", " << MapPosition.y << " is already in use\n";
		world->printInfo(MapPosition);
		delete b;
	}
}


void printTileInfo(sf::Vector2f MapP, world* w) 
{
	w->printInfo(MapP);
}
