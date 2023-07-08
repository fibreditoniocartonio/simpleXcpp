#include "../inc/physics.hpp"
#include "../inc/player.hpp"
#include "../inc/level.hpp"
#include "../inc/gameEngine.hpp"
#include "../inc/entity.hpp"
#include "../inc/menu.hpp"

bool CollisionBetween(Entity* e1, Entity* e2){
	if(
		e1->x+e1->width > e2->x &&
		e1->x < e2->x+e2->width &&
		e1->y+e1->height > e2->y &&
		e1->y < e2->y+e2->height
	){
		return true;
	} else {
		return false;
	}
}

int ResolveCollision(Entity* entity, Entity* obstacle){
    //thanks to https://youtu.be/watch?v=7ASnv0y2pGU that made me understand the AABB way
    float xEntry, yEntry, xEntryTime, yEntryTime; 
    float xExit, yExit, xExitTime, yExitTime;
    if(entity->xv > 0){
        xEntry = obstacle->x - (entity->x + entity->width);
        xExit = (obstacle->x + obstacle->width) - entity->x;
    }else{
        xEntry = entity->x - (obstacle->x + obstacle->width);
        xExit = (entity->x + entity->width) - obstacle->x;  
    }
    xEntryTime = std::abs(xEntry / entity->xv);
    xExitTime = std::abs(xExit / entity->xv);    
    if(entity->yv > 0){
        yEntry = obstacle->y - (entity->y + entity->height);
        yExit = (obstacle->y + obstacle->height) - entity->y;

    }else{
        yEntry = entity->y - (obstacle->y + obstacle->height);
        yExit = (entity->y + entity->height) - obstacle->y;      
    }
    yEntryTime = std::abs(yEntry / entity->yv);
    yExitTime = std::abs(yExit / entity->yv);      
    
    if(xExitTime < xEntryTime && yExitTime < yEntryTime){
        //there was no collision
        return -1;
    }else{

        if(xEntryTime < yEntryTime){
            //vertical axis collision (x)
            entity->x += xEntry;           
            entity->xv = 0;
            return 1;
        }else{
            //horizontal axis collision (y)
            entity->y += yEntry;
            entity->yv = 0;
            return 2;
        }
    }
}

void DoGamePhysics(GameEngine* game, Player* player, Livello* level, sf::RenderWindow* window){
	switch (game->gamestate){
	 case 1: static_cast<Alert*>(game->currentMenu)->Physics(game);
		break;
	 case 3: static_cast<SettingsMenu*>(game->currentMenu)->Physics(game);
		break;
	 default: //usually -1, in game
	 	//player physics
		player->Physics(game, level);
		//entity physics
		Entity screen = Entity(window->getView().getCenter().x-game->windowWidth, window->getView().getCenter().y-game->windowHeight, game->windowWidth*2, game->windowHeight*2);
		for(int i=0; i < level->contaEntity; i++){
			if(level->entity[i]->isActive){
			if(CollisionBetween(&screen, level->entity[i])){
				level->entity[i]->Physics(player);
			}
			}
		}
		break;
	}//fine dello switch(gamestate)
}
