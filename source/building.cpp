#include "../header/building.h"

#include "../header/world.h"

building::building(sf::Vector2f sp, sf::Vector2f mp, world* w, uint16_t sa, uint16_t ss) {
	this->screenPosition = sp;
	this->WORLD = w;
	this->mapPosition = mp;

	this->inv = inventory(sa,ss);

	this->type = "Normal Tile";
	
	mFrame = 0;
}
building::building(sf::Vector2f sp, world* w, uint16_t sa, uint16_t ss) {
	this->screenPosition = sp;
	this->WORLD = w;
	this->mapPosition = WORLD->screenToMap(sp);

	this->inv = inventory(sa,ss);

	this->type = "Normal Tile";

	mSize = sf::Vector2f(50,50);

	mFrame = 0;
}
building::~building() {}//I dont know if I should write anything in here

void building::update(float dt, uint16_t frame)
{

}
inventory* building::getInventory() {
	return &inv;
}

void building::draw(sf::RenderWindow* w) const {
	sf::RectangleShape shape;
	shape.setFillColor(sf::Color::Black);
	shape.setPosition(screenPosition);
	shape.setSize(sf::Vector2f(50,50));
	w->draw(shape);
}

void building::printInfo() const
{
	std::cout << "#############\n";
	std::cout << "Building [" << type << "]\n";
	std::cout << "at Map x: " << mapPosition.x << " Map y: " << mapPosition.y << "\n";
	std::cout << "at Screen x: " << screenPosition.x << " Screen y: " << screenPosition.y << "\n";

	std::cout << "Inventory: \n";
	inv.print();

	std::cout << "#############\n";
}

sf::Vector2f building::getSize() const {return mSize;}
sf::Vector2f building::getPosition() const {return screenPosition;}
std::string building::getType() const {return type;}

void building::setRotation(uint16_t rot) {
	// not much happening here for most buildings
	mRotation = rot;
}
uint16_t building::getRotation() const {return mRotation;}

container* building::createUI() const {
	return createInventoryUI(&inv);
}

void hideInterface(component* c) {
	c->getParent()->show(false);
}
container* building::createInventoryUI(const inventory* invP) const {

	sf::Vector2f mGlobalPosition = screenPosition;
	mGlobalPosition.x += mSize.x;

	container* mCont = new container(NULL);

	component* backGround = new component(mGlobalPosition, sf::Vector2f(400,200), mCont, sf::Color(0,0,150,130));
	mCont->add("BG", backGround, 3);
	
	component* closeButton = new button(sf::Vector2f(0,0), sf::Vector2f(50,50), mCont, sf::Color(180, 10,10), hideInterface);
	closeButton->setRelativAnchor(mGlobalPosition);
	closeButton->setRelativPosition(sf::Vector2f(10, 10));
	mCont->add("close", closeButton, 0);

	component* name = new label(sf::Vector2f(0,0), mCont, "assets/arial.ttf", 24, sf::Color::Black, getType());
	name->setRelativAnchor(mGlobalPosition);
	name->setRelativPosition(sf::Vector2f(70, 10));
	mCont->add("name", name, 0);

	// add labels that are inventory
	// is 4x8 with a size of 12
	// but the inventory may not be 4x8
	// calculate rows and collums
//	const uint16_t ROWS = 8;
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

	return mCont;
}

void building::updateUI(container* c) {
	updateInventoryUI(c, &inv);
}
void building::updateInventoryUI(container* mCont, const inventory* invP) const {
	if (mCont == NULL) return;

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
}

