#include "../inc/player.hpp"
#include "../inc/level.hpp"
#include "../inc/gameEngine.hpp"
#include "../inc/entity.hpp"
#include "../inc/physics.hpp"
#include "../inc/menu.hpp"

Player::Player(GameEngine* game){
		this->width=20; this->height=24;
		this->shape.setSize(sf::Vector2f(this->width, this->height));
		this->shape.setFillColor(sf::Color(0,64,240,255));
	
		this->text.setCharacterSize(this->charSize);
		this->text.setFillColor(sf::Color::Yellow);
		this->text.setFont(game->font);
}

void Player::Physics(GameEngine* game, Livello* level){
		//temp variables
		float speed = this->speed;

		//collisions
		for(int i=0; i < level->contaEntity; i++){
			//if entity->type = "platform" //da implementare
			if(CollisionBetween(this, level->entity[i])){
				//new Alert(game, 16, "entity nr: "+std::to_string(i)+"\nx: "+std::to_string(level->entity[i]->x)+"\ty: "+std::to_string(level->entity[i]->y)+"\nw: "+std::to_string(level->entity[i]->width)+"\th: "+std::to_string(level->entity[i]->height)+"\n\nPlayer:\nx: "+std::to_string(this->x)+"\ty: "+std::to_string(this->y)+"\nw: "+std::to_string(this->width)+"\th:"+std::to_string(this->height));
				
				//solve vertical collision
				this->y += -this->yv;
				this->yv = 0;
				//dash
				if(game->keys[5]){this->xv*=(0.95/level->friction);}
				
				//solve horizontal collision
				if(CollisionBetween(this, level->entity[i])){
					this->x += -this->xv;
					this->xv = 0;
				}
				
				//jump
				if(game->keys[4] && !this->giaSaltato){
					this->yv=-this->jumpHeight;
					this->giaSaltato=true;
				}
			}
		}

		//vertical movement (only with debugMode)
		if(game->keys[0] && game->debugMode){this->yv-=speed;}
		if(game->keys[1] && game->debugMode){this->yv+=speed;}
		
		//horizontal movement
		if(game->keys[2]){this->xv+=speed;}
		if(game->keys[3]){this->xv-=speed;}
		
		//apply movement
		this->xv = this->xv*level->friction;
		this->x += this->xv;

		//apply gravity
		this->yv += level->gravity;
		this->y += this->yv;

		if(!game->keys[4]){
			this->giaSaltato=false;
		}

		if(game->keys[7]){
			Alert* alert = new Alert(game, 16, "You found you can open the menu with ENTER and ESCAPE? Very nice.\n\nHere are some other buttons:\nMove left   -  ArrowLeft & Numpad4\nMove right  -  ArrowRight & Numpad6\nJump        -  Z & Space\nDash        -  X & LShift\n\nYou can even do a walljump by pressing Jump while in contact with a wall.\nNice cock btw");
		}
} 

void Player::Render(sf::RenderWindow* window){
		this->shape.setPosition((int)this->x, (int)this->y);
		this->text.setString(("X: "+std::to_string((int)this->x)+"\nY: "+std::to_string((int)this->y)));
		this->text.setPosition((int)this->x, (int)this->y);
		window->draw(this->shape);
		window->draw(this->text);
}
