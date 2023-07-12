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


class Alert : public Menu{  //gamestate 1
 public:
	int previousGameState, borderDim, timer;
	sf::Text testo;
	sf::Color color1, color2;
	void* previousMenu;
	void Render(sf::RenderWindow* window) override;
	void Physics(GameEngine* game) override;
	//constructor
	Alert(GameEngine* game, int charSize, std::string stringa);
};


class MainMenu : public Menu{   //gamestate 2
 public:
	int previousGameState, index, maxIndex;
	bool tastoGiaSchiacciato=true, exitGame=false;
	sf::Text testo;
    sf::Texture titleScreenImg;
    sf::Sprite titleScreenSprite;
	void* previousMenu;
	GameEngine* game;
	void Render(sf::RenderWindow* window) override;
	void Physics(GameEngine* game) override;
	//constructor
	MainMenu(GameEngine* game);
};


class SettingsMenu : public Menu{   //gamestate 3
 public:
	int previousGameState, borderDim, index, maxIndex;
	bool tastoGiaSchiacciato=true, listenNewKey;
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
