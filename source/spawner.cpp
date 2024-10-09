#include "../blocks/spawner.h"


spawner::spawner(uint16_t x, uint16_t y, world* w, uint16_t sa, uint16_t ss, ItemType sp) : 
	building(x,y,w,sa,ss)
{
	
	this->Spawn = sp;
	
	this->type = "Spawner";

	this->timeToSpawn = 1.5;
	for (int i = 0; i < sa; i++) {
		label* c = new label(sf::Vector2f(x,y), "", sf::Color::White, 12, "assets/arial.ttf");
		std::string k = "label " + i; 
		this->info.add(k, c);
		c->setPosition(sf::Vector2f(x, y - i*12));
	}
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
		for (int i = 0; i < inv.getSlotAmmount(); i++) {
			ItemType t = inv.getItemAt(i).type;
			std::string k = "label " + i; // creating key
			if (t == ItemType::EMPTY) {// if item is empty(slot is emoty) then set the label text to nothing
				static_cast<label*>(info.getComponent(k))->setText("");
			} else { // else: set thet text to item name x Ammount
				std::string s = ItemData[t].name + " " + std::to_string(inv.getItemAt(i).ammount);
				static_cast<label*>(info.getComponent(k))->setText(s);
			}
		}
	}
}
