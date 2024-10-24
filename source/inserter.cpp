#include "../blocks/inserter.h"
#include "../header/world.h"

inserter::inserter(sf::Vector2f sp, world* w, uint16_t ts, uint16_t r , float sd): 
	building(sp, w, 1, ts) {
	this->speed = sd;
	this->timer = 0;
	this->transferSize = ts;

	setRotation(r);

	this->type = "Inserter";
}


void inserter::setRotation(uint16_t r) {
	if (r == 360) r = 0;
	mRotation = r;
	switch (r) {
		case 0:
			mSourceOffset = sf::Vector2f(0,1);
			mTargetOffset = sf::Vector2f(0,-1);
			break;
		case 90:
			mSourceOffset = sf::Vector2f(-1,0);
			mTargetOffset = sf::Vector2f(1,0);
			break;
		case 180:
			mSourceOffset = sf::Vector2f(0,-1);
			mTargetOffset = sf::Vector2f(0,1);
			break;
		case 270:
			mSourceOffset = sf::Vector2f(1,0);
			mTargetOffset = sf::Vector2f(-1,0);
			break;
		default:
			std::cout << "Invalid rotation of " << r << " in " << this << "\n";
			std::cout << "setting rotation to 0 " << "\n";
			setRotation(0);
			break;
	}
}


void inserter::update(float dt, uint16_t frame) {
	timer += dt;

	if (timer < speed) return;
	timer -= speed;
	
	building* source = WORLD->get(mapPosition + mSourceOffset );
	building* target = WORLD->get(mapPosition + mTargetOffset ); 
	
	if (source == NULL || target == NULL) return;

	inventory* sourceINV = source->getInventory();	
	
	inventory* targetINV = target->getInventory();
/*
	if (target->getType() != "conveyor") 
		targetINV = target->getInventory();
	else {
		conveyor* c = (conveyor*)target;
		targetINV = c->getAccessInv();
	}
*/
	if (sourceINV == NULL || targetINV == NULL) return;	


	ItemType ItemToTransfer = sourceINV->getLastItem();
	if (ItemToTransfer == ItemType::EMPTY) return;
	uint16_t transfered = sourceINV->remove(ItemToTransfer , transferSize);
	if (target->getType() != "conveyor") 
		targetINV->add(ItemToTransfer , transfered);
	else
		targetINV->add(ItemToTransfer, transfered, 0);
}

void inserter::draw(sf::RenderWindow* w) const {
	sf::RectangleShape rec;
	rec.setSize(sf::Vector2f(50,50));
	rec.setPosition(screenPosition);
	rec.setFillColor(sf::Color::Black);

	// dir is the target direction
	sf::RectangleShape dir;
	
	if (mRotation == 90 || mRotation == 270)
		dir.setSize(sf::Vector2f(5,50));
	else 
		dir.setSize(sf::Vector2f(50,5));

	dir.setFillColor(sf::Color::Red);

//	dir.setPosition(screenPosition + sf::Vector2f(-23*mTargetOffset.y,-23*mTargetOffset.x) );

	if (mRotation == 0)
		dir.setPosition(screenPosition + sf::Vector2f(0,0) );	
	else if (mRotation == 90)
		dir.setPosition(screenPosition + sf::Vector2f(45,0) );	
	else if (mRotation == 180)
		dir.setPosition(screenPosition + sf::Vector2f(0,45) );	
	else if (mRotation == 270)
		dir.setPosition(screenPosition + sf::Vector2f(0,0) );	
	
	w->draw(rec);
	w->draw(dir);
}


