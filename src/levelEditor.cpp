#include "../inc/gameEngine.hpp"
#include "../inc/textEngine.hpp"
#include "../inc/rendering.hpp"
#include "../inc/physics.hpp"
#include "../inc/player.hpp"
#include "../inc/level.hpp"
#include "../inc/entity.hpp"
#include "../inc/levelEditor.hpp"

Editor::Editor(GameEngine* game){
    this->state = 0;
    this->game = game;
	this->previousGameState=game->gamestate; this->previousMenu=game->currentMenu;
    this->windowWidthEditor=game->windowWidth+(((float)16/(float)9)-((float)game->windowWidth/(float)game->windowHeight))*game->windowHeight;
    this->windowHeightEditor=game->windowHeight;
    this->toolsMenuAreaX = this->windowWidthEditor-game->windowWidth;
    this->camera = sf::Vector2f(game->player->x+game->player->width/2, game->player->y+game->player->height/2);
    this->showCameraDot = true;
    this->tastoGiaSchiacciato = true;
    this->index=0; this->maxIndex=0;
    if (!this->texture.loadFromFile("./res/img/titlescreen/titlescreen.png")){new Alert(this->game, 16, this->game->textEngine->testo[4]+"\n\n./res/img/titlescreen/titlescreen.png");}
    this->texture.setSmooth(false); //do not blur the pixels
    this->sprite.setTexture(this->texture);    
    game->window->setTitle("simpleXcpp - Level Editor");
    game->window->setView(calcViewWhenResized(game->window->getSize(), sf::Vector2u(this->windowWidthEditor, this->windowHeightEditor)));    
    game->ChangeGameState(1000, this);
}
void Editor::CloseEditor(){
    this->game->window->setTitle("simpleXcpp");
    this->game->window->setView(calcViewWhenResized(this->game->window->getSize(), sf::Vector2u(this->game->windowWidth, this->game->windowHeight)));
	this->game->ChangeGameState(this->previousGameState, this->previousMenu);
	delete this;    
}
void Editor::Render(sf::RenderWindow* window){
    switch(this->state){
     case 0:
        this->sprite.setPosition(sf::Vector2f((this->windowWidthEditor-this->game->windowWidth)/2,0));
        window->draw(this->sprite);
        this->testo = sf::Text("LEVEL EDITOR", this->game->font, 28); this->testo.setFillColor(sf::Color(211,128,0,255));
        this->testo.setPosition(sf::Vector2f(245,104));
        window->draw(this->testo);
        this->testo.setCharacterSize(32);
		for(int i=0; i < this->maxIndex; i++){
			this->testo.setPosition(sf::Vector2f(80, 140+this->testo.getCharacterSize()*i));
			std::string txtString = " ";
			if(this->index == i){
				this->testo.setFillColor(sf::Color(216,136,0,255));
				txtString = ">";
			}else{
				this->testo.setFillColor(sf::Color(63,72,255,255));
			}
			switch(i){
			 case 0: txtString+=this->game->textEngine->testo[25];
			 	break;
			 case 1: txtString+=this->game->textEngine->testo[26];
			 	break;
			 default: txtString+=this->game->textEngine->testo[27];
			 	break;
			}
			this->testo.setString(txtString);
			window->draw(this->testo);
		}
        this->testo.setCharacterSize(16);
        this->testo.setFillColor(sf::Color::White);
        this->testo.setPosition(sf::Vector2f(0, this->windowHeightEditor-this->testo.getCharacterSize()));
		this->testo.setString(versioneDiGioco);
		window->draw(this->testo);         
        break;
     default:
        sf::RectangleShape rect;
        //draw the left part of the screen, the level preview
        this->view = calcViewOnPlayerMovement(calcViewWhenResized(this->game->window->getSize(), sf::Vector2u(this->game->windowWidth, this->game->windowHeight)), this->camera, this->game->level, game->windowWidth, game->windowHeight);
        this->view.setViewport(sf::FloatRect(0.f, 0.f, this->view.getViewport().width, this->view.getViewport().height));
        window->setView(this->view);
        Entity screen = Entity(window->getView().getCenter().x-game->windowWidth/2, window->getView().getCenter().y-game->windowHeight/2, game->windowWidth, game->windowHeight);
        for(int i=0; i < this->game->level->contaEntity; i++){
            if(this->game->level->entity[i]->isActive){
                if(CollisionBetween(&screen, this->game->level->entity[i])){
                    this->game->level->entity[i]->Render(window);
                }
            }
        }
        if(this->showCameraDot){
            rect.setFillColor(sf::Color::Red);
            rect.setPosition(this->view.getCenter());
            rect.setSize(sf::Vector2f(1, 1));
            window->draw(rect);
        }
        //draw the right part of the screen, the tools menu of the levelEditor
        this->view.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));
        this->view.setSize(sf::Vector2f(this->windowWidthEditor, this->windowHeightEditor));
        this->view.setCenter(sf::Vector2f(this->view.getSize().x/2, this->view.getSize().y/2));
        window->setView(this->view);
		rect.setPosition(this->game->windowWidth, 0);
        rect.setSize(sf::Vector2f(this->windowWidthEditor-this->game->windowWidth, this->windowHeightEditor));
        window->draw(rect);
        break;
    }
}
void Editor::Physics(GameEngine* game){
    sf::Event event; //editor's personal event system, mainly for mouse events
    while (this->game->window->pollEvent(event)){
        if (event.type == sf::Event::Resized){ //reset the view when window is resized
            this->game->window->setView(calcViewWhenResized(this->game->window->getSize(), sf::Vector2u(this->windowWidthEditor, this->windowHeightEditor)));
        }else if (event.type == sf::Event::KeyPressed){
            //game.UpdateKeys(event.key.code, true);
        }else if (event.type == sf::Event::KeyReleased){
            //game.UpdateKeys(event.key.code, false);
        }
    }
    bool tastiPremuti = false;
    switch(this->state){
     case 0: //level editor main menu
        this->maxIndex = 3;
        if(game->keys[4] && !this->tastoGiaSchiacciato){
            this->CloseEditor();
        }
        if((game->keys[5] || game->keys[7]) && !this->tastoGiaSchiacciato){
            switch(this->index){
                case 0: //New Level
                    this->game->level->LoadLevel("./levels/test1");
                    this->camera = sf::Vector2f(this->game->player->x+game->player->width/2, this->game->player->y+game->player->height/2);
                    this->state=-1;
                    break;
                case 1: //Load Level
                    new Alert(this->game, 16, "Not implemented yet");
                    break;
                default: //Return to the game
                    this->CloseEditor();
                    break;
            }
        }
        if(game->keys[0] && !this->tastoGiaSchiacciato){
            this->index--;
        }
        if(game->keys[1] && !this->tastoGiaSchiacciato){
            this->index++;
        }
        if(this->index > this->maxIndex-1){this->index = 0;}
        if(this->index < 0){this->index = this->maxIndex-1;}
        for(int i=0; i<11; i++){ if(game->keys[i]){tastiPremuti=true;} }
        this->tastoGiaSchiacciato=tastiPremuti;        
        break;
     default: //in the level editor
        int speed = 5;
        if(game->keys[5]){speed *= 3;}
        if(game->keys[2]){this->camera.x += speed;}
        if(game->keys[3]){this->camera.x -= speed;}
        if(game->keys[1]){this->camera.y += speed;}
        if(game->keys[0]){this->camera.y -= speed;}
        if(this->camera.x < game->windowWidth/2){this->camera.x=game->windowWidth/2;}
        if(this->camera.x > game->level->maxWidth-game->windowWidth/2){this->camera.x=game->level->maxWidth-game->windowWidth/2;}
        if(this->camera.y < game->windowHeight/2){this->camera.y=game->windowHeight/2;}
        if(this->camera.y > game->level->maxHeight-game->windowHeight/2){this->camera.y=game->level->maxHeight-game->windowHeight/2;}
        if(game->keys[4]){this->CloseEditor();}
        break;
    }
}