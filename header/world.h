#pragma once
#include<vector>
#include<stdint.h>
#include <SFML/Graphics.hpp>
#include <cmath>

#include "tile.h"

class building;


class world {
private:
	std::vector<std::vector<building*>> map;
	std::vector<std::vector<tile>> tiles;

	const sf::Vector2f* mpCameraPosition;
	
	sf::Vector2f mWindowSize;

	uint16_t tileSize;

	uint16_t width;
	uint16_t height;
public:
	world(uint16_t,uint16_t, uint16_t, sf::Vector2f, sf::Vector2f*);

	building* get(uint16_t, uint16_t);
	building* get(sf::Vector2f);
	building* set(uint16_t,uint16_t, building*);	
	building* set(sf::Vector2f, building*);	
	void printInfo(sf::Vector2f);

	void setTile(sf::Texture*, sf::Vector2f);
	void setTile(sf::Texture*, uint16_t, uint16_t);

	void update(float, uint16_t);
	void draw(sf::RenderWindow*);
	void cameraMoved(sf::Vector2f);

	uint16_t getWidth () const;
	uint16_t getHeight() const;
	uint16_t getTileSize() const;

	sf::Vector2f screenToMap(sf::Vector2f) const;
	bool isInWorld(sf::Vector2f) const;
	bool inScreen(const sf::Vector2f&) const;	
};
