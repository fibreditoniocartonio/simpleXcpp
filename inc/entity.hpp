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
	float x, y;
	int width, height;
	float xv=0, yv=0; //momentum
	std::string id;
	virtual void Physics(Player* player);
	virtual void Render(sf::RenderWindow* window);
	virtual std::string SaveToFile();
	virtual ~Entity();
	Entity ();
 	Entity (float x, float y, int width, int height);
};

class AABB : public Entity{
 public:
    AABB(Entity* e1);
};

class Blocco : public Entity{
 public:
	sf::RectangleShape shape;
	sf::Color color;
	int skipOnSave;
	void Render(sf::RenderWindow* window) override;
	int Initialize(std::vector<Entity*> *entity);
	int Initialize(std::vector<Entity*> *entity, std::string* tempString);
	void UpdateRenderHitbox();
	std::string SaveToFile() override;
};

class Slope : public Entity{
 public:
	float x1, y1, x2, y2, coefficienteAngolare, intersezioneQ;
	int slopeType;
	sf::ConvexShape shape;
	sf::Color color;
	float CalculateIntersection(Entity* entity);
	void Render(sf::RenderWindow* window) override;
	int Initialize(std::vector<Entity*> *entity, std::string* tempString);
	std::string SaveToFile() override;
};
