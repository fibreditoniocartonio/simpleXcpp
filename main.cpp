#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

#include "inc/gameEngine.h"
#include "inc/gameVersion.h"
#include "inc/level.h"
#include "inc/player.h"
#include "inc/camera.h"
#include "inc/physics.h"

int main(){
	GameEngine game;
	sf::RenderWindow window(sf::VideoMode(game.windowWidth, game.windowHeight), "simpleXcpp");
	window.setFramerateLimit(game.frameLimit);
	window.setView(calcViewWhenResized(window.getSize(), sf::Vector2u(game.windowWidth, game.windowHeight)));

	Livello level;
	level.LoadLevel("proprieta;1100;500;0.62;0.85\\nblocco;0;240;360;20;15;52;61;255;\\nblocco;50;124;60;30;255;52;61;255;\\nblocco;1000;250;100;50;0;200;255;255;\\n");
	
	Player player;

	//game loop
	while (window.isOpen()){
		//read events
		sf::Event event;
		while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed){
				window.close();
			}
			if (event.type == sf::Event::Resized){ //reset the view when window is resized
				window.setView(calcViewWhenResized(window.getSize(), sf::Vector2u(game.windowWidth, game.windowHeight)));
			}
			//read input events
			if (event.type == sf::Event::KeyPressed){
				game.updateKeys(event.key.code, true);
			}
			if (event.type == sf::Event::KeyReleased){
				game.updateKeys(event.key.code, false);
			}
        	}
		
		//Physics
		player.Physics(&game, &level);

		//Rendering
		//window.clear();
		window.clear(sf::Color(0,0,50,255));

		//render player
		player.Render(&window);
		if(game.gamestate==-1){ //when in game move the camera following the player
			window.setView(calcViewOnPlayerMovement(window.getView(), &player, &level, game.windowWidth, game.windowHeight));
		}

		//render level
		for(int i=0; i<level.contaEntity; i++){
			level.entity[i]->Render(&window);
		}
		window.display();
	}

	return 0;
}
