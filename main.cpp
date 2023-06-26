#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

#include "inc/gameEngine.h"
#include "inc/gameVersion.h"
#include "inc/physics.h"
#include "inc/level.h"

int main(){
	GameEngine game;
	sf::RenderWindow window(sf::VideoMode(game.windowWidth, game.windowHeight), "simpleXcpp");
	window.setFramerateLimit(game.frameLimit);
	
	Level level("blocco;0;240;360;20;15;52;61;255;\\nblocco;50;124;60;30;255;52;61;255;\\nblocco;1000;250;100;50;0;200;255;255;\\n");
	
	sf::CircleShape shape(32.f);
	shape.setFillColor(sf::Color::Green);
	
	sf::Font font;
	if(!font.loadFromFile("res/font/Swanston.ttf")){/*error loading the font*/}
	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(16);
	text.setFillColor(sf::Color::Red);
	text.move(shape.getRadius()/2, shape.getRadius()/2);

	//game loop
	while (window.isOpen()){
		//read events
		sf::Event event;
		while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed){
				window.close();
			}
			//read input events
			if (event.type == sf::Event::KeyPressed){
				game.updateKeys(event.key.code, true);
			}
			if (event.type == sf::Event::KeyReleased){
				game.updateKeys(event.key.code, false);
			}
        	}
		
		//testing input
		int x=0, y=0, speed=10;
		if(game.keys[5]){speed*=2;}
		if(game.keys[0]){y=-speed;}
		if(game.keys[1]){y=+speed;}
		if(game.keys[2]){x=+speed;}
		if(game.keys[3]){x=-speed;}
		shape.move(x,y);
		text.move(x,y);
		text.setString(("X: "+std::to_string((int)text.getPosition().x)+"\nY: "+std::to_string((int)text.getPosition().y)));

		//rendering
		window.clear();
		//render player
		window.draw(shape);
		window.draw(text);
		//render level
		for(int i=0; i<level.contaEntity; i++){
			window.draw(level.entity[i].renderHitbox());
		}
		window.display();
	}

	return 0;
}
