#include "../component.h"


component::component() {
	this->show = false;
	this->position = sf::Vector2f(0,0);
}
component::~component() {

}

void component::setPosition(sf::Vector2f v) {this->position = v;}
sf::Vector2f component::getPosition() const {return this->position;}

void component::draw(sf::RenderWindow* w) const {}
void component::action() {}

void component::setText(std::string s) {this->text = s;}
std::string component::getText() const {return text;}
