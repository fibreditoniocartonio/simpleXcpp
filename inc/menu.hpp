#pragma once

#include <string>
#include <vector>
#include <fstream> 

#include <SFML/Graphics.hpp>

class GameEngine;

class Menu {
 public:
	int width, height, maxWidth, maxHeight, speed;
	bool isOpen=false, isClosing=false;

	virtual void Physics(GameEngine* game);
	virtual void Render(sf::RenderWindow* window);
	virtual	void Animation();
	
	//constructor and destructor
	Menu();
	virtual ~Menu();
};


class Alert : public Menu{
 public:
	int previousGameState, borderDim;
	void* previousMenu;
	sf::Text testo;
	sf::Color color1, color2;
	
	void Render(sf::RenderWindow* window) override;

	void Physics(GameEngine* game) override;

	//constructor
	Alert(GameEngine* game, int charSize, std::string stringa);
};
