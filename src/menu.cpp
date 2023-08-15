#include "../inc/menu.hpp"
#include "../inc/gameEngine.hpp"
#include "../inc/textEngine.hpp"

void Menu::Physics(GameEngine* game) {}
void Menu::Render(sf::RenderWindow* window){}
void Menu::Animation(){
		if(!this->isClosing){
			this->width+=(int)(this->maxWidth/speed);
			this->height+=(int)(this->maxWidth/speed);
		}else{
			this->width-=(int)(this->maxWidth/speed);
			this->height-=(int)(this->maxHeight/speed);
		}
}
Menu::Menu(){}
Menu::~Menu(){}

void AlignCenter(sf::Text* text){
	text->setOrigin(sf::Text().getGlobalBounds().left+text->getGlobalBounds().width/2.0f, sf::Text().getGlobalBounds().top +text->getGlobalBounds().height/2.0f);
}
void AlignLeft(sf::Text* text){
	text->setOrigin(sf::Text().getOrigin());
}


//Alert -> gamestate = 1
void Alert::Render(sf::RenderWindow* window){
		sf::RectangleShape rect;
		rect.setSize(sf::Vector2f(this->width, this->height));
		int x=(int)(window->getView().getCenter().x - this->width/2);
		int y=(int)(window->getView().getCenter().y - this->height/2);
		rect.setPosition(x,y);
		rect.setFillColor(this->color2);
		window->draw(rect);
		if((this->width > this->borderDim) && (this->height > this->borderDim)){
			rect.setPosition(x+(this->borderDim/2),y+(this->borderDim/2));
			rect.setSize(sf::Vector2f((this->width - this->borderDim), (this->height - this->borderDim)));
			rect.setFillColor(this->color1);
			window->draw(rect);
		}
		if(this->isOpen && !this->isClosing){
			this->testo.setPosition(sf::Vector2f(x+this->borderDim, y+this->borderDim));
			window->draw(this->testo);
		}
}
void Alert::Physics(GameEngine* game){
		if(!this->isOpen){
			this->Animation();
			if(this->width > this->maxWidth){this->width=this->maxWidth;}
			if(this->height > this->maxHeight){this->height=this->maxHeight;}
			if(this->width == this->maxWidth && this->height == this->maxHeight){this->isOpen=true;}
		}else{
			if(!this->isClosing){
				if(this->timer>0){
					this->timer--;
				}else{
					for(int i=0; i<11; i++){
						//read input to close the Alert
						if(game->keys[i]){this->isClosing=true;}
					}
				}
			}else{
				if(this->previousGameState == -1){
					this->Animation();
					if(this->width < 1 && this->height < 1){
						game->ChangeGameState(this->previousGameState, this->previousMenu);
						delete this;
					}
				}else{
					game->ChangeGameState(this->previousGameState, this->previousMenu);
					delete this;
				}
			}
		}
}
Alert::Alert(GameEngine* game, int charSize, std::string stringa){
	this->maxWidth=game->windowWidth;
	this->maxHeight=game->windowHeight;
	if(game->gamestate != -1){
		this->timer = 5;
		this->width = this->maxWidth;
		this->height = this->maxHeight;
	}else{
		this->timer = 0;
		this->width=0;
		this->height=0;
	}
	this->borderDim=16;
	this->speed=14;
	this->color1 = sf::Color(82,181,139,255);
	this->color2 = sf::Color(200,200,200,255);
	this->previousGameState = game->gamestate;
	this->previousMenu = game->currentMenu;
        std::string finalString = "";	
	int maxCharPerLine=(int)(2*(this->maxWidth-(2*this->borderDim))/charSize);
        int charNum = 1;
	for(int i=0; i < stringa.length(); i++){
            finalString += stringa[i];
            charNum++;
            if(std::isspace(stringa[i])){
                if(stringa[i]=='\n'){
                    charNum=1;
                }else{            
                int verifySpace = charNum;
                    for(int j=i+1; j < stringa.length(); j++){
                        verifySpace++;
                        if(verifySpace > maxCharPerLine){
                            charNum = verifySpace+1;
                        }
                        if(std::isspace(stringa[j])){
                            j = stringa.length();
                        }                    
                    }
                }
            }
            if(charNum > maxCharPerLine){
                finalString += "\n";
                charNum=1;
            }    
	}
	this->testo = sf::Text(finalString, game->font, charSize);
	this->testo.setFillColor(sf::Color::White);
	game->ChangeGameState(1, this);
}


