#pragma once
#include<vector>
#include<stdint.h>
#include <SFML/Graphics.hpp>
#include <cmath>

class building;

class world {
private:
	std::vector<std::vector<building*>> map;

	uint16_t tileSize;

	uint16_t width;
	uint16_t height;
public:
	world(uint16_t,uint16_t, uint16_t);

	building* getBuilding(uint16_t, uint16_t);
	building* getBuilding(sf::Vector2f);
	building* setBuilding(uint16_t,uint16_t, building*);	
	void printInfo(sf::Vector2f);

	void update(float);
	void UIAction(sf::Event, sf::Vector2f);
	void draw(sf::RenderWindow*) const;

	uint16_t getWidth () const;
	uint16_t getHeight() const;

	sf::Vector2f screenToMap(sf::Vector2f) const;
	bool isInWorld(sf::Vector2f) const;
	
};
