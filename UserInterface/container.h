#pragma once

#include  <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include "component.h" 

class container {
protected:
	std::vector<std::unordered_map<std::string , component*>> mComps;
	bool mShow;
public:
	container();

	component* add(std::string, component*, uint16_t);

	void draw(sf::RenderWindow*);
};