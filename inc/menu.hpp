#pragma once

#include <string>
#include <vector>
#include <fstream> 

#include <SFML/Graphics.hpp>

class GameEngine;
class Testo;

class Menu {
 public:
	int width, height, maxWidth, maxHeight, speed;
	bool isOpen=false, isClosing=false;
	virtual void Physics(GameEngine* game);
	virtual void Render(sf::RenderWindow* window);
	virtual	void Animation();	
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
	Alert(GameEngine* game, int charSize, std::string stringa);
};


class MainMenu : public Menu{   //gamestate 2
 public:
	int previousGameState, index, maxIndex;
	bool tastoGiaSchiacciato=true, exitGame=false;
	sf::Text testo;
	std::vector<Testo*> textClick;
    sf::Texture titleScreenImg;
    sf::Sprite titleScreenSprite;
	std::string language;
	void* previousMenu;
	GameEngine* game;
	void InitializeClickableText();
	void CleanClickableText();
	void CloseMenu();
	void Render(sf::RenderWindow* window) override;
	void Physics(GameEngine* game) override;
	MainMenu(GameEngine* game);
};


class SettingsMenu : public Menu{   //gamestate 3
 public:
	int previousGameState, borderDim, index, langIndex, langMaxIndex;
	bool tastoGiaSchiacciato=true, listenNewKey;
	sf::Text testo;
	sf::Color color1, color2;
	std::vector<Testo*> textClick;
	std::string language;
	void* previousMenu;
	GameEngine* game;
	int state; //0: main setting menu, 1:keyboard settings, 2:gamepad settings
	int maxIndex [3]; //maxIndex [state]
	void InitializeClickableText();
	void CleanClickableText();
	void CloseMenu();	
	void Render(sf::RenderWindow* window) override;
	void Physics(GameEngine* game) override;
	SettingsMenu(GameEngine* game);
};
