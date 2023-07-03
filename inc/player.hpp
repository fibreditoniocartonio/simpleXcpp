#pragma once

#include <string>
#include <vector>
#include <fstream> 

#include <SFML/Graphics.hpp>

#include "entity.hpp"

class Livello;
class GameEngine;

class Player : public Entity{
 public:
	float speed=0.5;
	float jumpHeight=10;
	bool giaSaltato=false;
	
	sf::RectangleShape shape;
	sf::Text text;
	const int charSize=8;

	Player(GameEngine* game);

	void Physics(GameEngine* game, Livello* level);

	void Render(sf::RenderWindow* window) override;
};
