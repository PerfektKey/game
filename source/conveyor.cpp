#include "../blocks/conveyor.h"

conveyor::conveyor(sf::Vector2f pos, world* w, uint16_t sa, uint16_t ss, float sp) :
	building(pos, w, sa, ss) {
	mSpeed = sp;	
	
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
void conveyor::update(float dt) {
	// get the next and previous 
}
