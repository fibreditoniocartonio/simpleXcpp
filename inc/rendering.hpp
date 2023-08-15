#pragma once

#include <string>
#include <vector>
#include <fstream> 

#include <SFML/Graphics.hpp>

class GameEngine;
class Player;
class Livello;

sf::View calcViewWhenResized(const sf::Vector2u &windowsize, const sf::Vector2u &designedsize);

sf::View calcViewOnPlayerMovement(sf::View view, sf::Vector2f camera, Livello* level, int windowWidth, int windowHeight);

void RenderGameScreen(GameEngine* game, Player* player, Livello* level, sf::RenderWindow* window);
