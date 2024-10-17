#include "../UserInterface/component.h"

component::component(sf::Vector2f pos, sf::Vector2f size) {
	mGlobalPosition = pos;
	mRelativPosition = sf::Vector2f(0,0);
	mRelativAnchor = sf::Vector2f(0,0);
	
	mHitboxSize = size;
	mHitbox.setSize(size);
	mHitbox.setFillColor(sf::Color(0,0,0,0));
	mHitbox.setPosition(pos);
}
				      
component::component(sf::Vector2f pos, sf::Vector2f size, sf::Color c) :
	component(pos, size) {
	
	mHitbox.setFillColor(c);
}

void component::draw(sf::RenderWindow* w) const {
	w->draw(mHitbox);
}

void component::setSize(sf::Vector2f s) {mHitboxSize = s;}
sf::Vector2f component::getSize() const {return mHitboxSize;}

void component::setGlobalPosition(sf::Vector2f pos) {mGlobalPosition = pos;}
sf::Vector2f component::getGlobalPosition() const {return mGlobalPosition;}

void component::setRelativPosition(sf::Vector2f p) {mRelativPosition = p;}
sf::Vector2f component::getRelativPosition() const {return mRelativPosition;}

void component::setRelaticAnchor(sf::Vector2f p) {mRelativAnchor = p;}
sf::Vector2f component::getRelativAnchor() const {return mRelativAnchor;}
