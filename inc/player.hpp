class Player {
 public:
	int x=0, y=0;
	int width=24, height=24;
	int speed=1;
	sf::RectangleShape shape;
	sf::Font font;
	sf::Text text;
	const int charSize=8;

	Player(){
		this->shape.setSize(sf::Vector2f(this->width, this->height));
		this->shape.setFillColor(sf::Color::Green);
	
		this->text.setCharacterSize(this->charSize);
		this->text.setFillColor(sf::Color::Red);
		if(!this->font.loadFromFile("res/font/PixelOperatorMono.ttf")){/*error loading fonts*/}
		//this->font.setSmooth(false); //require SFML 2.6 (I have 2.5.1 because it's the last available on Gentoo...)
		this->text.setFont(this->font);
	}

	virtual void Physics(GameEngine* game, Livello* level){
		int speed=this->speed;
		if(game->keys[5]){speed*=5;}
		if(game->keys[0]){this->y-=speed;}
		if(game->keys[1]){this->y+=speed;}
		if(game->keys[2]){this->x+=speed;}
		if(game->keys[3]){this->x-=speed;}
		this->shape.setPosition(this->x,this->y);
		this->text.setString(("X: "+std::to_string((int)this->x)+"\nY: "+std::to_string((int)this->y)));
		this->text.setPosition(this->x, this->y);
	} 

	virtual void Render(sf::RenderWindow* window){
		window->draw(this->shape);
		window->draw(this->text);
	}
};
