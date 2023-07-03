#pragma once

#include <string>
#include <vector>
#include <fstream> 

#include <SFML/Graphics.hpp>

class Player;
class Level;

class Entity {
 public:
 	bool isActive = true;
	int x, y, width, height;
	std::string id;
	virtual void Physics(Player* player);
	virtual void Render(sf::RenderWindow* window);
	virtual ~Entity();
	Entity ();
 	Entity (int x, int y, int width, int height);
};

class Blocco : public Entity{
 public:
	sf::RectangleShape shape;
	sf::Color color;
	void CreateHitbox();
	void Render(sf::RenderWindow* window) override;
};
