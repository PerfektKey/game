#include <iostream>
#include <SFML/Graphics.hpp>

int main () {
	
	// creating window
	sf::RenderWindow window(sf::VideoMode(1000,800), "Bakteria Game");
	

	// Game loop
	while (window.isOpen()) {
		sf::Event event;
		
		// checking for 
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		
		// updating the frame
		window.clear(sf::Color(180,180,180));
		window.display();
	}
	
	return 0;
}
