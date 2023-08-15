#include "../inc/player.hpp"
#include "../inc/level.hpp"
#include "../inc/gameEngine.hpp"
#include "../inc/entity.hpp"
#include "../inc/menu.hpp"
#include "../inc/physics.hpp"
#include "../inc/levelEditor.hpp"
#include "../inc/rendering.hpp"

sf::View calcViewWhenResized(const sf::Vector2u &windowsize, const sf::Vector2u &designedsize){
	sf::FloatRect viewport(0.f, 0.f, 1.f, 1.f);
	float screenwidth = windowsize.x / static_cast<float>(designedsize.x);
	float screenheight = windowsize.y / static_cast<float>(designedsize.y);
	if(screenwidth > screenheight){
		viewport.width = screenheight / screenwidth;
		viewport.left = (1.f - viewport.width) / 2.f;
	}
	else if(screenwidth < screenheight){
		viewport.height = screenwidth / screenheight;
		viewport.top = (1.f - viewport.height) / 2.f;
	}
	sf::View view( sf::FloatRect( 0, 0, designedsize.x , designedsize.y ) );
	view.setViewport(viewport);
	return view;
}

sf::View calcViewOnPlayerMovement(sf::View view, sf::Vector2f camera, Livello* level, int windowWidth, int windowHeight){
	int xDisegnata, yDisegnata;
	if (camera.x < windowWidth/2){
		xDisegnata = 0;
	} else {
		if (camera.x > level->maxWidth-windowWidth/2 ) {
			xDisegnata = level->maxWidth-windowWidth;	
		} else {
			xDisegnata = camera.x-windowWidth/2;
		} 
	}	
	if (camera.y < windowHeight/2){
		yDisegnata = 0;
	} else {
		if (camera.y > level->maxHeight-windowHeight/2){
			yDisegnata = level->maxHeight-windowHeight;
		} else {
			yDisegnata = camera.y-windowHeight/2;
		}
	}
	view.setCenter(xDisegnata+windowWidth/2, yDisegnata+windowHeight/2);
	return view;
}


void RenderGameScreen(GameEngine* game, Player* player, Livello* level, sf::RenderWindow* window){
	window->clear();
	switch (game->gamestate){
	 case 1: static_cast<Alert*>(game->currentMenu)->Render(window);
		break;
	 case 2: static_cast<MainMenu*>(game->currentMenu)->Render(window);
		break;        
	 case 3: static_cast<SettingsMenu*>(game->currentMenu)->Render(window);
		break;
	 case 1000: static_cast<Editor*>(game->currentMenu)->Render(window);
		break;		
	 default: //usually -1, in game
		//render level
		Entity screen = Entity(window->getView().getCenter().x-game->windowWidth/2, window->getView().getCenter().y-game->windowHeight/2, game->windowWidth, game->windowHeight);
		for(int i=0; i < level->contaEntity; i++){
			if(level->entity[i]->isActive){
			 if(CollisionBetween(&screen, level->entity[i])){
				level->entity[i]->Render(window);
			 }
			}
		}
		//render player
		window->setView(calcViewOnPlayerMovement(window->getView(), sf::Vector2f(player->x+player->width/2, player->y+player->height/2), level, game->windowWidth, game->windowHeight));
		player->Render(window);
		break;
	}//fine dello switch(gamestate)
	window->display();
}
