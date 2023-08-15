#include "../inc/player.hpp"
#include "../inc/level.hpp"
#include "../inc/entity.hpp"

void Entity::Physics(Player* player) {}
void Entity::Render(sf::RenderWindow* window){}
std::string Entity::SaveToFile(){return "";}
Entity::~Entity() {}
Entity::Entity (){}
Entity::Entity (float x, float y, int width, int height){ this->x=x; this->y=y; this->width=width; this->height=height;}

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

//Blocco
int Blocco::Initialize(std::vector<Entity*> *entity){
    std::string tempString[] = {"blocco", "0", "0", "0", "0", std::to_string(this->color.r), std::to_string(this->color.g), std::to_string(this->color.b), std::to_string(this->color.a), "1"};
    this->Initialize(entity, &tempString[0]);
    return 1;
}
int Blocco::Initialize(std::vector<Entity*> *entity, std::string* tempString){
    this->id=tempString[0];
    this->x=std::stoi(tempString[1]);
    this->y=std::stoi(tempString[2]);
    this->width=std::stoi(tempString[3]);
    this->height=std::stoi(tempString[4]);
    this->color = sf::Color(std::stoi(tempString[5]), std::stoi(tempString[6]), std::stoi(tempString[7]), std::stoi(tempString[8]));
    this->skipOnSave = std::stoi(tempString[9]);
    this->shape.setSize(sf::Vector2f(this->width, this->height));
    this->shape.setPosition(this->x, this->y);
    this->shape.setFillColor(this->color);
    entity->push_back(this);
    return 1;
}
void Blocco::UpdateRenderHitbox(){ this->shape.setPosition(this->x, this->y); this->shape.setSize(sf::Vector2f(this->width, this->height)); this->shape.setFillColor(this->color); }
std::string Blocco::SaveToFile(){
    if(this->skipOnSave == 0){
        return "<"
        +this->id+";"
        +std::to_string(this->x).erase(std::to_string(this->x).find_last_not_of('0')+1, std::string::npos).erase(std::to_string(this->x).erase(std::to_string(this->x).find_last_not_of('0')+1, std::string::npos).find_last_not_of('.') + 1, std::string::npos)+";"
        +std::to_string(this->y).erase(std::to_string(this->y).find_last_not_of('0')+1, std::string::npos).erase(std::to_string(this->y).erase(std::to_string(this->y).find_last_not_of('0')+1, std::string::npos).find_last_not_of('.') + 1, std::string::npos)+";"
        +std::to_string(this->width)+";"
        +std::to_string(this->height)+";"
        +std::to_string(this->color.r)+";"+std::to_string(this->color.g)+";"+std::to_string(this->color.b)+";"+std::to_string(this->color.a)+";"
        +std::to_string(this->skipOnSave)+";"
        +">";
    }else{ return ""; }
}
void Blocco::Render(sf::RenderWindow* window){ window->draw(shape); }

