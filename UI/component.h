#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class component {
private:
	sf::Vector2f screenPosition;
	sf::Vector2f relativUIposition;
	bool show;
	

	
	sf::RectangleShape hitbox;
	sf::Vector2f hitboxSize;
	bool focusedByMouse;

	sf::Text label;
	sf::Font font;
	uint16_t characterSize;
	std::string text;
public:
	component();
	virtual ~component();

	virtual void draw(sf::RenderWindow*) const;
	virtual void action(sf::Event, sf::Vector2f);
	
	virtual void focusedMouse(sf::Vector2f);

	sf::Vector2f getPosition() const;
	void setPosition(sf::Vector2f);

	std::string getText() const;
	void setText(std::string);


};
