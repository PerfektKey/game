#pragma once
#include<vector>
#include<stdint.h>
#include "building.h"
#include <SFML/Graphics.hpp>

class world {
private:
	std::vector<std::vector<building*>> map;

	uint16_t tileSize;

	uint16_t width;
	uint16_t height;
public:
	world(uint16_t,uint16_t, uint16_t);

	building* getBuilding(uint16_t, uint16_t) const;
	building* setBuilding(uint16_t,uint16_t, building*);	
	void printInfo(sf::Vector2f);

	void update();
	void draw(sf::RenderWindow*) const;

	uint16_t getWidth () const;
	uint16_t getHeight() const;

	sf::Vector2f windowToWorldPosition(sf::Vector2f) const;
	bool isInWorld(sf::Vector2f) const;
	
};
