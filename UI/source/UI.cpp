#include "../UI.h"


UI::UI() {

}

void UI::add(std::string k, component* c) {
	comps[k] = c;

}
std::unordered_map<std::string, component*>* UI::getComponents() {return &comps;}
component* UI::getComponent(std::string k) {
	if (comps.find(k) == comps.end()) return NULL;

	return comps.at(k);
}

void UI::draw(sf::RenderWindow* w) const {
	for (const auto& [k,c] : comps)
		c->draw(w);
}

void UI::action(sf::Event e, sf::Vector2f mouse ) {
	for (auto& [k,c] : comps) {
		c->action(e, mouse);
		c->focusedMouse(mouse);
	}
}

void UI::setVisibility(bool b) {
	for (auto& [k,c] : comps) {
		c->setVisibility(b);
	}
}
