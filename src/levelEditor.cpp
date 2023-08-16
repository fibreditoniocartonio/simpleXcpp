#include "../inc/gameEngine.hpp"
#include "../inc/textEngine.hpp"
#include "../inc/rendering.hpp"
#include "../inc/physics.hpp"
#include "../inc/player.hpp"
#include "../inc/level.hpp"
#include "../inc/entity.hpp"
#include "../inc/levelEditor.hpp"

Editor::Editor(GameEngine* game){
    this->state = 0; //0 main editor menu
    this->game = game;
	this->previousGameState=game->gamestate; this->previousMenu=game->currentMenu;
    this->windowWidthEditor=game->windowWidth+(((float)16/(float)9)-((float)game->windowWidth/(float)game->windowHeight))*game->windowHeight;
    this->windowHeightEditor=game->windowHeight;
    this->camera = sf::Vector2f(game->windowWidth/2, game->windowHeight/2);
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
     default:
        window->setView(calcViewWhenResized(this->game->window->getSize(), sf::Vector2u(game->windowWidth, game->windowHeight))); //restore viewport
        //draw the left part of the screen, the level preview
        sf::View editorView = calcViewOnPlayerMovement(window->getView(), this->camera, this->game->level, game->windowWidth, game->windowHeight);
        editorView.setViewport(sf::FloatRect(0.f, 0.f, editorView.getViewport().width, editorView.getViewport().height));
        window->setView(editorView);
        Entity screen = Entity(window->getView().getCenter().x-game->windowWidth/2, window->getView().getCenter().y-game->windowHeight/2, game->windowWidth, game->windowHeight);
        for(int i=0; i < this->game->level->contaEntity; i++){
            if(this->game->level->entity[i]->isActive){
                if(CollisionBetween(&screen, this->game->level->entity[i])){
                    this->game->level->entity[i]->Render(window);
                }
            }
        }
        sf::RectangleShape rect;
        rect.setFillColor(sf::Color::Red);
        rect.setPosition(editorView.getCenter());
        rect.setSize(sf::Vector2f(1, 1));
        window->draw(rect);
        //draw the right part of the screen, the tools menu of the levelEditor
        editorView.setViewport(sf::FloatRect(editorView.getViewport().width, 0.f, (1.f-editorView.getViewport().width), 1.f));
        editorView.setSize(sf::Vector2f((this->windowWidthEditor-this->game->windowWidth), this->windowHeightEditor));
        editorView.setCenter(sf::Vector2f(editorView.getSize().x/2, editorView.getSize().y/2));
        window->setView(editorView);
		rect.setPosition(0, 0);
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
}