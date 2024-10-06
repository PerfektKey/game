#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include "building.h"

int main () {
	
	// creating window
	sf::RenderWindow window(sf::VideoMode(1000,800), "Bakteria Game");
	
	//standart tile
	sf::RectangleShape tile;
	tile.setSize(sf::Vector2f(50,50));
	tile.setOutlineColor(sf::Color::Black);
	tile.setOutlineThickness(5);

	sf::Vector2i mouseP = sf::Mouse::getPosition();

	std::vector<building> pl;

	// Game loop
	while (window.isOpen()) {
		sf::Event event;
	
	
		mouseP = sf::Mouse::getPosition(window);
		sf::Vector2f tileP = sf::Vector2f( std::floor(mouseP.x/50)*50 , std::floor(mouseP.y/50)*50 ); 
		tile.setPosition(tileP);


		// checking for 
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::O)) {
				building b(tileP.x, tileP.y);	// set a tile
				pl.push_back(b);
				std::cout << "Placed new tile at: " << tileP.x << ", " << tileP.y << "\n";
			}
		}

		
		// updating the frame
		window.clear(sf::Color(180,180,180));
		//window.draw(tile);
		for (auto& i : pl)
			i.draw(&window);
		window.display();
	}
	
	return 0;
}
