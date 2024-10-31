
#include "../header/worldGeneration.h"


void worldGeneration::fill(world* w) {
	sf::Texture* t = new sf::Texture();
	if (!t->loadFromFile("assets/env/stone01.png")) {
	}
	
	uint16_t wi = w->getWidth();
	uint16_t h = w->getHeight();
	for (uint16_t x = 0; x < wi; x++)
	for (uint16_t y = 0; y < h; y++)
		w->setTile(t, x,y);
}
