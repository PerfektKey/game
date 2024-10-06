#pragma once

#include <stdint.h>
#include <SFML/Graphics.hpp>

class building {
private:
	sf::Vector2f position;
public:
	building(uint16_t, uint16_t);


	uint16_t getX() const;
	uint16_t getY() const;

	void draw(sf::RenderWindow*) const;

};
