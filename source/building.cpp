#include "../header/building.h"


building::building(uint16_t x, uint16_t y, world* w) {
	this->screenPosition = sf::Vector2f(x,y);
	this->WORLD = w;
	this->mapPosition = sf::Vector2f(0,0);

	this->inv = inventory(5,5);
}


void building::draw(sf::RenderWindow* w) const {
	sf::RectangleShape shape;
	shape.setFillColor(sf::Color::Black);
	shape.setPosition(screenPosition);
	shape.setSize(sf::Vector2f(50,50));
	w->draw(shape);
}

void building::printInfo() const
{
	std::cout << "#############\n";
	std::cout << "Building []\n";
	std::cout << "at Map x: " << mapPosition.x << " Map y: " << mapPosition.y << "\n";
	std::cout << "at Screen x: " << screenPosition.x << " Screen y: " << screenPosition.y << "\n";

	std::cout << "Inventory: \n";
	inv.print();

	std::cout << "#############\n";
}
