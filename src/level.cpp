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
			objState=0; loading=false;
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
	for(int i=0; i < this->contaEntity; i++){ delete this->entity[i]; }
	std::vector<Entity*> nuovoVettore;
	this->entity=nuovoVettore;
	this->contaEntity=0;
}

void Livello::SetProprieties(std::string* tempString){
	this->maxWidth=std::stoi(tempString[1]);
	this->maxHeight=std::stoi(tempString[2]);
	this->gravity=std::stof(tempString[3]);
	this->friction=std::stof(tempString[4]);
	Blocco* newBlocco[4]; //create level borders
	for(int i=0; i<4; i++){
		newBlocco[i] = new Blocco();
		this->contaEntity += newBlocco[i]->Initialize(&this->entity);
		newBlocco[i]->color=sf::Color(255, 255, 0, 255);
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
		newBlocco[i]->UpdateRenderHitbox();
	}
}
std::string Livello::GetProprieties(){
	return "<proprieta;"
	+std::to_string(this->maxWidth)+";"
	+std::to_string(this->maxHeight)+";"
	+std::to_string(this->gravity).erase(std::to_string(this->gravity).find_last_not_of('0')+1, std::string::npos).erase(std::to_string(this->gravity).erase(std::to_string(this->gravity).find_last_not_of('0')+1, std::string::npos).find_last_not_of('.') + 1, std::string::npos)+";"
	+std::to_string(this->friction).erase(std::to_string(this->friction).find_last_not_of('0')+1, std::string::npos).erase(std::to_string(this->friction).erase(std::to_string(this->friction).find_last_not_of('0')+1, std::string::npos).find_last_not_of('.') + 1, std::string::npos)+";"
	+">";
}
//.erase(std::to_string(temp).find_last_not_of('0')+1, std::string::npos).erase(std::to_string(temp).erase(std::to_string(temp).find_last_not_of('0')+1, std::string::npos).find_last_not_of('.') + 1, std::string::npos)+";"
void Livello::SetPlayerInitialPosition(std::string* tempString){
	this->playerStartingPos = sf::Vector2f(std::stoi(tempString[1]), std::stoi(tempString[2]));
	this->player->x = std::stoi(tempString[1]);
	this->player->y = std::stoi(tempString[2]);
}
std::string Livello::GetPlayerInitialPosition(){
	return "<playerStartingPos;"
	+std::to_string(this->playerStartingPos.x).erase(std::to_string(this->playerStartingPos.x).find_last_not_of('0')+1, std::string::npos).erase(std::to_string(this->playerStartingPos.x).erase(std::to_string(this->playerStartingPos.x).find_last_not_of('0')+1, std::string::npos).find_last_not_of('.') + 1, std::string::npos)+";"
	+std::to_string(this->playerStartingPos.y).erase(std::to_string(this->playerStartingPos.y).find_last_not_of('0')+1, std::string::npos).erase(std::to_string(this->playerStartingPos.y).erase(std::to_string(this->playerStartingPos.y).find_last_not_of('0')+1, std::string::npos).find_last_not_of('.') + 1, std::string::npos)+";"
	+">";
}

void Livello::DecodeObj(std::string tempString[32]){
	if(tempString[0] == "proprieta"){
		this->SetProprieties(&tempString[0]);
	}else if(tempString[0] == "playerStartingPos"){
		this->SetPlayerInitialPosition(&tempString[0]);
	}else if(tempString[0] == "blocco"){
		Blocco* newBlocco = new Blocco();
		this->contaEntity += newBlocco->Initialize(&this->entity, &tempString[0]);
	}else if(tempString[0] == "slope"){
		Slope* newSlope = new Slope();
		this->contaEntity += newSlope->Initialize(&this->entity, &tempString[0]);
	}
}

std::string Livello::GenerateLevelString(){
	std::string tempString = this->GetProprieties() + this->GetPlayerInitialPosition();
	for(int i=0; i < this->contaEntity; i++){ tempString += this->entity[i]->SaveToFile(); }
	return tempString;
}
