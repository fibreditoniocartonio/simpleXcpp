int CollisionBetween(Entity* e1, Entity* e2);

class Player {
 public:
	int x=0, y=0;
	float xv=0, yv=0; //momentum
	int width=20, height=24;
	float speed=0.5;
	float jumpHeight=10;
	bool giaSaltato=false;
	sf::RectangleShape shape;
	sf::Text text;
	const int charSize=8;

	Player(GameEngine* game){
		this->shape.setSize(sf::Vector2f(this->width, this->height));
		this->shape.setFillColor(sf::Color(0,64,240,255));
	
		this->text.setCharacterSize(this->charSize);
		this->text.setFillColor(sf::Color::Yellow);
		this->text.setFont(game->font);
	}

	virtual void Physics(GameEngine* game, Livello* level){
		//temp variables
		float speed = this->speed;

		//vertical movement (only with debugMode)
		if(game->keys[0] && game->debugMode){this->yv-=speed;}
		if(game->keys[1] && game->debugMode){this->yv+=speed;}
		
		//horizontal movement
		if(game->keys[2]){this->xv+=speed;}
		if(game->keys[3]){this->xv-=speed;}
		
		//apply movement
		this->xv=this->xv*level->friction;
		this->x+=(int)this->xv;

		//apply gravity
		this->yv+=level->gravity;
		this->y+=(int)this->yv;
		
		//collisions
		Entity playerHitBox = Entity(this->x, this->y, this->width, this->height);
		for(int i=0; i < level->contaEntity; i++){
			//if entity->type = "platform" //da implementare
			switch (CollisionBetween(&playerHitBox, level->entity[i])){
				//horizontal collision
				case 1: 
					this->x=level->entity[i]->x+level->entity[i]->width;
					if(game->keys[4] && !this->giaSaltato){
						if (this->xv > 0) {
							this->xv = -7;
						} else {
							this->xv = 7;
						}
						this->yv=-this->jumpHeight+1;
						this->giaSaltato=true;
					}else{
						this->xv = 0;
					}
					break;
				case 3: 
					this->x=level->entity[i]->x-this->width;
					if(game->keys[4] && !this->giaSaltato){
						if (this->xv > 0) {
							this->xv = -7;
						} else {
							this->xv = 7;
						}
						this->yv=-this->jumpHeight+1;
						this->giaSaltato=true;
					}else{
						this->xv = 0;
					}
					break;
				//vertical collision
				case 2:	
					this->yv = level->gravity;
					this->y = level->entity[i]->y+level->entity[i]->height;
					break;
				case 4: 
					this->y = level->entity[i]->y-this->height+1;
					this->yv = 0;
					if(game->keys[5]){this->xv*=(0.95/level->friction);} //dash
					if(game->keys[4] && !this->giaSaltato){
						this->yv=-this->jumpHeight;
						this->giaSaltato=true;
					} //jump
					break;
				default: //no collision
					break;
			}
		}

		if(!game->keys[4]){
			this->giaSaltato=false;
		}


		if(game->keys[7]){
			Alert* alert = new Alert(game, 16, "You found you can open the menu with     ENTER and ESCAPE? Very nice.            \nHere are some other buttons:            \nMove left   -  ArrowLeft & Numpad4       Move right  -  ArrowRight & Numpad6      Jump        -  Z & Space                 Dash        -  X & LShift");
		}
	} 

	virtual void Render(sf::RenderWindow* window){
		this->shape.setPosition(this->x,this->y-1);
		this->text.setString(("X: "+std::to_string((int)this->x)+"\nY: "+std::to_string((int)this->y)));
		this->text.setPosition(this->x, this->y);
		window->draw(this->shape);
		window->draw(this->text);
	}
};
