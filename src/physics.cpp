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

void DoGamePhysics(GameEngine* game, Player* player, Livello* level, sf::RenderWindow* window){
	switch (game->gamestate){
	 case 1: static_cast<Alert*>(game->currentMenu)->Physics(game);
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
