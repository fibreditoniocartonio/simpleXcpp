#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

#include "inc/gameVersion.hpp"
#include "inc/gameEngine.hpp"
#include "inc/menu.hpp"
#include "inc/entity.hpp"
#include "inc/level.hpp"
#include "inc/player.hpp"
#include "inc/physics.hpp"
#include "inc/rendering.hpp"

int main(){
	GameEngine game;
	sf::RenderWindow window(sf::VideoMode(game.windowWidth, game.windowHeight), "simpleXcpp");
	window.setFramerateLimit(game.frameLimit);
	window.setView(calcViewWhenResized(window.getSize(), sf::Vector2u(game.windowWidth, game.windowHeight)));

	Livello level;
	level.LoadLevel("<proprieta;1100;300;0.65;0.86><blocco;0;240;360;20;15;52;61;255;><blocco;50;124;60;30;255;52;61;255;><blocco;1000;250;100;50;0;200;255;255;>");
	
	Player player = Player(&game);

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
		DoGamePhysics(&game, &player, &level, &window);

		//Rendering
		RenderGameScreen(&game, &player, &level, &window);
	}
	return 0;
}
