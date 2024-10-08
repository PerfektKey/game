#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class component {
private:
	sf::Vector2f position;
	bool show;
	std::string text;
public:
	component();
	virtual ~component();

	virtual void draw(sf::RenderWindow*) const;
	virtual void action();
	
	sf::Vector2f getPosition() const;
	void setPosition(sf::Vector2f);

	std::string getText() const;
	void setText(std::string);


};
