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

void container::draw(sf::RenderWindow* w) {
	for (int i = mComps.size()-1; i >= 0; i--)
	for (auto& [k,v] : mComps[i])
		if (v != NULL) v->draw(w);
}
