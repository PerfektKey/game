#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include "header/world.h"
#include <stdint.h>
#include <thread>

#include "header/worldGeneration.h"

// blocks
#include "header/building.h"
#include "blocks/spawner.h"
#include "blocks/inserter.h"
#include "blocks/vault.h"
#include "blocks/conveyor.h"
#include "blocks/crafter.h"

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

void moveCamera(sf::Event, float);


// data
enum Buildings {
	nothing,
	Spawner,
	Inserter,
	Vault,
	Conveyor,
	Crafter
};
Buildings toBuild;

std::unordered_map<std::string, recepie> FurnaceReceps = {
	{"Test 101", recepie(1, {
				slot(ItemType::CopperOre, 1)
			},
			{
				slot(ItemType::CopperPlate, 1)
			}
			)
	}

};

sf::Vector2f mousePosition = sf::Vector2f();
const uint16_t TILE_SIZE = 50;
world WORLD(20,20, TILE_SIZE);

uint16_t rotation = 0;
bool oPressed = false;

 sf::Vector2f cameraPosition;
 uint16_t cameraSpeed;
 float cameraZoom;
 label cameraPositionUI(sf::Vector2f(30,30), NULL, "assets/arial.ttf", 30, sf::Color::Black, "x: 0 y: 0");

uint16_t frame = 0;
sf::Clock deltaClock;
sf::Time dt;
label fps(sf::Vector2f(30,70), NULL, "assets/arial.ttf", 30, sf::Color::Black, "fps: 0");

// A UI inventory
inventoryInterface interface;

sf::RenderWindow window(sf::VideoMode(1000, 800), "SFML GAME");

void updateLoop() {

	std::cout << "in thread " << "\n";
}


int main() {

	//
	toBuild = Buildings::nothing;

	// window
	
	worldGeneration::fill(&WORLD);

	cameraPosition = sf::Vector2f(0,0);
	cameraSpeed = 500;
	cameraZoom = 1;


	std::thread updater(updateLoop);

	// Game Loop
	while (window.isOpen()) {
		
		// get mouse Position
		sf::Vector2i preConv = sf::Mouse::getPosition(window);
		mousePosition = sf::Vector2f(preConv.x, preConv.y) + cameraPosition;
		
		sf::Event event;
		while (window.pollEvent(event)) {
			InputEvent(event, &window);
			moveCamera(event, dt.asSeconds());
		}

		fps.setContent("fps: " + std::to_string(uint16_t(1000/dt.asSeconds())));

		// drawing
		interface.update();
		WORLD.update(dt.asSeconds(), frame);
		dt = deltaClock.restart();
		window.clear(sf::Color(180, 180, 180));
		WORLD.draw(&window);
		interface.draw(&window);
		cameraPositionUI.draw(&window);
		fps.draw(&window);
		window.display();
		frame++;  // overflow resets frame counter
	}

	updater.join();
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
	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5)) {
		toBuild = Buildings::Crafter;
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

void moveCamera(sf::Event e, float dt) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		cameraPosition.y -= cameraSpeed * dt;
	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		cameraPosition.y += cameraSpeed * dt;
	} 
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		cameraPosition.x += cameraSpeed * dt;
	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		cameraPosition.x -= cameraSpeed * dt;
	}

	if (cameraPosition.x < 0) cameraPosition.x = 0;
	if (cameraPosition.y < 0) cameraPosition.y = 0;
	
	WORLD.cameraMoved(cameraPosition);
	cameraPositionUI.setContent("x: "+ std::to_string((int16_t)cameraPosition.x) + " y: " + std::to_string((int16_t)cameraPosition.y));
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
			return new spawner(worldPosition, &WORLD,"assets/blocks/spawner/spawner01.png", 5,5, ItemType::CopperOre, 2);
		case Buildings::Inserter:
			return new inserter(worldPosition, &WORLD, "assets/blocks/inserter/inserter02.png", 1, rotation, 2);
		case Buildings::Vault:
			return new vault(worldPosition, &WORLD, "assets/blocks/storage/storage01.png", 10, 20);
		case Buildings::Conveyor:
			return new conveyor(worldPosition, &WORLD, "assets/blocks/conveyor/conveyor01.png", 6, 1, rotation, 3 );
		case Buildings::Crafter:
			return new crafter(worldPosition, &WORLD, "assets/blocks/crafter/crafter01.png", &FurnaceReceps, 1);
	}

	return NULL;
}
void placeBuilding(sf::Vector2f pos) {
	if (pos.x < 0 || pos.y < 0) return;
	// get building to place
	building* b = buildingFactorie(sf::Vector2f(pos.x*TILE_SIZE , pos.y*TILE_SIZE));

	if (b == NULL) return;

	// place building
	if (WORLD.set(pos, b) == NULL) return;

	delete b;
}
