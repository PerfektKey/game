#pragma once

#include <stdint.h>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "inventory.h"

class world;

class building {
protected:
	sf::Vector2f screenPosition;
	world* WORLD;
	sf::Vector2f mapPosition;

	inventory inv;
public:
	building(uint16_t, uint16_t, world*, uint16_t,uint16_t);
	virtual ~building();

	virtual void update();

	uint16_t getX() const;
	uint16_t getY() const;

	void draw(sf::RenderWindow*) const;
	
	void printInfo() const;
};
