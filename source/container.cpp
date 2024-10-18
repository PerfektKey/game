#include "../UserInterface/container.h"


container::container() {
	mShow = false;

	mComps.push_back(std::unordered_map<std::string, component*>());
	mComps.push_back(std::unordered_map<std::string, component*>());
	mComps.push_back(std::unordered_map<std::string, component*>());
}


component* container::add(std::string name, component* c, uint16_t layer) {
	if (layer > 10) std::cout << "\033[31mTrying to acces layer " << layer << " is this correct?\033[37m\n";
	while (layer >= mComps.size())  mComps.push_back(std::unordered_map<std::string, component*>());

	mComps[layer][name] = c;
	
	return NULL;
}

component* container::get(std::string name) {
	// loop through layers
	for (auto& layer : mComps) {
		if (layer.find(name) == layer.end()) continue;

		return layer.at(name);
	}

	return NULL;
}
component* container::get(std::string name, uint16_t layer) {
	// loop through layers
	if (mComps.at(layer).find(name) == mComps.at(layer).end()) return NULL;

	return mComps.at(layer).at(name);

}



void container::show(bool b) {
	mShow = b;
}
void container::draw(sf::RenderWindow* w) {
	if (!mShow) return;

	for (int i = mComps.size()-1; i >= 0; i--)
	for (auto& [k,v] : mComps[i])
		if (v != NULL) v->draw(w);
}

void container::action(sf::Event e, sf::Vector2f p) {
	for (int i = mComps.size()-1; i >= 0; i--)
	for (auto& [k,v] : mComps[i])
		if (v != NULL) v->action(e,p);
}
