#pragma once

#include <string>
#include <vector>
#include <fstream> 

#include <SFML/Graphics.hpp>
#include "menu.hpp"


class GameEngine;
class Testo;

class Editor : public Menu{  //gamestate 1000
 public:
    GameEngine* game;
    void* previousMenu;
    int index, maxIndex, previousGameState, windowWidthEditor, windowHeightEditor;
    bool showCameraDot, tastoGiaSchiacciato;
    int state;
    /*  state 0: in level editor
        state 1: level editor main menu
    */
    std::vector<Testo*> textClick;
    sf::Text testo;
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Vector2f camera;
    sf::View view;
	Editor(GameEngine* game);
    void InitializeClickableText();
    void CloseEditor();
	void Render(sf::RenderWindow* window) override;
	void Physics(GameEngine* game) override;
};