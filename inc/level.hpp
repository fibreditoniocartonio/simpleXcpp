#pragma once

#include <string>
#include <vector>
#include <fstream> 

#include <SFML/Graphics.hpp>

class GameEngine;
class Entity;
class Player; 

class Livello {
 public:
	GameEngine* game;
    Player* player;
	sf::Vector2f playerStartingPos;
	std::vector<Entity*> entity;
    std::string currentLevelFile = "";
	int contaEntity=0;
	int maxWidth, maxHeight;
	float gravity, friction;

	//constructor
	Livello(GameEngine* game, Player* player);

	//Decoder
	void CleanLevel();
	void LoadLevel(std::string filePath);
	void SetProprieties(std::string* tempString);
	std::string GetProprieties();
	void SetPlayerInitialPosition(std::string* tempString);
	std::string GetPlayerInitialPosition();
	void DecodeObj(std::string tempString[32]);
	std::string GenerateLevelString();
};
