#include "../header/building.h"

#include "../header/world.h"

building::building(sf::Vector2f sp, sf::Vector2f mp, world* w, uint16_t sa, uint16_t ss) {
	this->screenPosition = sp;
	this->WORLD = w;
	this->mapPosition = mp;

	this->UIvis = false;
	this->info = UI();
		
	this->inv = inventory(sa,ss);

	this->type = "Normal Tile";
}
building::building(sf::Vector2f sp, world* w, uint16_t sa, uint16_t ss) {
	this->screenPosition = sp;
	this->WORLD = w;
	this->mapPosition = WORLD->screenToMap(sp);

	this->UIvis = false;
	this->info = UI();
		
	this->inv = inventory(sa,ss);

	this->type = "Normal Tile";
}
building::~building() {}//I dont know if I should write anything in here

void building::update(float dt)
{

}
void building::UIAction(sf::Event e, sf::Vector2f mouseP) {
	info.action(e, mouseP);
}
inventory* building::getInventory() {
	return &inv;
}

void building::draw(sf::RenderWindow* w) const {
	sf::RectangleShape shape;
	shape.setFillColor(sf::Color::Black);
	shape.setPosition(screenPosition);
	shape.setSize(sf::Vector2f(50,50));
	w->draw(shape);

	if (UIvis) info.draw(w);
}

void building::printInfo() const
{
	std::cout << "#############\n";
	std::cout << "Building [" << type << "]\n";
	std::cout << "at Map x: " << mapPosition.x << " Map y: " << mapPosition.y << "\n";
	std::cout << "at Screen x: " << screenPosition.x << " Screen y: " << screenPosition.y << "\n";

	std::cout << "Inventory: \n";
	inv.print();

	std::cout << "#############\n";
}

void building::showUI(bool b){
	UIvis = b;
	info.setVisibility(b);
}
