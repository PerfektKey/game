#pragma once

#include<iostream>

#include <SFML/Graphics.hpp>
#include "component.h"
#include <unordered_map>
#include <string>

class UI {
protected:
	std::vector<std::unordered_map<std::string, component*>> comps; // The vector is the layers, index 0 is drawn and updated before index 1
	
public:
	UI();
	
	void add(std::string, component*, uint16_t=0);
	std::vector<std::unordered_map<std::string, component*>>* getComponents();
	component* getComponent(std::string);
	component* getComponent(std::string, uint16_t);

	void draw(sf::RenderWindow*) const;
	void action(sf::Event, sf::Vector2f);

	void setVisibility(bool);
};
