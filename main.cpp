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
	game.window = &window;
	window.setFramerateLimit(game.frameLimit);
	window.setView(calcViewWhenResized(window.getSize(), sf::Vector2u(game.windowWidth, game.windowHeight)));
	
	Player player (&game);
	game.player = &player;

	Livello level (&game, &player);
	level.LoadLevel("./levels/test1");
	game.level = &level;

    new MainMenu(&game);
    game.SetLanguage("english.txt"); //read texts from language file

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
				if(game.listenNewKey == 1){ game.BindNewKeyKB(event.key.code);
				}else{ game.UpdateKeys(event.key.code, true);}
			}else if (event.type == sf::Event::KeyReleased){
				game.UpdateKeys(event.key.code, false);

			}else if (event.type == sf::Event::MouseButtonPressed){
				game.UpdateMouseButton(event.mouseButton.button, true);
				game.UpdateMouseCoordinate(sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
				if(event.mouseButton.button == sf::Mouse::Left){ new Alert(&game, 16, "Left\nabsx: "+std::to_string(event.mouseButton.x)+" absy:"+std::to_string(event.mouseButton.y)+"\nwinx: "+std::to_string(game.mouse.x)+" winy:"+std::to_string(game.mouse.y)+"\nviex:"+std::to_string(game.MouseCoordInView(&window.getView()).x)+" viey:"+std::to_string(game.MouseCoordInView(&window.getView()).y)); }
			}else if (event.type == sf::Event::MouseButtonReleased){
				game.UpdateMouseButton(event.mouseButton.button, false);
				game.UpdateMouseCoordinate(sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
			}else if (event.type == sf::Event::MouseMoved){
				game.UpdateMouseCoordinate(sf::Vector2f(event.mouseMove.x, event.mouseMove.y));

			}else if (event.type == sf::Event::JoystickDisconnected){
				new Alert (&game, 16, "Joystick "+std::to_string(event.joystickConnect.joystickId)+" disconnected.\n("+game.joystick.getIdentification(event.joystickConnect.joystickId).name+")\n\nPress any button to resume the game.");
			} else if (event.type == sf::Event::JoystickMoved){
				if(game.listenNewKey == 2){ game.BindNewKeyJS(game.joystickHandler.GetAxisKey(&event));
				}else{ game.UpdateKeysJoystick(game.joystickHandler.GetAxisKey(&event), true);}
			}else if (event.type == sf::Event::JoystickButtonPressed){
				if(game.listenNewKey == 2){ game.BindNewKeyJS(event.joystickButton.button);
				}else{ game.UpdateKeysJoystick(event.joystickButton.button, true);}
			}else if (event.type == sf::Event::JoystickButtonReleased){
				game.UpdateKeysJoystick(event.joystickButton.button, false);
			}                                                
       	}
		//Physics
		DoGamePhysics(&game, &player, &level, &window); 
		//Rendering
		RenderGameScreen(&game, &player, &level, &window);
	}
	return 0;
}
