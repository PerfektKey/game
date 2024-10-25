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

	uint16_t mFrame;

	uint16_t mRotation;
public:
	building(sf::Vector2f, sf::Vector2f, world*, uint16_t,uint16_t);
	building(sf::Vector2f, world*, uint16_t, uint16_t);
	virtual ~building();

	inventory* getInventory();

	virtual container* createUI() const;
	virtual container* createInventoryUI(const inventory*) const;
	virtual void updateUI(container*);
	virtual void updateInventoryUI(container*, const inventory*) const;

	virtual void update(float, uint16_t);

	sf::Vector2f getSize() const;
	sf::Vector2f getPosition() const;
	std::string getType() const;

	virtual void setRotation(uint16_t);
	uint16_t getRotation() const;

	virtual void draw(sf::RenderWindow*) const;
	
	void printInfo() const;
};
