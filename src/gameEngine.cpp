#include "../inc/gameEngine.hpp"
#include "../inc/textEngine.hpp"
#include "../inc/levelEditor.hpp"
#include "../inc/menu.hpp"

int JoystickHandler::GetAxisKey(sf::Event* evento){
    if(evento->joystickMove.position > this->axisDeadZone){
        return (33*(evento->joystickMove.axis+1)+1);
    }else if(evento->joystickMove.position < -this->axisDeadZone){
        return (33*(evento->joystickMove.axis+1)+2);
    }else{
        return -(33*(evento->joystickMove.axis+1));
    }
    return -1;
}

void GameEngine::ChangeGameState(int newGameState, void* newMenu){
		this->currentMenu=newMenu;
		this->gamestate=newGameState;
}

void GameEngine::UpdateKeys(sf::Keyboard::Key keyInput, bool isPressed){
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

void GameEngine::UpdateMouseCoordinate(sf::Vector2f absoluteMousePosition){
	switch(this->gamestate){
		case 1000:	//level editor
			this->mouse.x = absoluteMousePosition.x * (float)static_cast<Editor*>(this->currentMenu)->windowWidthEditor / (float)this->window->getSize().x;
			this->mouse.y = absoluteMousePosition.y * (float)static_cast<Editor*>(this->currentMenu)->windowHeightEditor / (float)this->window->getSize().y;
			break;
		default:
			if(this->window->getSize().x > this->window->getSize().y){
				this->mouse.x = (absoluteMousePosition.x-((float)this->window->getSize().x*(float)this->window->getView().getViewport().left)) * (float)this->windowWidth / ((float)this->window->getSize().x-2*(float)this->window->getSize().x*(float)this->window->getView().getViewport().left);
				this->mouse.y = absoluteMousePosition.y * (float)this->windowHeight / (float)this->window->getSize().y;
			}else{
				this->mouse.x = absoluteMousePosition.x * (float)this->windowWidth / (float)this->window->getSize().x;
				this->mouse.y = (absoluteMousePosition.y-((float)this->window->getSize().y*(float)this->window->getView().getViewport().top)) * (float)this->windowHeight / ((float)this->window->getSize().y-2*(float)this->window->getSize().y*(float)this->window->getView().getViewport().top);
			}
			break;
	}
}
void GameEngine::UpdateMouseButton(sf::Mouse::Button mouseInput, bool isPressed){
	if(mouseInput == sf::Mouse::Left){
		this->mouseClick[0] = isPressed;
	}else if(mouseInput == sf::Mouse::Right){
		this->mouseClick[1] = isPressed;
	}
}

void GameEngine::UpdateKeysJoystick(int keyInput, bool isPressed){
	for (int keyIndex=0; keyIndex < sizeof(this->keys)/sizeof(bool); keyIndex++){
        if(keyInput>0){
		  if(keyInput==this->joystickHandler.keySettings[keyIndex][0] || keyInput==this->joystickHandler.keySettings[keyIndex][1]){
			 if(isPressed){
				this->keys[keyIndex]=true;
				this->ultimoTastoLetto=keyIndex;
			 }else{
				this->keys[keyIndex]=false;
			 }
		  }
        }else{
            //axis deadzone
            if((1-keyInput)==this->joystickHandler.keySettings[keyIndex][0] || (2-keyInput)==this->joystickHandler.keySettings[keyIndex][0] || (1-keyInput)==this->joystickHandler.keySettings[keyIndex][1] || (2-keyInput)==this->joystickHandler.keySettings[keyIndex][1]){
                this->keys[keyIndex]=false;
            }
        }
	}    
}

void  GameEngine::BindNewKeyKB(sf::Keyboard::Key keyInput){
	this->keySettings[this->newKeyIndex[0]][this->newKeyIndex[1]] = keyInput;
	this->listenNewKey = -1;
}
void  GameEngine::BindNewKeyJS(int keyInput){
	this->joystickHandler.keySettings[this->newKeyIndex[0]][this->newKeyIndex[1]] = keyInput;
	this->listenNewKey = -1;
}

void GameEngine::SetLanguage(std::string language){	
	this->language = language;
	this->UpdateTextLanguage();
}

void GameEngine::UpdateTextLanguage(){	
	this->textEngine->LoadText(this->language);
}

//costructor
GameEngine::GameEngine(){
	this->textEngine = new TextEngine(this);
	if(!this->font.loadFromFile("res/font/PixelOperatorMono.ttf")){/*error loading fonts*/}
    //this->font.setSmooth(false); //require SFML 2.6 and I only have 2.5.1 on gentoo
}

