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

// functions decleration
void InputEvent(sf::Event, sf::RenderWindow*);
building* buildingFactorie(sf::Vector2f);
void placeBuilding(sf::Vector2f);

// data
enum Buildings {
	nothing,
	Spawner,
	Inserter,
	Vault
};
Buildings toBuild;

sf::Vector2f mousePosition = sf::Vector2f();
const uint16_t TILE_SIZE = 50;
world WORLD(20,20, TILE_SIZE);

sf::Clock deltaClock;
sf::Time dt;

int main() {
	
	//
	toBuild = Buildings::nothing;

	// window
	sf::RenderWindow window(sf::VideoMode(1000, 800), "SFML GAME");
	
	// Game Loop
	while (window.isOpen()) {
		
		// get mouse Position
		sf::Vector2i preConv = sf::Mouse::getPosition(window);
		mousePosition = sf::Vector2f(preConv.x, preConv.y);
		
		sf::Event event;
		while (window.pollEvent(event)) {
			InputEvent(event, &window);
		}

		window.clear(sf::Color(180, 180, 180));
		WORLD.draw(&window);
		WORLD.update(dt.asSeconds());
		window.display();

		dt = deltaClock.restart();
	}


}


void InputEvent(sf::Event e, sf::RenderWindow* w) {
	
	if (e.type == sf::Event::Closed) {
		w->close();
	// building choose related 
	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
		toBuild = Buildings::Spawner;	
	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
		toBuild = Buildings::Inserter;	
	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {
		toBuild = Buildings::Vault;
	} else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
		toBuild = Buildings::nothing; 
	} else if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		// eithe place a building or print the info
		if (toBuild != Buildings::nothing)
			placeBuilding(WORLD.screenToMap(mousePosition));
		else
			WORLD.printInfo(WORLD.screenToMap(mousePosition));
	}
}


building* buildingFactorie(sf::Vector2f worldPosition) {
	switch (toBuild) {
		case Buildings::nothing:
			return NULL;
		case Buildings::Spawner:
			return new spawner(worldPosition, &WORLD, 5,5, ItemType::Copper);
		case Buildings::Inserter:
			return new inserter(worldPosition, &WORLD, 2, 1);
		case Buildings::Vault:
			return new vault(worldPosition, &WORLD, 10, 20);
	}

	return NULL;
}
void placeBuilding(sf::Vector2f pos) {
	// get building to place
	building* b = buildingFactorie(sf::Vector2f(pos.x*TILE_SIZE , pos.y*TILE_SIZE));

	if (b == NULL) return;

	// place building
	if (WORLD.setBuilding(pos, b) == NULL) return;

	delete b;
}
