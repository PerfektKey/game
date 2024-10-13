#include "../blocks/inserter.h"
#include "../header/world.h"

inserter::inserter(sf::Vector2f sp, world* w, float sd, uint16_t ts): 
	building(sp, w, 1, ts) {
	this->speed = sd;
	this->timer = 0;

	this->type = "Inserter";
}


void inserter::update(float dt) {
	building* source = WORLD->getBuilding(mapPosition - sf::Vector2f(1, 0));
	building* target = WORLD->getBuilding(mapPosition + sf::Vector2f(1, 0));
	
	//gg	
}
