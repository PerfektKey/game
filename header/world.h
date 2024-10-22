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

	building* get(uint16_t, uint16_t);
	building* get(sf::Vector2f);
	building* set(uint16_t,uint16_t, building*);	
	building* set(sf::Vector2f, building*);	
	void printInfo(sf::Vector2f);

	void update(float, uint16_t);
	void draw(sf::RenderWindow*) const;

	uint16_t getWidth () const;
	uint16_t getHeight() const;

	sf::Vector2f screenToMap(sf::Vector2f) const;
	bool isInWorld(sf::Vector2f) const;
	
};
