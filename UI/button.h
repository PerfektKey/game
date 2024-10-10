#include "component.h"

#include <iostream>

class button : public component{
protected:
	bool pressed; // when the button is clicked, this is true
	bool canBePressed; // if it can be pressed

	void (*pressFunc)();
public:
	button(sf::Vector2f, sf::Vector2f, sf::Color, void (*pf)());

	virtual void action(sf::Event, sf::Vector2f);

	bool getStatus() const;

	bool getPressable() const;
	void setPressable(bool);
};
