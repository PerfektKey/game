#pragma once

#include <stdint.h>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "inventory.h"
#include <string>

class world;

class building {
protected:
	sf::Vector2f screenPosition;
	sf::Vector2f mapPosition;
	sf::Vector2f mSize;

	world* WORLD;
	inventory inv;

	std::string type;
public:
	building(sf::Vector2f, sf::Vector2f, world*, uint16_t,uint16_t);
	building(sf::Vector2f, world*, uint16_t, uint16_t);
	virtual ~building();

	inventory* getInventory();

	virtual void update(float);

	sf::Vector2f getSize() const;
	sf::Vector2f getPosition() const;
	std::string getType() const;

	void draw(sf::RenderWindow*) const;
	
	void printInfo() const;
};
