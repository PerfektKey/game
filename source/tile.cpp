#include "../header/tile.h"

tile::tile() :
	tile(NULL){
}

tile::tile(sf::Vector2f* pCam) {
	pCameraPosition = pCam;
	pTexture = NULL;
}


void tile::draw(sf::RenderWindow* w) {
	if (pCameraPosition == NULL) std::cout << "camera pointer in tile " << this << " NULL" << "\n";
	mScreenPosition = mWorldPosition - *pCameraPosition; 
	mSprite.setPosition(mScreenPosition);

	w->draw(mSprite);
}
	
sf::Vector2f tile::getScreenPosition() const {return mScreenPosition;}
sf::Vector2f tile::getWorldPosition() const {return mWorldPosition;}

void tile::setWorldPosition(const sf::Vector2f& p) {mWorldPosition = p;}
void tile::setTexture(sf::Texture* t) {
	if (t == NULL) {
		std::cout << "tried setting texture of tile " << this << " as NULL\n";
		return;
	}
	pTexture = t;
	mSprite.setTexture(*t);
}
