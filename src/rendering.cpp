#include "../inc/rendering.hpp"
#include "../inc/player.hpp"
#include "../inc/level.hpp"
#include "../inc/gameEngine.hpp"
#include "../inc/entity.hpp"
#include "../inc/menu.hpp"
#include "../inc/physics.hpp"

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

sf::View calcViewOnPlayerMovement(sf::View view, Player* player, Livello* level, int windowWidth, int windowHeight){
	int xDisegnata, yDisegnata;
	int centerX = player->x+(int)player->width/2;
	int centerY = player->y+(int)player->height/2;
	
	//calculate where is the pixel to draw in the upper left corner
	if (centerX < windowWidth/2){
		xDisegnata = 0;
	} else {
		if (centerX > level->maxWidth-windowWidth/2 ) {
			xDisegnata = level->maxWidth-windowWidth;	
		} else {
			xDisegnata = centerX-windowWidth/2;
		} 
	}
      	
	if (centerY < windowHeight/2){
		yDisegnata = 0;
	} else {
		if (centerY > level->maxHeight-windowHeight/2){
			yDisegnata = level->maxHeight-windowHeight;
		} else {
			yDisegnata = centerY-windowHeight/2;
		}
	}

	//shift the coordinate calculated to the center of the screen because that's what SFML prefer
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
		window->setView(calcViewOnPlayerMovement(window->getView(), player, level, game->windowWidth, game->windowHeight));
		player->Render(window);
		break;
	}//fine dello switch(gamestate)
	window->display();
}
