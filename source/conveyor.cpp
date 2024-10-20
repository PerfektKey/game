#include "../blocks/conveyor.h"

#include "../header/world.h"

conveyor::conveyor(sf::Vector2f pos, world* w, uint16_t sa, uint16_t ss, float tps) :
	building(pos, w, sa, ss) { // access inventory has a size of 1
	mSpeed = 1/tps * ss; 
	mTimer = 0;

	std::cout << mSpeed << "\n";

	view = inventory(mSlotAmmount, 99);
	
	type = "conveyor";
}

void conveyor::draw(sf::RenderWindow* w) const {
	// just a placeholder for before the sprite is created
	// drawing two triangles pointing in the direction
	sf::CircleShape triangle1(10,3);
	triangle1.setPosition(screenPosition + sf::Vector2f(25,15));
	triangle1.setFillColor(sf::Color::Black);
	triangle1.rotate(90);
	w->draw(triangle1);
	
	sf::CircleShape triangle2(10,3);
	triangle2.setPosition(screenPosition + sf::Vector2f(45,15));
	triangle2.setFillColor(sf::Color::Black);
	triangle2.rotate(90);
	w->draw(triangle2);
}

/*
inventory* conveyor::getInventory() {
	view.setSlot(0, inv.getSlot(0));
	for (uint16_t i = 0; i < mSlotAmmount-1;i++)
		view.setSlot(i+1, mShiftInv.getSlot(i));
	return &view;
}
*/

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
	

	// do first index shift (shift from access to shift inventory)
/*
	if (inv.getSlot(0).type != ItemType::EMPTY) return;
	inv.setSlot(0, inv.getSlot(0));
	inv.setSlot(0, slot());
*/
}
slot conveyor::getOut() {
	slot ret = inv.getSlot(mSlotAmmount-2);
	inv.setSlot(mSlotAmmount-2, slot());
	return ret;
}

// only takes stuff: has to ask next inventory to take from itself
		
		// UPDATE DOESNT CHECK HOW MUCH IT TAKES!!!!

void conveyor::update(float dt) {
	// update only onces per frame
	// 	-> check if it has been updated this frame

	// only do it if the timer is up
	mTimer += dt;
	if (mTimer < mSpeed) return;
	
	while (mTimer >= mSpeed) {
		mTimer -= mSpeed;

		// get the next and previous blocks
		building* source = WORLD->get(mapPosition + sf::Vector2f(-1,0));
		building* target = WORLD->get(mapPosition + sf::Vector2f(1,0));

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
	}
}
