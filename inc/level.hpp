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
	std::vector<Entity*> entity;
    std::string currentLevelFile = "";
	int contaEntity=0;
	int maxWidth, maxHeight;
	float gravity, friction;

	//constructor
	Livello(GameEngine* game, Player* player);

	//Decoder
	void LoadLevel(std::string filePath);
    
	void CleanLevel();

	void DecodeObj(std::string tempString[32]);
};
