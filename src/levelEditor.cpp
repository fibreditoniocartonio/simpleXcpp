#include "../inc/gameEngine.hpp"
#include "../inc/textEngine.hpp"
#include "../inc/rendering.hpp"
#include "../inc/physics.hpp"
#include "../inc/player.hpp"
#include "../inc/level.hpp"
#include "../inc/entity.hpp"
#include "../inc/levelEditor.hpp"

Editor::Editor(GameEngine* game){
    this->state = 1;
    this->game = game;
	this->previousGameState=game->gamestate; this->previousMenu=game->currentMenu;
    this->windowWidthEditor=game->windowWidth+(((float)16/(float)9)-((float)game->windowWidth/(float)game->windowHeight))*game->windowHeight;
    this->windowHeightEditor=game->windowHeight;
    this->camera = sf::Vector2f(game->player->x+game->player->width/2, game->player->y+game->player->height/2);
    this->showCameraDot = true;
    this->tastoGiaSchiacciato = true;
    this->alertAspectRatioAlreadyShown = false;
    this->index=0; this->maxIndex=0;
    if (!this->texture.loadFromFile("./res/img/titlescreen/titlescreen.png")){new Alert(this->game, 16, this->game->textEngine->testo[4]+"\n\n./res/img/titlescreen/titlescreen.png");}
    this->texture.setSmooth(false); //do not blur the pixels
    this->sprite.setTexture(this->texture);
    this->InitializeClickableText();
    game->window->setTitle("simpleXcpp - Level Editor");
    game->window->setView(calcViewWhenResized(game->window->getSize(), sf::Vector2u(this->windowWidthEditor, this->windowHeightEditor)));    
    game->ChangeGameState(1000, this);
}
void Editor::InitializeClickableText(){
    //state 0 - main menu
    for(int i=0; i < 3; i++){
        this->textClick.push_back(new Testo(this->game->textEngine->testo[25+i], 80, 140+32*i, 32, sf::Color(63,72,255,255), this->game->font));
    }    
}
void Editor::CloseEditor(){
    for(int i=0; i < this->textClick.size(); i++){ delete (this->textClick[i]); }
    this->game->window->setTitle("simpleXcpp");
    this->game->window->setView(calcViewWhenResized(this->game->window->getSize(), sf::Vector2u(this->game->windowWidth, this->game->windowHeight)));
	this->game->ChangeGameState(this->previousGameState, this->previousMenu);
	delete this;    
}
void Editor::Render(sf::RenderWindow* window){
    switch(this->state){
     case 1: //editor main menu
        this->sprite.setPosition(sf::Vector2f((this->windowWidthEditor-this->game->windowWidth)/2,0));
        window->draw(this->sprite);
        this->testo = sf::Text("LEVEL EDITOR", this->game->font, 28); this->testo.setFillColor(sf::Color(211,128,0,255));
        this->testo.setPosition(sf::Vector2f(245,104));
        window->draw(this->testo);
		for(int i=0; i < this->maxIndex; i++){
            this->textClick[i]->CopyTextIn(&this->testo);
			if(this->index == i){
				this->testo.setFillColor(sf::Color(216,136,0,255));
                this->testo.setString(">"+this->testo.getString());
			}else{
				this->testo.setFillColor(sf::Color(63,72,255,255));
			}
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
        rect.setFillColor(sf::Color::Blue);
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
            rect.setPosition(this->view.getCenter());
            rect.setSize(sf::Vector2f(1, 1));
            window->draw(rect);
        }
        //draw the right part of the screen, the tools menu of the levelEditor
        this->view.setViewport(sf::FloatRect(0.f, 0.f, (this->view.getViewport().width*(16.f/9.f)/(4.f/3.f)), (this->view.getViewport().height*(16.f/9.f)/(4.f/3.f))));
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
    if(!this->alertAspectRatioAlreadyShown && (((float)game->window->getSize().x/(float)game->window->getSize().y > (16.f/9.f)+0.1) || ((float)game->window->getSize().x/(float)game->window->getSize().y < (16.f/9.f)-0.1))){
        this->alertAspectRatioAlreadyShown = true;
        new Alert(game, 16, game->textEngine->testo[33]);
    }
    bool tastiPremuti=false, click=false;
    Entity mouse (this->game->mouse.x, this->game->mouse.y, 1, 1);
    switch(this->state){
     case 1: //level editor main menu
        this->maxIndex = 3;
        //mouse input
        for(int i=0; i<this->maxIndex; i++){
            if(CollisionBetween(this->textClick[i], &mouse)){
                this->index = i;
                if(this->game->mouseClick[0]){
                    click=true; tastiPremuti=true;
                }
            }
        }
        //keyboard/gamepad input
        if(game->keys[4] && !this->tastoGiaSchiacciato){
            this->CloseEditor();
        }
        if((game->keys[5] || game->keys[7] || click) && !this->tastoGiaSchiacciato){
            switch(this->index){
                case 0: //New Level
                    this->game->level->LoadLevel("./levels/test1");
                    this->camera = sf::Vector2f(this->game->player->x+game->player->width/2, this->game->player->y+game->player->height/2);
                    this->state=0;
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