#include "building.h"


building::building(uint16_t x, uint16_t y, world* w) {
	this->screenPosition = sf::Vector2f(x,y);
	this->WORLD = w;
}


void building::draw(sf::RenderWindow* w) const {
	sf::RectangleShape shape;
	shape.setFillColor(sf::Color::Black);
	shape.setPosition(screenPosition);
	shape.setSize(sf::Vector2f(50,50));
	w->draw(shape);
}


