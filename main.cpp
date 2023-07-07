#include <string>
#include <vector>
#include <fstream> 

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
	
	Player player (&game);

	Livello level (&game, &player);
	level.LoadLevel("./levels/test1");

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
			}else if (event.type == sf::Event::KeyReleased){
				game.updateKeys(event.key.code, false);
			}else if (event.type == sf::Event::JoystickDisconnected){
				new Alert (&game, 16, "Joystick "+std::to_string(event.joystickConnect.joystickId)+" disconnected.\n("+game.joystick.getIdentification(event.joystickConnect.joystickId).name+")\n\nPress any button to resume the game.");
			} else if (event.type == sf::Event::JoystickMoved){
				game.updateKeysJoystick(game.joystickHandler.GetAxisKey(&event), true);
			}else if (event.type == sf::Event::JoystickButtonPressed){
				game.updateKeysJoystick(event.joystickButton.button, true);
			}else if (event.type == sf::Event::JoystickButtonReleased){
				game.updateKeysJoystick(event.joystickButton.button, false);
			}                                                
       	}

		//Rendering
		RenderGameScreen(&game, &player, &level, &window);
        
		//Physics
		DoGamePhysics(&game, &player, &level, &window);        
	}
	return 0;
}
