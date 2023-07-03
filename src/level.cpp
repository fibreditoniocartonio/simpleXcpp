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
		}
	}