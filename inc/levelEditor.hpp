#pragma once

#include <string>
#include <vector>
#include <fstream> 

#include <SFML/Graphics.hpp>
#include "menu.hpp"


class GameEngine;

class Editor : public Menu{  //gamestate 1000
 public:
    GameEngine* game;
    void* previousMenu;
    int state, previousGameState, windowWidthEditor, windowHeightEditor;
    sf::Vector2f camera;
	Editor(GameEngine* game);
    void CloseEditor();
	void Render(sf::RenderWindow* window) override;
	void Physics(GameEngine* game) override;
};