//Slope
int Slope::Initialize(std::vector<Entity*> *entity, std::string* tempString){
    this->id=tempString[0];
    this->x1=std::stoi(tempString[1]);
    this->y1=std::stoi(tempString[2]);
    this->x2=std::stoi(tempString[3]);
    this->y2=std::stoi(tempString[4]);
    this->color = sf::Color(std::stoi(tempString[5]), std::stoi(tempString[6]), std::stoi(tempString[7]), std::stoi(tempString[8]));  
    if(this->x1 < this-> x2){this->x = this->x1; }else{ this->x = this->x2;}
    if((this->y2 - this->y1) < 0){
        this->y = this->y2;
        if((this->x2 - this->x1) > 0){
            this->slopeType = 0;
        }else{
            this->slopeType = 1;
        }
    }else{
        this->y = this->y1; 
        if((this->x2 - this->x1) > 0){
            this->slopeType = 2;
        }else{
            this->slopeType = 3;
        }
    }    
    this->width=std::abs(this->x2-this->x1); this->height=std::abs(this->y2-this->y1);
    this->coefficienteAngolare = (this->y2-this->y1)/(this->x2-this->x1); //y = mx+q
    this->intersezioneQ = this->y1 - this->coefficienteAngolare * this->x1;
    this->shape.setPointCount(3);
    shape.setPoint(0, sf::Vector2f(0, 0));
    shape.setPoint(1, sf::Vector2f((this->x2-this->x1), (this->y2-this->y1)));
    shape.setPoint(2, sf::Vector2f((this->x2-this->x1), 0));
    this->shape.setPosition(this->x1, this->y1);
	this->shape.setFillColor(this->color);
    entity->push_back(this);
    Blocco* newBlocco1 = new Blocco(); Blocco* newBlocco2 = new Blocco();
    newBlocco1->Initialize(entity); newBlocco2->Initialize(entity);
    newBlocco1->color = this->color; newBlocco2->color = this->color;
    switch (this->slopeType){
        case 0:
            newBlocco1->x=this->x+this->width/15; newBlocco1->y=this->y+this->height-1; newBlocco1->width=this->width-this->width/15; newBlocco1->height=1;
            newBlocco2->x=this->x+this->width-1; newBlocco2->y=this->y+this->height/15; newBlocco2->width=1; newBlocco2->height=this->height-this->height/15;
            break;
        case 1:
            newBlocco1->x=this->x; newBlocco1->y=this->y+this->height-1; newBlocco1->width=this->width-this->width/15; newBlocco1->height=1;
            newBlocco2->x=this->x; newBlocco2->y=this->y+this->height/15; newBlocco2->width=1; newBlocco2->height=this->height-this->height/15;			
            break;
        case 2:
            newBlocco1->x=this->x+this->width/15; newBlocco1->y=this->y; newBlocco1->width=this->width-this->width/15; newBlocco1->height=1;
            newBlocco2->x=this->x+this->width-1; newBlocco2->y=this->y; newBlocco2->width=1; newBlocco2->height=this->height-this->height/15;			
            break;
        default:
            newBlocco1->x=this->x; newBlocco1->y=this->y; newBlocco1->width=this->width-this->width/15; newBlocco1->height=1;
            newBlocco2->x=this->x; newBlocco2->y=this->y; newBlocco2->width=1; newBlocco2->height=this->height-this->height/15;				
            break;
    }
    newBlocco1->UpdateRenderHitbox(); newBlocco2->UpdateRenderHitbox();
    return 3; //3 new entity added to the array
}
float Slope::CalculateIntersection(Entity* entity){ return (this->coefficienteAngolare * (entity->x + entity->width/2) + this->intersezioneQ); }
std::string Slope::SaveToFile(){
    return "<"
    +this->id+";"
    +std::to_string(this->x1).erase(std::to_string(this->x1).find_last_not_of('0')+1, std::string::npos).erase(std::to_string(this->x1).erase(std::to_string(this->x1).find_last_not_of('0')+1, std::string::npos).find_last_not_of('.') + 1, std::string::npos)+";"
    +std::to_string(this->y1).erase(std::to_string(this->y1).find_last_not_of('0')+1, std::string::npos).erase(std::to_string(this->y1).erase(std::to_string(this->y1).find_last_not_of('0')+1, std::string::npos).find_last_not_of('.') + 1, std::string::npos)+";"
    +std::to_string(this->x2).erase(std::to_string(this->x2).find_last_not_of('0')+1, std::string::npos).erase(std::to_string(this->x2).erase(std::to_string(this->x2).find_last_not_of('0')+1, std::string::npos).find_last_not_of('.') + 1, std::string::npos)+";"
    +std::to_string(this->y2).erase(std::to_string(this->y2).find_last_not_of('0')+1, std::string::npos).erase(std::to_string(this->y2).erase(std::to_string(this->y2).find_last_not_of('0')+1, std::string::npos).find_last_not_of('.') + 1, std::string::npos)+";"
    +std::to_string(this->color.r)+";"+std::to_string(this->color.g)+";"+std::to_string(this->color.b)+";"+std::to_string(this->color.a)+";"
    +">";
}
void Slope::Render(sf::RenderWindow* window){ window->draw(shape); }

