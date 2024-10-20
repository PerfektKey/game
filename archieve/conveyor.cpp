#include "../blocks/conveyor.h"

#include "../header/world.h"

conveyor::conveyor(sf::Vector2f pos, world* w, uint16_t sa, uint16_t ss, float sp) :
	building(pos, w, 1, ss) { // access inventory has a size of 1
	mSpeed = sp;
	mTimer = 0;

	mShiftInv = inventory(sa-1, ss);
	mSlotAmmount = sa;
	
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
	for (uint16_t i = mSlotAmmount-2; i > 0; i--) {
		if (mShiftInv.getSlot(i).type != ItemType::EMPTY) continue;
		mShiftInv.setSlot(i, mShiftInv.getSlot(i-1));
		mShiftInv.setSlot(i-1, slot());
	}
	
	// do first index shift (shift from access to shift inventory)
	if (mShiftInv.getSlot(0).type != ItemType::EMPTY) return;
	mShiftInv.setSlot(0, inv.getSlot(0));
	inv.setSlot(0, slot());
}
slot conveyor::getOut() {
	slot ret = mShiftInv.getSlot(mSlotAmmount-2);
	mShiftInv.setSlot(mSlotAmmount-2, slot());
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
	mTimer -= mSpeed;

	// 	shifting:
	//		[conv1][conv2][conv3]
	//		conv1 has to ask conv2 to take(update)
	//		conv2 has to ask conv3 to take(update)
	//		conv3 cant ask next to take(update) goes backward

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
		conveyor* conv = (conveyor*)source;
		slot s = conv->getOut();
		inv.setSlot(0, s);
		
	}
}
