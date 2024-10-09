#include "../component.h"


component::component(sf::Vector2f p, sf::Vector2f size) {
	this->show = false;
	this->screenPosition = p;

	this->focusedByMouse = false;

	hitbox.setFillColor(sf::Color(255,255,255,0));
	this->hitboxSize = size;
	hitbox.setSize(hitboxSize);
}
component::~component() {

}

void component::setPosition(sf::Vector2f v) {
	this->screenPosition = v;
//	label.setPosition(screenPosition);
	hitbox.setPosition(screenPosition + sf::Vector2f(-1,1)); // moving the hitbox to better fit the text
}
sf::Vector2f component::getPosition() const {return this->screenPosition;}

void component::draw(sf::RenderWindow* w) const {
	if (!show) return;
	
	w->draw(hitbox);
}
void component::action(sf::Event e, sf::Vector2f mouse) {
}

void component::focusedMouse(sf::Vector2f mouse) {
}

void component::setVisibility(bool b) {show = b;}
