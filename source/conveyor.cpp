#include "../blocks/conveyor.h"

#include "../header/world.h"

conveyor::conveyor(sf::Vector2f pos, world* w, uint16_t sa, uint16_t ss, uint16_t r , float tps) :
	building(pos, w, sa, ss) { // access inventory has a size of 1
	mSpeed = 1/tps * ss; 
	mTimer = 0;
	
	setRotation(r);

	type = "conveyor";
}

void conveyor::draw(sf::RenderWindow* w) const {
	// just a placeholder for before the sprite is created
	// drawing two triangles pointing in the direction
	sf::CircleShape triangle1(10,3);
	triangle1.setPosition(screenPosition + sf::Vector2f(25,15));
	triangle1.setOrigin(5,5);
	triangle1.setFillColor(sf::Color::Black);
	triangle1.rotate(mRotation);
	w->draw(triangle1);
	
	sf::CircleShape triangle2(10,3);
	triangle2.setPosition(screenPosition + sf::Vector2f(45,15));
	triangle2.setOrigin(5,5);
	triangle2.setFillColor(sf::Color::Black);
	triangle2.rotate(mRotation);
	w->draw(triangle2);
}

void conveyor::shiftInv() {

	// have to shift the inventory i.e.:
	// [Copper][Empty][Emtpy][Copper]
	// ->
	// [Empty][Copper][Empty][Empty]
	//
	// for loop from last slot to first
	// if slot i is empty replace with slot i-1
	for (uint16_t i = inv.getSlotAmmount()-1; i > 0; i--) {
		if (inv.getSlot(i).type != ItemType::EMPTY) continue;
		inv.setSlot(i, inv.getSlot(i-1));
		inv.setSlot(i-1, slot());
	}
}
slot conveyor::getOut() {
	slot ret = inv.getSlot(mSlotAmmount-2);
	inv.setSlot(mSlotAmmount-2, slot());
	return ret;
}

// only takes stuff: has to ask next inventory to take from itself

void conveyor::setRotation(uint16_t r) {
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

		// UPDATE DOESNT CHECK HOW MUCH IT TAKES!!!!

void conveyor::update(float dt, uint16_t frame) {
	// update only onces per frame
	// 	-> check if it has been updated this frame

	if (mFrame == frame) return; // it has already been updated this frame
	mFrame = frame;

	// only do it if the timer is up
	mTimer += dt;
	if (mTimer < mSpeed) return;
	
	while (mTimer >= mSpeed) {
		mTimer -= mSpeed;

		// get the next and previous blocks
		building* source = WORLD->get(mapPosition + mSourceOffset);
		building* target = WORLD->get(mapPosition + mTargetOffset);


		// conv1 conv2 conv3
		// conv1 source == NULL
		// 	conv1 shifts
		// conv2 
		// 	source == conv1

		// first update source
		shiftInv();
		if (source != NULL && source->getType() == "conveyor") {
			source->update(dt, frame);
		}
		// put item in target if conveyor
		
		if (target != NULL && target->getType() == "conveyor" && target->getInventory()->getSlot(0).type == ItemType::EMPTY) {
			target->update(dt, frame);
			inventory* tInv = target->getInventory();
			slot si = inv.remove( (inv.getSlotAmmount()-1) , tInv->getSlotSize());
			tInv->add(si.type, si.ammount, 0);
		}
		return;
/*
		// first update the target
		if (target != NULL && target->getType() == "conveyor") {
			target->update(dt); // will cause this to be updated multible times a frame <<-- fix this
		}

		// then shift my own shiftInventory
		shiftInv();

		// then take from the source(if it is a conveyor) and put it into my inventory
		if (source != NULL && source->getType() == "conveyor" && inv.getSlot(0).type == ItemType::EMPTY) {
			uint16_t sourceLast = source->getInventory()->getSlotAmmount() - 1; // last index of slots, last of the slots 
			slot si = source->getInventory()->remove(sourceLast, inv.getSlotSize());
			inv.add(si.type, si.ammount, 0);
	//		conveyor* conv = (conveyor*)source;
	//		slot s = conv->getOut();
	//		inv.setSlot(0, s);
			
		}
*/
	}
}
