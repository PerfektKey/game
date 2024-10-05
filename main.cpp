#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>

int main () {
	
	// creating window
	sf::RenderWindow window(sf::VideoMode(1000,800), "Bakteria Game");
	
	//standart tile
	sf::RectangleShape tile;
	tile.setSize(sf::Vector2f(50,50));
	tile.setOutlineColor(sf::Color::Black);
	tile.setOutlineThickness(5);

	sf::Vector2i mouseP = sf::Mouse::getPosition();

	// Game loop
	while (window.isOpen()) {
		sf::Event event;
		
		// checking for 
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		mouseP = sf::Mouse::getPosition(window);
		sf::Vector2f tileP = sf::Vector2f( std::floor(mouseP.x/50)*50 , std::floor(mouseP.y/50)*50 ); 
		tile.setPosition(tileP);

		
		// updating the frame
		window.clear(sf::Color(180,180,180));
		window.draw(tile);
		window.display();
	}
	
	return 0;
}
