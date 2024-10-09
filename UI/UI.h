#pragma once

#include <SFML/Graphics.hpp>
#include "component.h"
#include <vector>

class UI {
protected:
	std::vector<component*> comps;
	
public:
	UI();
	
	void add(component*);
	std::vector<component*>* getComponents();

	void draw(sf::RenderWindow*) const;
	void action(sf::Event, sf::Vector2f);

	void setVisibility(bool);
};