//MainMenu -> gamestate = 2
void MainMenu::Render(sf::RenderWindow* window){
	int x=(int)(window->getView().getCenter().x - this->width/2);
	int y=(int)(window->getView().getCenter().y - this->height/2);
	if(this->isOpen && !this->isClosing){
        this->titleScreenSprite.setPosition(sf::Vector2f(x,y));
        window->draw(this->titleScreenSprite);    
        this->testo.setCharacterSize(32);
		for(int i=0; i < this->maxIndex; i++){
			this->testo.setPosition(sf::Vector2f(x+this->width/3, y+this->height/2+this->testo.getCharacterSize()*i));
			std::string txtString = " ";
			if(this->index == i){
				this->testo.setFillColor(sf::Color(216,136,0,255));
				txtString = ">";
			}else{
				this->testo.setFillColor(sf::Color(63,72,255,255));
			}
			switch(i){
			 case 0: txtString+=this->game->textEngine->testo[1];
			 	break;
			 case 1: txtString+=this->game->textEngine->testo[2];
			 	break;
			 default: txtString+=this->game->textEngine->testo[3];
			 	break;
			}
			this->testo.setString(txtString);
			window->draw(this->testo);
		}
        this->testo.setCharacterSize(16);
        this->testo.setFillColor(sf::Color::White);
        this->testo.setPosition(sf::Vector2f(x, y+this->height-this->testo.getCharacterSize()));
		this->testo.setString(versioneDiGioco);
		window->draw(this->testo);        
	}
    if(this->exitGame){window->close();}
}
void MainMenu::Physics(GameEngine* game){
		if(!this->isOpen){ //menu is opening
			this->Animation();
			if(this->width > this->maxWidth){this->width=this->maxWidth;}
			if(this->height > this->maxHeight){this->height=this->maxHeight;}
			if(this->width == this->maxWidth && this->height == this->maxHeight){this->isOpen=true;}
		}else{
			if(!this->isClosing){ //menu is open
				bool tastiPremuti = false;
				if((game->keys[5] || game->keys[7]) && !this->tastoGiaSchiacciato){
                    switch(this->index){
                        case 0: //New Game
                            this->previousGameState = -1; this->previousMenu = NULL;
                            this->isClosing = true;
                            break;
                        case 1: //Settings
                            new SettingsMenu(game);
                            break;
                        default: this->exitGame=true; break; //this flag will make Render() to call window->close()
                    }
				}
				if(game->keys[0] && !this->tastoGiaSchiacciato){
					this->index--;
				}
				if(game->keys[1] && !this->tastoGiaSchiacciato){
					this->index++;
				}
				if(this->index > this->maxIndex-1){this->index = 0;}
				if(this->index < 0){this->index = this->maxIndex-1;}
				for(int i=0; i<11; i++){ if(game->keys[i]){tastiPremuti=true;} }
				this->tastoGiaSchiacciato=tastiPremuti;
			}else{ //menu is closing
				if(this->previousGameState == -1){
					this->Animation();
					if(this->width < 1 && this->height < 1){
						game->ChangeGameState(this->previousGameState, this);
						delete this;
					}
				}else{
					game->ChangeGameState(this->previousGameState, this->previousMenu);
					delete this;
				}
			}
		}
}
MainMenu::MainMenu(GameEngine* game){
	this->index = 0;
    this->maxIndex = 3;
	this->maxWidth=game->windowWidth;
	this->maxHeight=game->windowHeight;
	if(game->gamestate != -1){
		this->width = this->maxWidth;
		this->height = this->maxHeight;
	}else{
		this->width=0;
		this->height=0;
	}
	this->speed=14;
    if (!this->titleScreenImg.loadFromFile("./res/img/titlescreen/titlescreen.png")){
        new Alert(game, 16, this->game->textEngine->testo[4]+"\n\n./res/img/titlescreen/titlescreen.png");
    }
    this->titleScreenImg.setSmooth(false); //do not blur the pixels
    this->titleScreenSprite.setTexture(this->titleScreenImg);    
	this->previousGameState = game->gamestate;
	this->previousMenu = game->currentMenu;
	this->testo = sf::Text("", game->font, 32);
    this->game = game;
	game->ChangeGameState(2, this);
} 


