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
    int index, maxIndex, previousGameState, windowWidthEditor, windowHeightEditor, toolsMenuAreaX;
    bool showCameraDot, tastoGiaSchiacciato;
    int state;
    /*  state -1: in level editor
        state 0: level editor main menu
    */
    sf::Text testo;
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Vector2f camera;
    sf::View view;
	Editor(GameEngine* game);
    void CloseEditor();
	void Render(sf::RenderWindow* window) override;
	void Physics(GameEngine* game) override;
};