
#include <SFML/Graphics.hpp>
// UI
#include "UserInterface/container.h"
#include "UserInterface/component.h"
#include "UserInterface/label.h"
#include "UserInterface/button.h"

void testFunc(component*);

int main() {
	// test UI
	container Cont;
	
	
	component* c1 = new component(sf::Vector2f(200,300), sf::Vector2f(100,50), &Cont, sf::Color::Red);
	component* c2 = new component(sf::Vector2f(200,320), sf::Vector2f(100,50), &Cont, sf::Color::White);
	component* c3 = new component(sf::Vector2f(270,290), sf::Vector2f(100,50), &Cont, sf::Color::Blue);
	component* l1 = new label(sf::Vector2f(50,50), &Cont, "assets/arial.ttf",24 , sf::Color::White, "Test Label");
	component* l2 = new label(sf::Vector2f(50,80), &Cont, "assets/arial.ttf",50 , sf::Color::Red, "Test Label tow");

	component* b1 = new button(sf::Vector2f(400,400), sf::Vector2f(100,100), &Cont, sf::Color::Black);
	component* b2 = new button(sf::Vector2f(600,400), sf::Vector2f(100,100), &Cont, sf::Color::Black, testFunc);

	Cont.add("Square 1", c1, 1);
	Cont.add("Square 2", c2, 0);
	Cont.add("Square 3", c3, 2);
	Cont.add("Label 1", l1, 0);
	Cont.add("Label 2", l2, 0);
	
	Cont.add("Button 1", b1, 0);
	Cont.add("Button 2", b2, 0);


	sf::RenderWindow w(sf::VideoMode(1000,800), "UI Test");

	while (w.isOpen()) {

		sf::Vector2i m = sf::Mouse::getPosition(w);
		sf::Vector2f mousePosition = sf::Vector2f(m.x , m.y);
	
		sf::Event e;
		while (w.pollEvent(e)) {
			if (e.type == sf::Event::Closed)
				w.close();
			Cont.action(e, mousePosition);
		
			button* b = static_cast<button*>(Cont.get("Button 1", 0));
			if (b != NULL) {
				if (b->isPressed())
					std::cout << "Button 1 pressed through isPressed()\n";
			} else 
				std::cout << "something went wrong\n";
		}


		w.clear(sf::Color(180,180,180,255));
		
		Cont.draw(&w);
		
		w.display();
	}

	return EXIT_SUCCESS;
}


void testFunc(component* c) {
	std::cout << "Function pointer function execution\n";
}
