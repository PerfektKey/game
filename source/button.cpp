#include "../UserInterface/button.h"

button::button(sf::Vector2f p, sf::Vector2f s, container* pa, sf::Color c, std::function<void(component*)> fp) :
	component(p, s, pa, c) { // position, size, parent, color
	
	mPressedFunc = fp;

}
	
button::button(sf::Vector2f p, sf::Vector2f s, container* pa, sf::Color c) : 
	component(p, s, pa, c) { // position, size, parent, color

	mPressedFunc = NULL;
}

void button::action(sf::Event e, sf::Vector2f mp) {
	mState = false;

	// checking if pressed
	if ( !sf::Mouse::isButtonPressed(sf::Mouse::Left) ) return; // if not mouse pressed: return

	bool xBounds = mp.x > mGlobalPosition.x && mp.x < mGlobalPosition.x+mHitboxSize.x;
	bool yBounds = mp.y > mGlobalPosition.y && mp.y < mGlobalPosition.y+mHitboxSize.y;

	if ( !(xBounds && yBounds) ) return; // not in bounds
	
	// is pressed
	
	mState = true;

	if (mPressedFunc != NULL) mPressedFunc(this);
}

bool button::isPressed() const {return mState;}
