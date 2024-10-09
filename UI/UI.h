#pragma once

#include<iostream>

#include <SFML/Graphics.hpp>
#include "component.h"
#include <unordered_map>
#include <string>

class UI {
protected:
	std::unordered_map<std::string, component*> comps;
	
public:
	UI();
	
	void add(std::string, component*);
	std::unordered_map<std::string, component*>* getComponents();
	component* getComponent(std::string);

	void draw(sf::RenderWindow*) const;
	void action(sf::Event, sf::Vector2f);

	void setVisibility(bool);
};
