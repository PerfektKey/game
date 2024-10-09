#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class component {
protected:
	sf::Vector2f screenPosition;
	sf::Vector2f relativUIposition;
	bool show;
	
	sf::RectangleShape hitbox;
	sf::Vector2f hitboxSize;
	bool focusedByMouse;

public:
	component(sf::Vector2f, sf::Vector2f);
	virtual ~component();

	virtual void draw(sf::RenderWindow*) const;
	virtual void action(sf::Event, sf::Vector2f);
	
	virtual void focusedMouse(sf::Vector2f);

	sf::Vector2f getPosition() const;
	virtual void setPosition(sf::Vector2f);

	void setVisibility(bool);
	bool getVisibility() const;

};
