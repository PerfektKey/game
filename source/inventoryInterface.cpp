#include "../UserInterface/inventoryInterface.h"

/*
void hideInterface(component* c) {
	c->getParent()->show(false);
}
*/
inventoryInterface::inventoryInterface() {
	mRef = NULL;
	mCont = NULL;
}
/*
void inventoryInterface::createUI() {

	component* backGround = new component(mGlobalPosition, sf::Vector2f(400,200), mCont, sf::Color(0,0,150,130));
	mCont->add("BG", backGround, 3);
	
	component* closeButton = new button(sf::Vector2f(0,0), sf::Vector2f(50,50), mCont, sf::Color(180, 10,10), hideInterface);
	closeButton->setRelativAnchor(mGlobalPosition);
	closeButton->setRelativPosition(sf::Vector2f(10, 10));
	mCont->add("close", closeButton, 0);

	component* name = new label(sf::Vector2f(0,0), mCont, "assets/arial.ttf", 24, sf::Color::Black, mRef->getType());
	name->setRelativAnchor(mGlobalPosition);
	name->setRelativPosition(sf::Vector2f(70, 10));
	mCont->add("name", name, 0);

	// add labels that are inventory
	// is 4x8 with a size of 12
	// but the inventory may not be 4x8
	// calculate rows and collums
	inventory* invP = mRef->getInventory();
	const uint16_t ROWS = 8;
	const uint16_t COLLUMS = 5; // may be useless
	uint16_t slots = invP->getSlotAmmount();
	uint16_t rows = floor(slots/COLLUMS); // ammount of full rows
	uint16_t collums = slots % COLLUMS; // ammount of leftover collums
	
	// add full rows
	for (int r = 0;r < rows; r++)
		for (int c = 0; c < COLLUMS;c++) {
			// convert rows, collums to index
			// if row = 1, collum 3 then index = 1*5+3
			const slot& currSlot = invP->getSlot(r*COLLUMS+c);
			std::string info = ItemData[currSlot.type].abbreviation + "x" + std::to_string(currSlot.ammount);
			component* invSlot = new label(sf::Vector2f(0,0), mCont, "assets/arial.ttf", 12, sf::Color::Black, info); 
			invSlot->setRelativAnchor(mGlobalPosition);
			invSlot->setRelativPosition(sf::Vector2f(10+72*c, 60+r*16));
			std::string slotName = "Slot " + std::to_string(c) + "x" + std::to_string(r);
			mCont->add(slotName, invSlot, 0);
		}
	// add leftover collums
	for (int c = 0;c < collums;c++) {
		const slot& currSlot = invP->getSlot(rows*COLLUMS+c);
		std::string info = ItemData[currSlot.type].abbreviation + "x" + std::to_string(currSlot.ammount);
		component* invSlot = new label(sf::Vector2f(0,0), mCont, "assets/arial.ttf", 12, sf::Color::Black, info); 
		invSlot->setRelativAnchor(mGlobalPosition);
		invSlot->setRelativPosition(sf::Vector2f(10+72*c, 60+rows*16));
		std::string slotName = "Slot " + std::to_string(c) + "x" + std::to_string(rows);
		mCont->add(slotName, invSlot, 0);
	}
}
*/

void inventoryInterface::setRef(building* b) {
	if (b == mRef){
		mCont->show(true); 
		return;
	}
	mRef = b;
	if (mCont != NULL) delete mCont;

	mCont = mRef->createUI();

	return;

	mCont = new container();
	mCont->show(true);

	mGlobalPosition = mRef->getPosition();
	mGlobalPosition.x += mRef->getSize().x;
	
//	createUI();
}

void inventoryInterface::update() {
	if (mRef == NULL) return;
	
	mRef->updateUI(mCont);
	return;
	/* 
	inventory* invP = mRef->getInventory();
	const uint16_t ROWS = 8;
	const uint16_t COLLUMS = 5; // may be useless
	uint16_t slots = invP->getSlotAmmount();
	uint16_t rows = floor(slots/COLLUMS); // ammount of full rows
	uint16_t collums = slots % COLLUMS; // ammount of leftover collums
	for (int r = 0;r < rows; r++)
		for (int c = 0; c < COLLUMS;c++) {
			const slot& currSlot = invP->getSlot(r*COLLUMS+c);
			std::string info = ItemData[currSlot.type].abbreviation + "x" + std::to_string(currSlot.ammount);
			std::string slotName = "Slot " + std::to_string(c) + "x" + std::to_string(r);
			component* comp = mCont->get(slotName, 0);
			label* l = static_cast<label*>(comp);
			l->setContent(info);	
		}	
	for (int c = 0;c < collums;c++) {
		const slot& currSlot = invP->getSlot(rows*COLLUMS+c);
		std::string info = ItemData[currSlot.type].abbreviation + "x" + std::to_string(currSlot.ammount);
		std::string slotName = "Slot " + std::to_string(c) + "x" + std::to_string(rows);
		component* comp = mCont->get(slotName, 0);
		label* l = static_cast<label*>(comp);
		l->setContent(info);
	}
*/	
}

void inventoryInterface::draw(sf::RenderWindow* w) {
	if (mCont != NULL) mCont->draw(w);
}
void inventoryInterface::action(sf::Event e, sf::Vector2f v) {
	if (mCont != NULL) mCont->action(e, v);
}
void inventoryInterface::show(bool b) {
	//if (mCont != NULL) mCont->show(b);
}
