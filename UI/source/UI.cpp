#include "../UI.h"


UI::UI() {

}

void UI::add(component* c) {comps.push_back(c);}
std::vector<component*>* UI::getComponents() {return &comps;}

void UI::draw(sf::RenderWindow* w) const {
	for (const auto c : comps)
		c->draw(w);
}

void UI::action(sf::Event e, sf::Vector2f mouse ) {
	for (auto c : comps) {
		c->action(e, mouse);
		c->focusedMouse(mouse);
	}
}

void UI::setVisibility(bool b) {
	for (auto c : comps) {
		c->setVisibility(b);
	}
}
