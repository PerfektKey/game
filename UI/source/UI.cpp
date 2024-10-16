#include "../UI.h"


UI::UI() {
	// three layers
	comps.push_back(std::unordered_map<std::string,component*>());
	comps.push_back(std::unordered_map<std::string,component*>());
	comps.push_back(std::unordered_map<std::string,component*>());
}

void UI::add(std::string k, component* c, uint16_t layer) {
	if (layer > 10) std::cout << "In " << this << " UI::add, adding to layer " << layer << " is this correct?\n";
	while (layer > comps.size()) {
		comps.push_back(std::unordered_map<std::string,component*>());
	}
	comps[layer][k] = c;

}
std::vector<std::unordered_map<std::string, component*>>* UI::getComponents() {return &comps;}
component* UI::getComponent(std::string k) {
	for (uint32_t i = 0; i < comps.size(); i++) {
		if (comps[i].find(k) == comps[i].end()) return NULL;

		return comps[i].at(k);
	}
	return NULL;
}
component* UI::getComponent(std::string k, uint16_t layer) {
	if (layer > comps.size()) return NULL;
	
	if (comps[layer].find(k) == comps[layer].end()) return NULL;

	return comps[layer].at(k);
	return NULL;
}
void UI::draw(sf::RenderWindow* w) const {
	for (const auto& layer : comps)
	for (const auto& [k,c] : layer)
		c->draw(w);
}

void UI::action(sf::Event e, sf::Vector2f mouse ) {
	for (auto& layer : comps)
	for (auto& [k,c] : layer) {
		c->action(e, mouse);
		c->focusedMouse(mouse);
	}
}

void UI::setVisibility(bool b) {
	for (auto& layer : comps)
	for (auto& [k,c] : layer) {
		c->setVisibility(b);
	}
}
