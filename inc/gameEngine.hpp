#pragma once

#include <string>
#include <vector>
#include <fstream> 

#include <SFML/Graphics.hpp>
#include "gameVersion.hpp"

class TextEngine;
class Livello;
class Player;

class JoystickHandler {
 public:
    int keySettings [11][2] = {{68,-1},{67,-1},{34,-1},{35,-1},{2,-1},{1,-1},{3,-1},{9,-1},{8,-1},{4,-1},{5,-1}};
    int axisDeadZone = 30;
    int GetAxisKey(sf::Event* evento);
};

class GameEngine {
 public:
	bool debugMode = false;
	int listenNewKey = -1;
	int newKeyIndex [2];
	const int frameLimit = 60;
	const int windowWidth=360, windowHeight=270;
	sf::RenderWindow* window;
	sf::Font font;
    sf::Joystick joystick;
	JoystickHandler joystickHandler;
	TextEngine* textEngine;
	Livello* level;
	Player* player;
	std::string language;
	
	int gamestate = 2;
	void* currentMenu = NULL;
	//stato -1: in partita
	//stato 1: c'e' un alert aperto - var alertAperto=false; 
	//stato 2: menu di pausa - var menuDiPausa=false; 
	//stato 3: menu opzioni - var nelMenuOpzioni=false; 
	//stato 4: opzioni nelle stage selection - var nelleOpzioniStageSelect=false; 
	//stato 5: nel menu carica partita - var nelMenuCaricaPartita=false; 
	//stato 6: menu Mappa - map menu
	//stato 1000: Level Editor
	
	void ChangeGameState(int newGameState, void* newMenu);

	//input key settings
	int ultimoTastoLetto;
	bool keys[11]={
		false, //0 = su
		false, //1 = giu
		false, //2 = destra
		false, //3 = sinistra
		false, //4 = jump 
		false, //5 = dash
		false, //6 = sparo
		false, //7 = start
		false, //8 = map 
		false, //9 = l
		false  //10= r
	};
	sf::Keyboard::Key keySettings[11][2]={
 		{sf::Keyboard::Up,	sf::Keyboard::Numpad8},
	 	{sf::Keyboard::Down,	sf::Keyboard::Numpad5},
	 	{sf::Keyboard::Right,	sf::Keyboard::Numpad6},
	 	{sf::Keyboard::Left,	sf::Keyboard::Numpad4},
	 	{sf::Keyboard::Z,	sf::Keyboard::Space},
	 	{sf::Keyboard::X,	sf::Keyboard::LShift},
	 	{sf::Keyboard::A,	sf::Keyboard::LControl},
	 	{sf::Keyboard::Enter,	sf::Keyboard::F1},
	 	{sf::Keyboard::RShift,	sf::Keyboard::M},
	 	{sf::Keyboard::D,	sf::Keyboard::L},
	 	{sf::Keyboard::C,	sf::Keyboard::R}
	};
	
	void UpdateKeys(sf::Keyboard::Key keyInput, bool isPressed);    
	void UpdateKeysJoystick(int keyInput, bool isPressed);
	void BindNewKeyKB(sf::Keyboard::Key keyInput);
	void BindNewKeyJS(int keyInput);
	void SetLanguage(std::string language);
	void UpdateTextLanguage();

	//costructor
	GameEngine();
};
