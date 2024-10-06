#pragma once

#include <stdint.h>
#include <SFML/Graphics.hpp>
#include <iostream>

class world;

class building {
private:
	sf::Vector2f screenPosition;
	world* WORLD;
	sf::Vector2f mapPosition;
public:
	building(uint16_t, uint16_t, world*);


	uint16_t getX() const;
	uint16_t getY() const;

	void draw(sf::RenderWindow*) const;
	
	void printInfo() const;
};
