#include "../label.h"

// my finger is long

label::label(sf::Vector2f p, std::string t, sf::Color c, uint16_t s, std::string f) :
component(p, sf::Vector2f( (s/2)*string.length()+2 , s+3) ) {

	this->characterSize = s;	
	this->string = t;	

	this->font.loadFromFile(f);
	text.setFont(font);
	text.setCharacterSize(s);
	text.setString(string);
	text.setFillColor(c);

	text.setPosition(p);
}
label::~label() {

}

void label::setPosition(sf::Vector2f v) {
	this->screenPosition = v;
	text.setPosition(screenPosition);
	hitbox.setPosition(screenPosition + sf::Vector2f(-1,1)); // moving the hitbox to better fit the text
}

void label::draw(sf::RenderWindow* w) const {
	if (!show) return;
	
	w->draw(text);
}
void label::action(sf::Event e, sf::Vector2f mouse) {
	// testing if the mouseposition is in the hitbox
	if (mouse.x > screenPosition.x-1 && mouse.x+hitboxSize.x && mouse.y > screenPosition.y+1 && mouse.y < screenPosition.y+hitboxSize.y) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
			focusedByMouse = true;
		} else if (sf::Event::MouseButtonReleased) {
			focusedByMouse = false;
		}
	}
}

void label::focusedMouse(sf::Vector2f mouse) {
	if (!focusedByMouse)
		return;

	setPosition(mouse - sf::Vector2f(hitboxSize.x/2 , hitboxSize.y/2) );
}

void label::setText(std::string s) {this->string = s;}
std::string label::getText() const {return string;}
