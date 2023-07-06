#pragma once

#include <string>
#include <vector>
#include <fstream> 

#include <SFML/Graphics.hpp>

class Entity;
class GameEngine;
class Player;
class Livello;
class AABB;

bool CollisionBetween(Entity* e1, Entity* e2);

int ResolveCollision(Entity* entity, Entity* obstacle);

void DoGamePhysics(GameEngine* game, Player* player, Livello* level, sf::RenderWindow* window);