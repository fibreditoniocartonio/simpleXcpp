class Menu {
 public:
	int width, height, maxWidth, maxHeight, speed;
	bool isOpen=false, isClosing=false;

	virtual void Physics(GameEngine* game) {}
	virtual void Render(sf::RenderWindow* window){}
	virtual	void Animation(){
		if(!this->isClosing){
			this->width+=(int)(this->maxWidth/speed);
			this->height+=(int)(this->maxWidth/speed);
		}else{
			this->width-=(int)(this->maxWidth/speed);
			this->height-=(int)(this->maxHeight/speed);
		}
	}
	
	//constructor and destructor
	Menu() {}
	virtual ~Menu() {}
};


class Alert : public Menu{
 public:
	int previousGameState, borderDim;
	sf::Text testo;
	sf::Color color1, color2;
	
	void Render(sf::RenderWindow* window) override{
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

	void Physics(GameEngine* game) override{
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
					switch(previousGameState){
						default: 
							game->ChangeGameState(-1, NULL); 
							break;
					}
				}
			}
		}
	}

	//constructor
	Alert(GameEngine* game, int charSize, std::string stringa){
		this->width=0;
		this->height=0;
		this->maxWidth=game->windowWidth;
		this->maxHeight=game->windowHeight;
		this->borderDim=16;
		this->speed=14;
		this->color1 = sf::Color(82,181,139,255);
		this->color2 = sf::Color(200,200,200,255);
		this->previousGameState = game->gamestate;
		
		int maxCharPerLine=(int)(2*(this->maxWidth-(2*this->borderDim))/charSize);
		int lines=1+(int)(stringa.length()/maxCharPerLine);
		std::string finalString=stringa.substr(0, maxCharPerLine);
		for(int i=1; i < lines; i++){
			finalString +="\n"+stringa.substr(i*maxCharPerLine, maxCharPerLine);
		}
		this->testo = sf::Text(finalString, game->font, charSize);
		this->testo.setFillColor(sf::Color::White);
		game->ChangeGameState(1, this);
	}
};
