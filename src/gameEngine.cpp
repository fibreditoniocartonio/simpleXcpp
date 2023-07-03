#include "../inc/gameEngine.hpp"
#include "../inc/menu.hpp"

void GameEngine::ChangeGameState(int newGameState, void* newMenu){
		this->currentMenu=newMenu;
		this->gamestate=newGameState;
}

void GameEngine::updateKeys(sf::Keyboard::Key keyInput, bool isPressed){
		for (int keyIndex=0; keyIndex < sizeof(keys)/sizeof(bool); keyIndex++){
			if(keyInput==keySettings[keyIndex][0] || keyInput==keySettings[keyIndex][1]){
				if(isPressed){
					keys[keyIndex]=true;
					ultimoTastoLetto=keyIndex;
				}else{
					keys[keyIndex]=false;
				}
			}
		}
}

//costructor
GameEngine::GameEngine(){
		if(!this->font.loadFromFile("res/font/PixelOperatorMono.ttf")){/*error loading fonts*/}
        //this->font.setSmooth(false); //require SFML 2.6 and I only have 2.5.1 on gentoo
}

