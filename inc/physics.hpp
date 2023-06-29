bool VerifyCollision(Entity* e1, Entity* e2){
	if (e2->x < e1->x + e1->width &&
      		e2->x + e2->width > e1->x &&
      		e2->y < e1->y + e1->height &&
      		e2->y + e2->height > e1->y)
	{
		return true;
      	}else { 
		return false;
	}
}

int CollisionBetween(Entity* e1, Entity* e2){
//returns -1 if no collision, 1 if collision with e1 left side, 2 if e1 upper side, 3 if e1 right side, 4 if e1 bottom side
	int collided = -1;
	Entity e1Sides[4] = {
		Entity(e1->x,e1->y+1,1,e1->height-2),
		Entity(e1->x+1,e1->y,e1->width-2,1),
		Entity(e1->x+e1->width-1,e1->y+1,1,e1->height-2),
		Entity(e1->x+1,e1->y+e1->height-1,e1->width-2,1)
	};
	for (int i=0; i<4; i++){
		if(VerifyCollision(&e1Sides[i], e2)){
			if(collided < 0){
		      		collided=i+1;
			}else{ //if multiple sides collision

			}
	      	}
	}
	return collided;
}

void DoGamePhysics(GameEngine* game, Player* player, Livello* level, sf::RenderWindow* window){
	switch (game->gamestate){
	 case 1:
		break;

	 default: //usually -1, in game
	 	//player physics
		player->Physics(game, level);
		//entity physics
		Entity screen = Entity(window->getView().getCenter().x-game->windowWidth, window->getView().getCenter().y-game->windowHeight, game->windowWidth*2, game->windowHeight*2);
		for(int i=0; i < level->contaEntity; i++){
			if(VerifyCollision(&screen, level->entity[i])){
				level->entity[i]->Physics(player);
			}
		}
		break;
	}//fine dello switch(gamestate)
}
