#include "../blocks/spawner.h"


spawner::spawner(sf::Vector2f sp, sf::Vector2f mp, world* w, uint16_t sa, uint16_t ss, ItemType st) : 
	building(sp, mp, w, sa, ss)
{
	
	this->Spawn = st;
	
	this->type = "Spawner";

	this->timeToSpawn = 1.5;
}
spawner::spawner(sf::Vector2f sp, world* w, uint16_t sa, uint16_t ss, ItemType st) : 
	building(sp,w,sa,ss)
{
	
	this->Spawn = st;
	
	this->type = "Spawner";

	this->timeToSpawn = 1.5;
}
spawner::~spawner() {}//I dont know if i should delete anythin here?

void spawner::update(float dt) {

	// add the time since last frame to the time since the last spawning
	elapsedTime += dt;

	float EPSILON = std::numeric_limits<float>::epsilon();

	while (timeToSpawn - elapsedTime < EPSILON) { // while the elapsed time is less than the time required to spawn, spawn
		this->inv.add(Spawn, 1); // spawn
		elapsedTime -= timeToSpawn; // reset the elapsed time
		if (elapsedTime < 0) elapsedTime = 0; // if the elapsed time is less than 0, set it to 0
		// update labels
	}
}
