#include "../blocks/spawner.h"


spawner::spawner(uint16_t x, uint16_t y, world* w, uint16_t sa, uint16_t ss, ItemType sp) : 
	building(x,y,w,sa,ss)
{
	
	this->Spawn = sp;
	
	this->type = "Spawner";

	this->timeToSpawn = 1.5;

	label* c = new label(sf::Vector2f(x,y), "Hello", sf::Color::White, 24, "assets/arial.ttf");
	this->info.add(c);
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
	}
}
