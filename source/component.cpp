#include "../UserInterface/component.h"

component::component(sf::Vector2f pos, sf::Vector2f size, container* c) {
	mGlobalPosition = pos;
	mRelativPosition = sf::Vector2f(0,0);
	mRelativAnchor = sf::Vector2f(0,0);

	mParent = c;
	
	mHitboxSize = size;
	mHitbox.setSize(size);
	mHitbox.setFillColor(sf::Color(0,0,0,0));
	mHitbox.setPosition(pos);
}
				      
component::component(sf::Vector2f pos, sf::Vector2f size, container* p, sf::Color c) :
	component(pos, size, p) {
	
	mHitbox.setFillColor(c);
}

void component::draw(sf::RenderWindow* w){
	mHitbox.setPosition(mGlobalPosition);
	w->draw(mHitbox);
}

void component::update(float dt) {
	// nothing to see here
}
void component::action(sf::Event e, sf::Vector2f mp) {
	// looks so empty >:(
}

void component::setSize(sf::Vector2f s) {mHitboxSize = s;}
sf::Vector2f component::getSize() const {return mHitboxSize;}

void component::setGlobalPosition(sf::Vector2f pos) {mGlobalPosition = pos;}
sf::Vector2f component::getGlobalPosition() const {return mGlobalPosition;}

void component::setRelativPosition(sf::Vector2f p) {
	mRelativPosition = p;
	mGlobalPosition = mRelativPosition + mRelativAnchor;
}
sf::Vector2f component::getRelativPosition() const {return mRelativPosition;}

void component::setRelativAnchor(sf::Vector2f p) {mRelativAnchor = p;}
sf::Vector2f component::getRelativAnchor() const {return mRelativAnchor;}

container* component::getParent() {return mParent;}
