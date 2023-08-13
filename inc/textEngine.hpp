#pragma once

#include <string>
#include <vector>
#include <fstream> 

#include <SFML/Graphics.hpp>

class GameEngine;

class TextEngine {
 public:
    GameEngine* game;
    std::vector<std::string> languagesFound;
    int languagesFoundCount, contaTesto;
    std::vector<std::string> testo;
	TextEngine(GameEngine* game);
	void LoadText(std::string language);
	void CleanText();
    void ReadHowManyLang();
};