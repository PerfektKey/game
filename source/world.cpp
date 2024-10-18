#include "../header/world.h"

#include "../header/building.h"


world::world(uint16_t w, uint16_t h, uint16_t ts) 
{
	this->width  = w;	
	this->height = h;
	this->map = std::vector<std::vector<building*>>(w, std::vector<building*>(h, NULL));
	
	this->tileSize = ts;
}

building* world::get(uint16_t wx, uint16_t hy) {
	if (wx >= width || hy >= height) return NULL;

	return map.at(wx).at(hy);
}
building* world::get(sf::Vector2f p) {
	if (p.x >= width || p.y >= height) return NULL;

	return map.at(p.x).at(p.y);
}
building* world::set(uint16_t wx, uint16_t hy, building* b)
{
	if (wx >= width || hy >= height) return b;
	if (map[wx][hy] != NULL) return b;
	map[wx][hy] = b;
	return NULL;
}
building* world::set(sf::Vector2f pos, building* b) {
	if (pos.x >= width || pos.y >= height) return b;
	if (map[pos.x][pos.y] != NULL) return b;
	map[pos.x][pos.y] = b;
	return NULL;
}	
void world::printInfo(sf::Vector2f pos) 
{

	if (pos.x >= width || pos.y >= height) return;
	if (map[pos.x][pos.y] == NULL) return;

	map[pos.x][pos.y]->printInfo();
}

void world::update(float dt) 
{
	for (auto& i : map)
	for (auto& b : i) {
		if (b == NULL) continue;
		 b->update(dt);
	}
}

void world::draw(sf::RenderWindow* w) const
{
	for (auto& i : map)
	for (auto& b : i)
		if (b != NULL) b->draw(w);
}

uint16_t world::getWidth() const {return this->width;}
uint16_t world::getHeight() const {return this->height;}


sf::Vector2f world::screenToMap(sf::Vector2f sp) const {
	return sf::Vector2f( floor(sp.x/tileSize) , floor(sp.y/tileSize) );
}
