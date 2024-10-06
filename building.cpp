#include "building.h"


building::building(uint16_t x, uint16_t y) {
	this->position = sf::Vector2f(x,y);

}


void building::draw(sf::RenderWindow* w) const {
	sf::RectangleShape shape;
	shape.setFillColor(sf::Color::Black);
	shape.setPosition(position);
	shape.setSize(sf::Vector2f(50,50));
	w->draw(shape);
}
