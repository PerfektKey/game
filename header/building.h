#pragma once

#include <stdint.h>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "inventory.h"
#include <string>
#include "../includes.h"

class world;

class building {
protected:
	sf::Vector2f screenPosition;
	world* WORLD;
	sf::Vector2f mapPosition;

	inventory inv;

	std::string type;

	UI info;	
	bool UIvis;
public:
	building(sf::Vector2f, sf::Vector2f, world*, uint16_t,uint16_t);
	building(sf::Vector2f, world*, uint16_t, uint16_t);
	virtual ~building();

	inventory* getInventory();

	virtual void update(float);

	uint16_t getX() const;
	uint16_t getY() const;

	void draw(sf::RenderWindow*) const;
	
	void printInfo() const;

	void showUI(bool);
};
