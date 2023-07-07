#include "../inc/gameEngine.hpp"
#include "../inc/menu.hpp"

int JoystickHandler::GetAxisKey(sf::Event* evento){
    if(evento->joystickMove.position > this->axisDeadZone){
        return (33+evento->joystickMove.axis+1);
    }else if(evento->joystickMove.position < -this->axisDeadZone){
        return (33+evento->joystickMove.axis+2);
    }else{
        return -(33+evento->joystickMove.axis);
    }
    return -1;
}

void GameEngine::ChangeGameState(int newGameState, void* newMenu){
		this->currentMenu=newMenu;
		this->gamestate=newGameState;
}

void GameEngine::updateKeys(sf::Keyboard::Key keyInput, bool isPressed){
		for (int keyIndex=0; keyIndex < sizeof(this->keys)/sizeof(bool); keyIndex++){
			if(keyInput==this->keySettings[keyIndex][0] || keyInput==this->keySettings[keyIndex][1]){
				if(isPressed){
					this->keys[keyIndex]=true;
					this->ultimoTastoLetto=keyIndex;
				}else{
					this->keys[keyIndex]=false;
				}
			}
		}
}

void GameEngine::updateKeysJoystick(int keyInput, bool isPressed){
	for (int keyIndex=0; keyIndex < sizeof(this->keys)/sizeof(bool); keyIndex++){
        if(keyInput>0){
		  if(keyInput==this->joystickHandler.keySettings[keyIndex]){
			 if(isPressed){
				this->keys[keyIndex]=true;
				this->ultimoTastoLetto=keyIndex;
			 }else{
				this->keys[keyIndex]=false;
			 }
		  }
        }else{
            //axis deadzone
            if((1-keyInput)==this->joystickHandler.keySettings[keyIndex] || (2-keyInput)==this->joystickHandler.keySettings[keyIndex]){
                this->keys[keyIndex]=false;
            }
        }
	}    
}

//costructor
GameEngine::GameEngine(){
		if(!this->font.loadFromFile("res/font/PixelOperatorMono.ttf")){/*error loading fonts*/}
        //this->font.setSmooth(false); //require SFML 2.6 and I only have 2.5.1 on gentoo
}

