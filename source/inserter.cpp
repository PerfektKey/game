#include "../blocks/inserter.h"
#include "../header/world.h"

inserter::inserter(sf::Vector2f sp, world* w, std::string s, uint16_t ts, uint16_t r , float sd): 
	building(sp, w, s, 1, ts) {
	this->speed = sd;
	this->timer = 0;
	this->transferSize = ts;

	setRotation(r);

	this->type = "Inserter";
}


void inserter::setRotation(uint16_t r) {
	if (r == 360) r = 0;
	mRotation = r;
	mSprite.setRotation(r);
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

	inventory* sourceINV = NULL;
	if (source->getType() == "crafter") {
		crafter* c = static_cast<crafter*>(source);
		sourceINV = c->getOutput();
	} else
		sourceINV = source->getInventory();
	
	inventory* targetINV = target->getInventory();

	if (sourceINV == NULL || targetINV == NULL) return;	


	ItemType ItemToTransfer = sourceINV->getLastItem();

	if (ItemToTransfer == ItemType::EMPTY) return;
	uint16_t transfered = sourceINV->remove(ItemToTransfer , transferSize);
	if (target->getType() != "conveyor") 
		targetINV->add(ItemToTransfer , transfered);
	else
		targetINV->add(ItemToTransfer, transfered, 0);
}

