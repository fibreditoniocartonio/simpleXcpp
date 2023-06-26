#include <string>

#include <SFML/Graphics.hpp>

#include "inc/gameEngine.h"

int main(){
	GameEngine game;
	sf::RenderWindow window(sf::VideoMode(360, 270), "simpleXcpp");
	window.setFramerateLimit(game.frameLimit);
	
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);
	
	sf::Font font;
	if (!font.loadFromFile("res/font/Swanston.ttf")){/*error loading the font*/}
	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(32);
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
		window.draw(shape);
		window.draw(text);
		window.display();
	}

	return 0;
}
