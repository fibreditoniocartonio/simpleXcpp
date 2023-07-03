#include "../inc/menu.hpp"
#include "../inc/gameEngine.hpp"

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
	
//constructor and destructor
Menu::Menu(){}
Menu::~Menu(){}

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
			testo.setPosition(sf::Vector2f(x+this->borderDim, y+this->borderDim));
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
				//read input
				for(int i=0; i<11; i++){
					if(game->keys[i]){this->isClosing=true;}
				}
			}else{
				this->Animation();
				if(this->width < 1 && this->height < 1){
					game->ChangeGameState(this->previousGameState, this->previousMenu);
					delete this;
				}
			}
		}
}

//constructor
Alert::Alert(GameEngine* game, int charSize, std::string stringa){
		this->width=0;
		this->height=0;
		this->maxWidth=game->windowWidth;
		this->maxHeight=game->windowHeight;
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
