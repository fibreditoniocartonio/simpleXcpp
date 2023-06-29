class Player {
 public:
	int x=0, y=0;
	float xv=0, yv=0; //momentum
	int width=20, height=24;
	float speed=1;
	sf::RectangleShape shape;
	sf::Font font;
	sf::Text text;
	const int charSize=8;

	Player(){
		this->shape.setSize(sf::Vector2f(this->width, this->height));
		this->shape.setFillColor(sf::Color(0,64,240,255));
	
		this->text.setCharacterSize(this->charSize);
		this->text.setFillColor(sf::Color::Yellow);
		if(!this->font.loadFromFile("res/font/PixelOperatorMono.ttf")){/*error loading fonts*/}
		//this->font.setSmooth(false); //require SFML 2.6 (I have 2.5.1 because it's the last available on Gentoo...)
		this->text.setFont(this->font);
	}

	virtual void Physics(GameEngine* game, Livello* level){
		float speed=this->speed;
		if(game->keys[5]){speed*=2.25;}
		if(game->keys[0]){this->yv-=speed;}
		if(game->keys[1]){this->yv+=speed;}
		if(game->keys[2]){this->xv+=speed;}
		if(game->keys[3]){this->xv-=speed;}
		this->xv=this->xv*level->friction;
		this->yv=this->yv*level->friction;
		this->x+=(int)this->xv;
		this->y+=(int)this->yv;
		this->shape.setPosition(this->x,this->y);
		this->text.setString(("X: "+std::to_string((int)this->x)+"\nY: "+std::to_string((int)this->y)));
		this->text.setPosition(this->x, this->y);
	} 

	virtual void Render(sf::RenderWindow* window){
		window->draw(this->shape);
		window->draw(this->text);
	}
};
