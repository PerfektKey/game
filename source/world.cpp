#include "../header/world.h"

#include "../header/building.h"


world::world(uint16_t w, uint16_t h, uint16_t ts, sf::Vector2f wd, sf::Vector2f* cam) 
{
	this->width  = w;	
	this->height = h;
	this->map = std::vector<std::vector<building*>> (w, std::vector<building*> (h, NULL));
	
	for (uint16_t x = 0; x < width; x++){
		tiles.push_back({});
		for (uint16_t y = 0; y < height; y++) {
			tiles[x].push_back(tile( cam));
		}
	}
	
	this->tileSize = ts;

	mpCameraPosition = cam;
	mWindowSize = wd;
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


//void world::setTile(sf::Texture*, sf::Vector2f);
//
void world::setTile(sf::Texture* t, uint16_t x, uint16_t y) {
	if (x >= width || y >= height) return;

	tiles[x][y].setTexture(t);
	tiles[x][y].setWorldPosition(sf::Vector2f(x*tileSize,y*tileSize));
}

void world::printInfo(sf::Vector2f pos) 
{

	if (pos.x >= width || pos.y >= height) return;
	if (map[pos.x][pos.y] == NULL) return;

	map[pos.x][pos.y]->printInfo();
}

void world::update(float dt, uint16_t frame) 
{
	for (auto& i : map)
	for (auto& b : i) {
		if (b == NULL) continue;
		 b->update(dt, frame);
	}
}

void world::draw(sf::RenderWindow* w)
{
	for (auto& i : tiles)
	for (auto& b : i)
		if (inScreen( b.getWorldPosition() )) b.draw(w);
	for (auto& i : map)
	for (auto& b : i)
		if (b != NULL && inScreen(b->getScreenPosition())) b->draw(w);
}

void world::cameraMoved(sf::Vector2f p) {
	for (auto& i : map)
	for (auto& b : i)
		if (b != NULL) b->setCameraOffset(p);
}

uint16_t world::getWidth() const {return this->width;}
uint16_t world::getHeight() const {return this->height;}
uint16_t world::getTileSize() const {return tileSize;}

sf::Vector2f world::screenToMap(sf::Vector2f sp) const {
	return sf::Vector2f( floor(sp.x/tileSize) , floor(sp.y/tileSize) );
}

bool world::inScreen(const sf::Vector2f& p) const {
	bool xBool = p.x+tileSize >= mpCameraPosition->x && p.x-tileSize <= mpCameraPosition->x+mWindowSize.x;
	bool yBool = p.y+tileSize >= mpCameraPosition->y && p.y-tileSize <= mpCameraPosition->y+mWindowSize.y;
	return xBool && yBool;
}