//SettingsMenu -> gamestate = 3
void SettingsMenu::Render(sf::RenderWindow* window){
	sf::RectangleShape rect;
	rect.setSize(sf::Vector2f(this->width, this->height));
	int x=(int)(window->getView().getCenter().x - this->width/2);
	int y=(int)(window->getView().getCenter().y - this->height/2);
	rect.setPosition(x,y);
	rect.setFillColor(this->color2);
	window->draw(rect);
	if((this->width > this->borderDim) && (this->height > this->borderDim)){
		rect.setPosition(x+(this->borderDim/2),y+(this->borderDim/2));
		rect.setSize(sf::Vector2f((this->width - this->borderDim), (this->height - this->borderDim)));
		rect.setFillColor(this->color1);
		window->draw(rect);
	}
	if(this->isOpen && !this->isClosing){
		switch(this->state){
		 case 0: //main settings menu
			this->testo.setCharacterSize(32);
			this->testo.setString(this->game->textEngine->testo[5]);
			this->testo.setFillColor(sf::Color(255,0,0,255));
			AlignCenter(&this->testo);
			this->testo.setPosition(sf::Vector2f(x+this->width/2, y+this->borderDim/2));
			window->draw(this->testo);
			this->testo.setCharacterSize(16);
			AlignLeft(&this->testo);
			for(int i=0; i<this->maxIndex; i++){
				this->testo.setPosition(sf::Vector2f(x+borderDim/2, y+(this->testo.getLineSpacing()*(2+i)+this->testo.getCharacterSize()*2+this->testo.getCharacterSize()*i)));
				std::string txtString = " ";
				if(this->index == i){
					this->testo.setFillColor(sf::Color(255,0,0,255));
					txtString = ">";
				}else{
					this->testo.setFillColor(sf::Color::White);
				}
				switch(i){
				 case 0: txtString+=this->game->textEngine->testo[6];
				 	break;
				 case 1: txtString+=this->game->textEngine->testo[7];
				 	break;
				 case 2: txtString+=this->game->textEngine->testo[24]+": "+this->game->textEngine->testo[0];
				 	break;
				 default: txtString+=this->game->textEngine->testo[8];
				 	break;
				}
				this->testo.setString(txtString);
				window->draw(this->testo);
			}
			break;

		 case 1: //keyboard settings menu
			this->testo.setCharacterSize(32);
			this->testo.setString(this->game->textEngine->testo[9]);
			this->testo.setFillColor(sf::Color(255,0,0,255));
			AlignCenter(&this->testo);
			this->testo.setPosition(sf::Vector2f(x+this->width/2, y+this->borderDim/2));
			window->draw(this->testo);
			this->testo.setCharacterSize(16);
			AlignLeft(&this->testo);
			for(int i=0; i<(this->maxIndex-1)/2+1; i++){
				if(i<(this->maxIndex-1)/2){
				  for(int j=0; j<2; j++){
					this->testo.setPosition(sf::Vector2f(x+(j*2+1)*this->width/5, y+(this->testo.getLineSpacing()*(2+i)+this->testo.getCharacterSize()*2+this->testo.getCharacterSize()*i)));
					if(this->index == i+j*(this->maxIndex-1)/2){
						if(this->game->listenNewKey != 1){
						this->testo.setString(">"+std::to_string(game->keySettings[i][j]));
						//this->testo.setString(">"+sf::Keyboard().getDescription(sf::Keyboard().delocalize(game->keySettings[i][j]))); //require SFML 2.6 that i dont have
						}else{
						this->testo.setString(">____________");
						}
						this->testo.setFillColor(sf::Color(255,0,0,255));
					}else{
						this->testo.setString(" "+std::to_string(game->keySettings[i][j]));
                        //this->testo.setString(" "+sf::Keyboard().getDescription(sf::Keyboard().delocalize(game->keySettings[i][j]))); //require SFML 2.6 that i dont have
						this->testo.setFillColor(sf::Color::White);
					}
					window->draw(this->testo);
				  }
				}
				this->testo.setFillColor(sf::Color::White);
				this->testo.setPosition(sf::Vector2f(x+borderDim/2, y+(this->testo.getLineSpacing()*(2+i)+this->testo.getCharacterSize()*2+this->testo.getCharacterSize()*i)));
				switch(i){
				 case 0:  this->testo.setString(" "+this->game->textEngine->testo[11]+":"); break;
				 case 1:  this->testo.setString(" "+this->game->textEngine->testo[12]+":"); break;
				 case 2:  this->testo.setString(" "+this->game->textEngine->testo[13]+":"); break;
				 case 3:  this->testo.setString(" "+this->game->textEngine->testo[14]+":"); break;
				 case 4:  this->testo.setString(" "+this->game->textEngine->testo[15]+":"); break;
				 case 5:  this->testo.setString(" "+this->game->textEngine->testo[16]+":"); break;
				 case 6:  this->testo.setString(" "+this->game->textEngine->testo[17]+":"); break;
				 case 7:  this->testo.setString(" "+this->game->textEngine->testo[18]+":"); break;
				 case 8:  this->testo.setString(" "+this->game->textEngine->testo[19]+":"); break;
				 case 9:  this->testo.setString(" "+this->game->textEngine->testo[20]+":"); break;
				 case 10: this->testo.setString(" "+this->game->textEngine->testo[21]+":"); break;
				 default:
				 	if(this->index == this->maxIndex-1){
						this->testo.setString(">"+this->game->textEngine->testo[8]);
						this->testo.setFillColor(sf::Color(255,0,0,255));
					}else{
						this->testo.setString(" "+this->game->textEngine->testo[8]);
					}
					break;
				}
				window->draw(this->testo);
			}
		 	break;

		 case 2: //gamepad settings menu
			this->testo.setCharacterSize(32);
			this->testo.setString(this->game->textEngine->testo[10]);
			this->testo.setFillColor(sf::Color(255,0,0,255));
			AlignCenter(&this->testo);
			this->testo.setPosition(sf::Vector2f(x+this->width/2, y+this->borderDim/2));
			window->draw(this->testo);
			this->testo.setCharacterSize(16);
			AlignLeft(&this->testo);
			for(int i=0; i<(this->maxIndex-1)/2+1; i++){
				if(i<(this->maxIndex-1)/2){
				  for(int j=0; j<2; j++){
					this->testo.setPosition(sf::Vector2f(x+(j+1)*this->width/3, y+(this->testo.getLineSpacing()*(2+i)+this->testo.getCharacterSize()*2+this->testo.getCharacterSize()*i)));
					std::string keyBinded;
					if(game->joystickHandler.keySettings[i][j] == -1){
						keyBinded = "-"; //not bound
					}else{
						keyBinded = std::to_string(game->joystickHandler.keySettings[i][j]);
					}
					if(this->index == i+j*(this->maxIndex-1)/2){
						if(this->game->listenNewKey != 2){
							this->testo.setString(">"+keyBinded);
						}else{
							this->testo.setString(">__");
						}
						this->testo.setFillColor(sf::Color(255,0,0,255));
					}else{
						this->testo.setString(" "+keyBinded);
						this->testo.setFillColor(sf::Color::White);
					}
					window->draw(this->testo);
				  }
				}
				this->testo.setFillColor(sf::Color::White);
				this->testo.setPosition(sf::Vector2f(x+borderDim/2, y+(this->testo.getLineSpacing()*(2+i)+this->testo.getCharacterSize()*2+this->testo.getCharacterSize()*i)));
				switch(i){
				 case 0:  this->testo.setString(" "+this->game->textEngine->testo[11]+":"); break;
				 case 1:  this->testo.setString(" "+this->game->textEngine->testo[12]+":"); break;
				 case 2:  this->testo.setString(" "+this->game->textEngine->testo[13]+":"); break;
				 case 3:  this->testo.setString(" "+this->game->textEngine->testo[14]+":"); break;
				 case 4:  this->testo.setString(" "+this->game->textEngine->testo[15]+":"); break;
				 case 5:  this->testo.setString(" "+this->game->textEngine->testo[16]+":"); break;
				 case 6:  this->testo.setString(" "+this->game->textEngine->testo[17]+":"); break;
				 case 7:  this->testo.setString(" "+this->game->textEngine->testo[18]+":"); break;
				 case 8:  this->testo.setString(" "+this->game->textEngine->testo[19]+":"); break;
				 case 9:  this->testo.setString(" "+this->game->textEngine->testo[20]+":"); break;
				 case 10: this->testo.setString(" "+this->game->textEngine->testo[21]+":"); break;
				 default:
				 	if(this->index == this->maxIndex-1){
						this->testo.setString(">"+this->game->textEngine->testo[8]);
						this->testo.setFillColor(sf::Color(255,0,0,255));
					}else{
						this->testo.setString(" "+this->game->textEngine->testo[8]);
					}
					break;
				}
				window->draw(this->testo);
			}
		 	break;
		 default: break;
		}//fine switch(state)
	}
}
void SettingsMenu::Physics(GameEngine* game){
		if(!this->isOpen){ //menu is opening
			this->Animation();
			if(this->width > this->maxWidth){this->width=this->maxWidth;}
			if(this->height > this->maxHeight){this->height=this->maxHeight;}
			if(this->width == this->maxWidth && this->height == this->maxHeight){this->isOpen=true;}
		}else{
			if(!this->isClosing){ //menu is open
				int currentState = this->state;
				bool tastiPremuti = false;
				switch(this->state){
				 case 0: //main settings menu
				 	this->maxIndex=4;
					if(game->keys[4] && !this->tastoGiaSchiacciato){this->isClosing=true;}
					if((game->keys[5] || game->keys[7]) && !this->tastoGiaSchiacciato){
						switch (this->index){
							case 0: case 1:
								this->state=this->index+1;
								this->index = 0;
								break;
							case 2:
								if(this->langIndex < this->langMaxIndex){
									this->langIndex++;
								}else{
									this->langIndex=0;
								}
								this->game->SetLanguage(this->game->textEngine->languagesFound[this->langIndex]);
								break;
							default:
								this->isClosing=true;
								break;
						}
					}
					break;

				 case 1: //keyboard settings menu
				 	this->maxIndex=23;
					if(!this->listenNewKey && game->listenNewKey != 1){
						if(game->keys[4] && !this->tastoGiaSchiacciato){this->index=this->state-1; this->state=0;}
						if((game->keys[0] && this->index == (this->maxIndex-1)/2) && !this->tastoGiaSchiacciato){this->index = this->maxIndex;}
						if((game->keys[0] && this->index == this->maxIndex-1) && !this->tastoGiaSchiacciato){this->index = (this->maxIndex-1)/2;}
						if((game->keys[1] && this->index == (this->maxIndex-1)/2-1) && !this->tastoGiaSchiacciato){this->index = this->maxIndex-2;}
						if((game->keys[2] || game->keys[3] )&& !this->tastoGiaSchiacciato){
							if(this->index < (this->maxIndex-1)/2){ 
								this->index += (this->maxIndex-1)/2;
							}else{
								this->index -= (this->maxIndex-1)/2;
							}
						}
						if((game->keys[5] || game->keys[7]) && !this->tastoGiaSchiacciato){
							if(this->index == this->maxIndex-1){
								this->index=this->state-1; this->state=0;
							}else{
								this->listenNewKey = true;
							}
						}
					}else{
						if(game->listenNewKey != 1){
							if(this->index < (this->maxIndex-1)/2){
								game->newKeyIndex[0]=this->index; game->newKeyIndex[1]=0;
							}else{
								game->newKeyIndex[0]=this->index-(this->maxIndex-1)/2; game->newKeyIndex[1]=1;
							}
							game->listenNewKey=1;
							this->listenNewKey=false;
						}else{
							tastiPremuti=true; //don't read input in this menu until a new key is bound
						}
					}
				 	break;

				 case 2: //gamepad settings menu
				 	this->maxIndex=23;
					if(!this->listenNewKey && game->listenNewKey != 2){
						if(game->keys[4] && !this->tastoGiaSchiacciato){this->index=this->state-1; this->state=0;}
						if((game->keys[0] && this->index == (this->maxIndex-1)/2) && !this->tastoGiaSchiacciato){this->index = this->maxIndex;}
						if((game->keys[0] && this->index == this->maxIndex-1) && !this->tastoGiaSchiacciato){this->index = (this->maxIndex-1)/2;}
						if((game->keys[1] && this->index == (this->maxIndex-1)/2-1) && !this->tastoGiaSchiacciato){this->index = this->maxIndex-2;}
						if((game->keys[2] || game->keys[3] )&& !this->tastoGiaSchiacciato){
							if(this->index < (this->maxIndex-1)/2){ 
								this->index += (this->maxIndex-1)/2;
							}else{
								this->index -= (this->maxIndex-1)/2;
							}
						}
						if((game->keys[5] || game->keys[7]) && !this->tastoGiaSchiacciato){
							if(this->index == this->maxIndex-1){
								this->index=this->state-1; this->state=0;
							}else{
								bool atLeastOneJoystickIsConnected = false;
								for(int i=0; i < 8; i++){ if(sf::Joystick::isConnected(i)){ atLeastOneJoystickIsConnected=true; } }
								if(atLeastOneJoystickIsConnected){
									this->listenNewKey = true;
								}else{
									new Alert(game, 16, this->game->textEngine->testo[22]+"\n\n"+this->game->textEngine->testo[23]);
								}
							}
						}
					}else{
						if(game->listenNewKey != 2){
							if(this->index < (this->maxIndex-1)/2){
								game->newKeyIndex[0]=this->index; game->newKeyIndex[1]=0;
							}else{
								game->newKeyIndex[0]=this->index-(this->maxIndex-1)/2; game->newKeyIndex[1]=1;
							}
							game->listenNewKey=2;
							this->listenNewKey=false;
						}else{
							tastiPremuti=true; //don't read input in this menu until a new key is bound
						}
					}
				 	break;

				 default: break;
				}//fine switch(state)
				if(game->keys[0] && !this->tastoGiaSchiacciato){
					this->index--;
				}
				if(game->keys[1] && !this->tastoGiaSchiacciato){
					this->index++;
				}
				if(this->index > this->maxIndex-1){this->index = 0;}
				if(this->index < 0){this->index = this->maxIndex-1;}
				for(int i=0; i<11; i++){ if(game->keys[i]){tastiPremuti=true;} }
				this->tastoGiaSchiacciato=tastiPremuti;
				if(currentState != this->state){this->Physics(game);} //update maxIndex to avoid rendering issues
			}else{ //menu is closing
				if(this->previousGameState == -1){
					this->Animation();
					if(this->width < 1 && this->height < 1){
						game->ChangeGameState(this->previousGameState, this->previousMenu);
						delete this;
					}
				}else{
					game->ChangeGameState(this->previousGameState, this->previousMenu);
					delete this;
				}
			}
		}
}
SettingsMenu::SettingsMenu(GameEngine* game){
	this->game = game;
	this->index = 0; this->maxIndex = 0;
	this->langMaxIndex = game->textEngine->languagesFoundCount-1;
	for(this->langIndex=0; this->langIndex<this->langMaxIndex+1; this->langIndex++){
		if(this->game->textEngine->languagesFound[this->langIndex] == this->game->language){break;}
	}
	this->listenNewKey = false;
	this->maxWidth=game->windowWidth;
	this->maxHeight=game->windowHeight;
	if(game->gamestate != -1){
		this->width = this->maxWidth;
		this->height = this->maxHeight;
	}else{
		this->width=0;
		this->height=0;
	}
	this->borderDim=16;
	this->speed=14;
	this->color1 = sf::Color(82,181,139,255);
	this->color2 = sf::Color(200,200,200,255);
	this->previousGameState = game->gamestate;
	this->previousMenu = game->currentMenu;
	this->testo = sf::Text("", game->font, 32);
	game->ChangeGameState(3, this);
	this->state = 0;
} 
