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
		//horizontal movement
		if(game->keys[2]){this->xv += this->speed;}
		if(game->keys[3]){this->xv -= this->speed;}
		
        //apply gravity
		this->yv += level->gravity;     
        
		//apply friction
		this->xv = this->xv*level->friction;
        
		//collisions
        AABB playerAABB (this);
		for(int i=0; i < level->contaEntity; i++){
			if(level->entity[i]->id == "blocco"){
				if(CollisionBetween(&playerAABB, level->entity[i])){ //collision may happened or may not
					int collisionSide = ResolveCollision(this, level->entity[i]); 
					if (collisionSide > 0){ //collision happened fr fr
						if(game->keys[5]){ //dash
							this->speed = this->speedDefault*2;
						}else{
							this->speed = this->speedDefault;
						}
						if(game->keys[4] && !this->giaSaltato){ //jump
							this->giaSaltato=true;
							if(this->yv != 0 && (game->keys[2] || game->keys[3])){ //walljump
								if(game->keys[2]){
									this->xv = -(this->speed*12);
								}else if(game->keys[3]){
									this->xv = this->speed*12;
								}
							}
							this->yv = -this->jumpHeight;
						}
						playerAABB = AABB(this); //updated because player momentum changed in ResolveCollision()
					}
				}
			}else if(level->entity[i]->id == "slope"){
				if(CollisionBetween(&playerAABB, level->entity[i])){ 
					if(static_cast<Slope*>(level->entity[i])->slopeType<2 && this->yv >= 0 && (this->y+this->height+this->yv > static_cast<Slope*>(level->entity[i])->CalculateIntersection(this))|| (static_cast<Slope*>(level->entity[i])->slopeType>1 && this->yv <= 0)){
						if(CollisionBetween(this, level->entity[i])){
							ResolveSlopeCollision(this, static_cast<Slope*>(level->entity[i]));
							if(game->keys[5]){ //dash
								this->speed = this->speedDefault*2;
							}else{
								this->speed = this->speedDefault;
							}
							if(game->keys[4] && !this->giaSaltato){ //jump
								this->giaSaltato=true;
								if(this->yv != 0 && (game->keys[2] || game->keys[3])){ //walljump
									if(game->keys[2]){
										this->xv = -(this->speed*12);
									}else if(game->keys[3]){
										this->xv = this->speed*12;
									}
								}
								this->yv = -this->jumpHeight;
							}
							playerAABB = AABB(this); //updated because player momentum changed in ResolveCollision()
							i+=2; //skip the 2 block related to the slope
						}
					}
				}
			}
		}
        
    //apply movement     
    this->x += this->xv;
	this->y += this->yv;      
        
	if(!game->keys[4]){
		this->giaSaltato=false;
	}

	if(game->keys[7]){
        new SettingsMenu(game);
	}
} 

void Player::Render(sf::RenderWindow* window){
	this->shape.setPosition((int)this->x, (int)this->y);
    window->draw(this->shape);
	//this->text.setString(("X: "+std::to_string((int)this->x)+"\tY: "+std::to_string((int)this->y)+"\nXV: "+std::to_string(this->xv)+"\tYV: "+std::to_string(this->yv)));
    //this->text.setPosition((int)this->x, (int)this->y-16);
	//window->draw(this->text);
}
