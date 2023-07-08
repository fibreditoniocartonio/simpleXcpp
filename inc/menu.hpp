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
	sf::Text testo;
	sf::Color color1, color2;
	void* previousMenu;
	
	void Render(sf::RenderWindow* window) override;

	void Physics(GameEngine* game) override;

	//constructor
	Alert(GameEngine* game, int charSize, std::string stringa);
};


class SettingsMenu : public Menu{
 public:
	int previousGameState, borderDim, index, maxIndex;
	bool tastoGiaSchiacciato, listenNewKey;
	sf::Text testo;
	sf::Color color1, color2;
	void* previousMenu;
	GameEngine* game;
	int state; //0: main setting menu, 1:keyboard settings, 2:gamepad settings
	
	void Render(sf::RenderWindow* window) override;

	void Physics(GameEngine* game) override;

	//constructor
	SettingsMenu(GameEngine* game);
};
