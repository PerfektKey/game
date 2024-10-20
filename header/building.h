#pragma once

#include <stdint.h>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "inventory.h"
#include <string>
#include "../UserInterface/include.h"

class world;

void hideInterface(component*);

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

	virtual container* createUI() const;
	virtual container* createInventoryUI(const inventory*) const;
	virtual void updateUI(container*) const;
	virtual void updateInventoryUI(container*, const inventory*) const;

	virtual void update(float);

	sf::Vector2f getSize() const;
	sf::Vector2f getPosition() const;
	std::string getType() const;

	virtual void draw(sf::RenderWindow*) const;
	
	void printInfo() const;
};
