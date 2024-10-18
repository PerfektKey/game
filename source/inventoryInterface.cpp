#include "../UserInterface/inventoryInterface.h"

void hideInterface(component* c) {
	c->getParent()->show(false);
}

inventoryInterface::inventoryInterface() {
	mRef = NULL;
	mCont = NULL;
}

void inventoryInterface::update() {

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
	for (int y = 0;y < 8; y++)
		for (int x = 0; x < 4; x++) {
			component* invSlot = new label(sf::Vector2f(0,0), mCont, "assets/arial.ttf", 12, sf::Color::Black, "ABx100"); 
			invSlot->setRelativAnchor(mGlobalPosition);
			invSlot->setRelativPosition(sf::Vector2f(10+72*x, 60+y*16));
			std::string slotName = "Slot " + std::to_string(x) + "x" + std::to_string(y);
			mCont->add(slotName, invSlot, 0);
		}

} 

void inventoryInterface::setRef(building* b) {
	if (b == mRef){
		mCont->show(true); 
		return;
	}
	mRef = b;
	if (mCont != NULL) delete mCont;

	mCont = new container();
	mCont->show(true);

	mGlobalPosition = mRef->getPosition();
	mGlobalPosition.x += mRef->getSize().x;
	
	update();
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
