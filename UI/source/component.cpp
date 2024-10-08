#include "../component.h"


component::component() {
	this->show = false;
	this->screenPosition = sf::Vector2f(0,0);
	this->text = "Empty text";

	this->focusedByMouse = false;

	this->font.loadFromFile("assets/arial.ttf");
	label.setFont(font);
	label.setCharacterSize(24);
	label.setString(text);
	label.setFillColor(sf::Color::Black);

//	hitbox.setFillColor(sf::Color::Red);
	hitbox.setFillColor(sf::Color(255,255,255,0));
	this->hitboxSize = sf::Vector2f( 12*text.length()+2 , 24+3);
	hitbox.setSize(hitboxSize); // +2 and +3 is to make the hitbox fit the text better
}
component::~component() {

}

void component::setPosition(sf::Vector2f v) {
	this->screenPosition = v;
	label.setPosition(screenPosition);
	hitbox.setPosition(screenPosition + sf::Vector2f(-1,1)); // moving the hitbox to better fit the text
}
sf::Vector2f component::getPosition() const {return this->screenPosition;}

void component::draw(sf::RenderWindow* w) const {
	w->draw(hitbox);
	w->draw(label);
}
void component::action(sf::Event e, sf::Vector2f mouse) {
	// testing if the mouseposition is in the hitbox
	if (mouse.x > screenPosition.x-1 && mouse.x+hitboxSize.x && mouse.y > screenPosition.y+1 && mouse.y < screenPosition.y+hitboxSize.y) {
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
			focusedByMouse = true;
		} else if (sf::Event::MouseButtonReleased) {
			focusedByMouse = false;
		}
	}
}

void component::focusedMouse(sf::Vector2f mouse) {
	if (!focusedByMouse)
		return;

	setPosition(mouse - sf::Vector2f(hitboxSize.x/2 , hitboxSize.y/2) );
}

void component::setText(std::string s) {this->text = s;}
std::string component::getText() const {return text;}
