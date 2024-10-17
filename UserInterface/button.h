#pragma once

#include <functional>

#include "component.h"

class container;

class button : public component {
private:
	std::function<void(component*)> mPressedFunc;
	bool mState; // true if pressed, false if not
public:
	button(sf::Vector2f, sf::Vector2f, container*, sf::Color, std::function<void(component*)>); // position, size, parent, color
	button(sf::Vector2f, sf::Vector2f, container*, sf::Color); // position, size, parent, color
	
	// a functoin to check if it has been pressed
	// either calls a function pointer or can be accesed throgh isPressed()
	
	// mouse Position
	virtual void action(sf::Event, sf::Vector2f);
	

	bool isPressed() const;

};
