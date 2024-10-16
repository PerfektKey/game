#include "../component.h"


component::component(sf::Vector2f p, sf::Vector2f size) {
	this->show = false;
	this->screenPosition = p;

	this->focusedByMouse = false;

	hitbox.setFillColor(sf::Color(255,255,255,0));
	this->hitboxSize = size;
	hitbox.setSize(hitboxSize);
	hitbox.setPosition(p);
}

component::component(sf::Vector2f p, sf::Vector2f size, sf::Color c) : component(p,size) {
	hitbox.setFillColor(c);
}
component::~component() {

}

void component::setPosition(sf::Vector2f v) {
	this->screenPosition = v;
//	label.setPosition(screenPosition);
	hitbox.setPosition(screenPosition + sf::Vector2f(-1,1)); // moving the hitbox to better fit the text
}
sf::Vector2f component::getPosition() const {return this->screenPosition;}

void component::setAnchorPosition(sf::Vector2f p) {
	anchorPosition = p;
}
sf::Vector2f component::getAnchorPosition() const {return anchorPosition;}

sf::Vector2f component::getRelativPosition() const {return relativPosition;}
void component::setRelativPosition(sf::Vector2f p) {
	relativPosition = p;
	screenPosition = p + anchorPosition;
}

void component::setMovable(bool b) {movable = b;}
bool component::getMovable() const {return movable;}
	
void component::draw(sf::RenderWindow* w) const {
	if (!show) return;
	
	w->draw(hitbox);
}
void component::action(sf::Event e, sf::Vector2f mouse) {
	// movable
	
	if (mouse.x > screenPosition.x-1 && mouse.x+hitboxSize.x && mouse.y > screenPosition.y+1 && mouse.y < screenPosition.y+hitboxSize.y) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
			focusedByMouse = true;
		} else if (sf::Event::MouseButtonReleased) {
			focusedByMouse = false;
		}
	}
}

void component::focusedMouse(sf::Vector2f mouse) {
	if (!focusedByMouse && !movable) return;

	setPosition(mouse);

}

void component::setVisibility(bool b) {show = b;}
bool component::getVisibility() const {return this->show;}
