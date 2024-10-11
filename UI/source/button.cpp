#include "../button.h"


button::button(sf::Vector2f p, sf::Vector2f s, sf::Color c, void (*pf)()) :
	component(p, s)
{
	hitbox.setFillColor(c); // just using hitbox as the button rectangle
	pressFunc = pf;
}


void button::action(sf::Event e, sf::Vector2f p) {
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		if (p.x > screenPosition.x && p.x < screenPosition.x+hitboxSize.x && p.y > screenPosition.y && p.y < screenPosition.y+hitboxSize.y) {
			// this button is right clicked
			pressFunc();
		}
}
