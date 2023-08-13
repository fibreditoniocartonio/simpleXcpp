#include "../inc/level.hpp"
#include "../inc/gameEngine.hpp"
#include "../inc/entity.hpp"
#include "../inc/player.hpp"
#include "../inc/menu.hpp"

Livello::Livello(GameEngine* game, Player* player){
	this->game = game;
	this->player = player;
}

void Livello::LoadLevel(std::string filePath){
	int objState=0;
	std::string stringaLivello="";
	std::string tempString[32];

	//open the file containing the new level
	std::fstream fileLivello(filePath);
	if(!fileLivello.is_open()){
		Alert* alert = new Alert(game, 16, "Error while opening the file at:\n"+filePath); 
	}else{
		this->currentLevelFile=filePath;
		while(fileLivello){
			stringaLivello += fileLivello.get();
		} //Alert* alert = new Alert(game, 16, stringaLivello); //show the string read from the file
	}
	fileLivello.close();

	//clean from previous level
	this->CleanLevel();

	//cicle the string to decode it
	bool loading = false;
	for (int i=0; i<stringaLivello.length(); i++){
		if(stringaLivello[i]=='>'){ //decode obj and start again with the next one
			this->DecodeObj(tempString);
			for(int j=0; j<32; j++){tempString[j]="";}
			objState=0;
			loading=false;
		}else if(stringaLivello[i]==';'){ //next param
			objState++;
		}else if(stringaLivello[i]=='<'){ //start loading
			loading = true;
		}else{
			if(loading){
				tempString[objState]+=stringaLivello[i];
			}
		}
	}
}

void Livello::CleanLevel(){
	for(int i=0; i < this->contaEntity; i++){
		delete this->entity[i];
	}
	std::vector<Entity*> nuovoVettore;
	this->entity=nuovoVettore;
	this->contaEntity=0;
}

void Livello::DecodeObj(std::string tempString[32]){
	if(tempString[0] == "proprieta"){
		this->maxWidth=std::stoi(tempString[1]);
		this->maxHeight=std::stoi(tempString[2]);
		this->gravity=std::stof(tempString[3]);
		this->friction=std::stof(tempString[4]);
		Blocco* newBlocco[4]; //create level borders
		for(int i=0; i<4; i++){
			newBlocco[i] = new Blocco();
			newBlocco[i]->id="blocco";
			newBlocco[i]->color=sf::Color(255, 255, 0, 255);
			//newBlocco[i]->color=sf::Color(0, 0, 0, 0); //invisible level borders
			switch (i){
				case 0: newBlocco[i]->x=-100;
					newBlocco[i]->y=-100;
					newBlocco[i]->width=this->maxWidth+100;
					newBlocco[i]->height=100;
					break;
				case 1: newBlocco[i]->x=-100;
					newBlocco[i]->y=-100;
					newBlocco[i]->width=100;
					newBlocco[i]->height=this->maxHeight+100;
					break;
				case 2: newBlocco[i]->x=-100;
					newBlocco[i]->y=this->maxHeight;
					newBlocco[i]->width=this->maxWidth+100;
					newBlocco[i]->height=100;
					break;
				default: newBlocco[i]->x=this->maxWidth;
					newBlocco[i]->y=-100;
					newBlocco[i]->width=100;
					newBlocco[i]->height=this->maxHeight+100;
					break;
			}
			newBlocco[i]->CreateHitbox();
			this->entity.push_back(newBlocco[i]);
		}
		this->contaEntity+=4;

	}else if(tempString[0] == "playerStartingPos"){
		this->player->x = std::stoi(tempString[1]);
		this->player->y = std::stoi(tempString[2]);

	}else if(tempString[0] == "blocco"){
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
		newBlocco->CreateHitbox();
		this->entity.push_back(newBlocco);
		this->contaEntity++;
	}else if(tempString[0] == "slope"){
		Slope* newSlope = new Slope();
		newSlope->id=tempString[0];
		newSlope->x1=std::stoi(tempString[1]);
		newSlope->y1=std::stoi(tempString[2]);
		newSlope->x2=std::stoi(tempString[3]);
		newSlope->y2=std::stoi(tempString[4]);
		newSlope->color.r=std::stoi(tempString[5]);
		newSlope->color.g=std::stoi(tempString[6]);
		newSlope->color.b=std::stoi(tempString[7]);
		newSlope->color.a=std::stoi(tempString[8]);
		newSlope->Initialize();
		this->entity.push_back(newSlope);
		Blocco* newBlocco1 = new Blocco();
		Blocco* newBlocco2 = new Blocco();
		newBlocco1->id="blocco"; newBlocco2->id="blocco";
		newBlocco1->color=newSlope->color; newBlocco2->color=newSlope->color;
		switch (newSlope->slopeType){
			case 0:
				newBlocco1->x=newSlope->x+newSlope->width/15; newBlocco1->y=newSlope->y+newSlope->height-1; newBlocco1->width=newSlope->width-newSlope->width/15; newBlocco1->height=1;
				newBlocco2->x=newSlope->x+newSlope->width-1; newBlocco2->y=newSlope->y+newSlope->height/15; newBlocco2->width=1; newBlocco2->height=newSlope->height-newSlope->height/15;
				break;
			case 1:
				newBlocco1->x=newSlope->x; newBlocco1->y=newSlope->y+newSlope->height-1; newBlocco1->width=newSlope->width-newSlope->width/15; newBlocco1->height=1;
				newBlocco2->x=newSlope->x; newBlocco2->y=newSlope->y+newSlope->height/15; newBlocco2->width=1; newBlocco2->height=newSlope->height-newSlope->height/15;			
				break;
			case 2:
				newBlocco1->x=newSlope->x+newSlope->width/15; newBlocco1->y=newSlope->y; newBlocco1->width=newSlope->width-newSlope->width/15; newBlocco1->height=1;
				newBlocco2->x=newSlope->x+newSlope->width-1; newBlocco2->y=newSlope->y; newBlocco2->width=1; newBlocco2->height=newSlope->height-newSlope->height/15;			
				break;
			default:
				newBlocco1->x=newSlope->x; newBlocco1->y=newSlope->y; newBlocco1->width=newSlope->width-newSlope->width/15; newBlocco1->height=1;
				newBlocco2->x=newSlope->x; newBlocco2->y=newSlope->y; newBlocco2->width=1; newBlocco2->height=newSlope->height-newSlope->height/15;				
				break;
		}
		newBlocco1->CreateHitbox(); newBlocco2->CreateHitbox();
		this->entity.push_back(newBlocco1); this->entity.push_back(newBlocco2);
		this->contaEntity+=3;
	}
}
