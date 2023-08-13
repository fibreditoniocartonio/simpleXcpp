#include "../inc/entity.hpp"
#include "../inc/player.hpp"
#include "../inc/level.hpp"

void Entity::Physics(Player* player) {}
void Entity::Render(sf::RenderWindow* window){}
Entity::~Entity() {}
Entity::Entity (){}
Entity::Entity (float x, float y, int width, int height){
	this->x=x; this->y=y; this->width=width; this->height=height;
}

AABB::AABB(Entity* e1){
    if(e1->xv > 0){
        this->x = e1->x;
    }else{
        this->x = e1->x+e1->xv;
    }
    if(this->yv > 0){
        this->y = e1->y;
    }else{
        this->y = e1->y+e1->yv;
    }
    this->width = e1->width + std::abs(e1->xv); 
    this->height = e1->height + std::abs(e1->yv);
    this->xv = e1->xv;
    this->yv = e1->yv; 
}

void Blocco::CreateHitbox(){
    this->shape.setSize(sf::Vector2f(this->width, this->height));
    this->shape.setPosition(this->x, this->y);
    this->shape.setFillColor(this->color);
}
void Blocco::Render(sf::RenderWindow* window){
	window->draw(shape);
}

void Slope::Initialize(){
    if(this->x1 < this-> x2){this->x = this->x1; }else{ this->x = this->x2;}
    if(this->y1 < this-> y2){this->y = this->y1; }else{ this->y = this->y2;}
    this->width=std::abs(this->x2-this->x1);
    this->height=std::abs(this->y2-this->y1);
    this->coefficienteAngolare = (this->y2-this->y1)/(this->x2-this->x1);
    this->intersezioneQ = this->y1 - this->coefficienteAngolare*this->x1;
    this->shape.setPointCount(3);
    shape.setPoint(0, sf::Vector2f(0, 0));
    shape.setPoint(1, sf::Vector2f((this->x2-this->x1), (this->y2-this->y1)));
    shape.setPoint(2, sf::Vector2f((this->x2-this->x1), 0));
    if((this->y2 - this->y1) < 0){
        if((this->x2 - this->x1) > 0){
            this->slopeType = 0;
        }else{
            this->slopeType = 1;
        }
    }else{ 
        if((this->x2 - this->x1) > 0){
            this->slopeType = 2;
        }else{
            this->slopeType = 3;
        }
    }
    this->shape.setPosition(this->x1, this->y1);
	this->shape.setFillColor(this->color);
}
float Slope::CalculateIntersection(Entity* entity){
    return (this->coefficienteAngolare * (entity->x + entity->width/2) + this->intersezioneQ);
}
void Slope::Render(sf::RenderWindow* window){
	window->draw(shape);
}
