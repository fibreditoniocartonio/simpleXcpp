#pragma once

#include <string>
#include <vector>
#include <fstream> 

#include <SFML/Graphics.hpp>

class Entity;
class Livello;
class GameEngine;

int CollisionBetween(Entity* e1, Entity* e2);

class Player {
 public:
	int x=0, y=0;
	float xv=0, yv=0; //momentum
	int width=20, height=24;
	float speed=0.5;
	float jumpHeight=10;
	bool giaSaltato=false;
	sf::RectangleShape shape;
	sf::Text text;
	const int charSize=8;

	Player(GameEngine* game);

	virtual void Physics(GameEngine* game, Livello* level);

	virtual void Render(sf::RenderWindow* window);
};
