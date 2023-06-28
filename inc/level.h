class Entity {
 public:
	int x, y, width, height;
	std::string id;
	sf::Color color;
	virtual void Physics() {}
	virtual sf::RectangleShape RenderHitbox(){
		sf::RectangleShape rectangle(sf::Vector2f(width, height));
		return rectangle;}
	virtual ~Entity() {}
};

class Blocco : public Entity{
 public:
	void Physics() override{}
	sf::RectangleShape RenderHitbox() override{
		sf::RectangleShape rectangle(sf::Vector2f(width, height));
		rectangle.setPosition(x, y);
		rectangle.setFillColor(color);
		return rectangle;
	}
};

class Level {
 public:
 	//vettore di entita'
	std::vector<Entity*> entity;
	int contaEntity;

	//costruttore e decoder
	Level(std::string stringaLivello){
		void DecodeObj(std::vector<Entity*>* puntaEntity, std::string tempString[32]);
		int objState=0;
		contaEntity=0;
		std::string tempString[32];
		//cicle the string to decode it
		for (int i=0; i<stringaLivello.length(); i++){
			if(stringaLivello[i]=='\\' && stringaLivello[i+1]=='n'){ //decode obj and start again with the next one
				DecodeObj(&entity, tempString);
				contaEntity++;
				for(int j=0; j<32; j++){tempString[j]="";}
				objState=0;
				i++;
			}else if(stringaLivello[i]==';'){ //next param
				objState++;
			}else{
				tempString[objState]+=stringaLivello[i];
			}
		}
	}

	//distruttore
	void CleanLevel(){
		for(int i=0; i<this->contaEntity; i++){
			delete this->entity[i];
		}
		this->contaEntity = 0;
	}
};

void DecodeObj(std::vector<Entity*>* puntaEntity, std::string tempString[32]){
	if(tempString[0] == "blocco"){
		Blocco* newBlocco = new Blocco();
		newBlocco->id=tempString[0];
		newBlocco->x=std::stoi(tempString[1]);
		newBlocco->y=std::stoi(tempString[2]);
		newBlocco->width=std::stoi(tempString[3]);
		newBlocco->height=std::stoi(tempString[4]);
		newBlocco->color.r=std::stoi(tempString[5]);
		newBlocco->color.g=std::stoi(tempString[6]);
		newBlocco->color.b=std::stoi(tempString[7]);
		newBlocco->color.a=std::stoi(tempString[8]);
		puntaEntity->push_back(newBlocco);
	}
}
