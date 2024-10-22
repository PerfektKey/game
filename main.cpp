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
#include "blocks/conveyor.h"

// UI
#include "UserInterface/container.h"
#include "UserInterface/component.h"
#include "UserInterface/label.h"
#include "UserInterface/inventoryInterface.h"

// functions decleration
void InputEvent(sf::Event, sf::RenderWindow*);
building* buildingFactorie(sf::Vector2f);
void placeBuilding(sf::Vector2f);
void rotate();

// data
enum Buildings {
	nothing,
	Spawner,
	Inserter,
	Vault,
	Conveyor
};
Buildings toBuild;

sf::Vector2f mousePosition = sf::Vector2f();
const uint16_t TILE_SIZE = 50;
world WORLD(20,20, TILE_SIZE);

uint16_t rotation = 0;
bool oPressed = false;

uint16_t frame = 0;
sf::Clock deltaClock;
sf::Time dt;

// A UI inventory
inventoryInterface interface;


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

		// drawing
		window.clear(sf::Color(180, 180, 180));
		WORLD.draw(&window);
		interface.draw(&window);
		interface.update();
		WORLD.update(dt.asSeconds(), frame);
		window.display();

		dt = deltaClock.restart();
		frame++;
	}


}


void InputEvent(sf::Event e, sf::RenderWindow* w) {
	
	interface.action(e, mousePosition);

	if (e.type == sf::Event::Closed) {
		w->close();
	// building choose related 
	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
		toBuild = Buildings::Spawner;	
	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
		toBuild = Buildings::Inserter;	
	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {
		toBuild = Buildings::Vault;
	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)) {
		toBuild = Buildings::Conveyor;
	} else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
		toBuild = Buildings::nothing; 
		rotation = 0; // reseting rotation
	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::O)) {
		if (toBuild != Buildings::nothing) rotate();
		oPressed = true;
	} else if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		// eithe place a building or print the info
		if (toBuild != Buildings::nothing)
			placeBuilding(WORLD.screenToMap(mousePosition));
		else {
			building* b =  WORLD.get(WORLD.screenToMap(mousePosition));
			if (b != NULL) interface.setRef(b);
			//WORLD.printInfo(WORLD.screenToMap(mousePosition));
		}
	} else if (e.type == sf::Event::KeyReleased) {
		if (e.key.code == sf::Keyboard::O) oPressed = false;
	}
}

void rotate() {
	if (oPressed) return;
	rotation += 90;
	if (rotation >= 360) rotation = 0;
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
		case Buildings::Conveyor:
			return new conveyor(worldPosition, &WORLD, 6, 1, rotation, 3 );
	}

	return NULL;
}
void placeBuilding(sf::Vector2f pos) {
	// get building to place
	building* b = buildingFactorie(sf::Vector2f(pos.x*TILE_SIZE , pos.y*TILE_SIZE));

	if (b == NULL) return;

	// place building
	if (WORLD.set(pos, b) == NULL) return;

	delete b;
}
