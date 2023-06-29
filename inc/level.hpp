class Player;

class Livello {
 public:
 	//vettore di entita'
	std::vector<Entity*> entity;
	int contaEntity;
	int maxWidth, maxHeight;
	float gravity, friction;

	//Decoder
	void LoadLevel(std::string stringaLivello){
		void DecodeObj(Livello* level, std::string tempString[32]);
		int objState=0;
		this->contaEntity=0;
		std::string tempString[32];
		//cicle the string to decode it
		bool loading = false;
		for (int i=0; i<stringaLivello.length(); i++){
			if(stringaLivello[i]=='>'){ //decode obj and start again with the next one
				DecodeObj(this, tempString);
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

	//distruttore
	void CleanLevel(){
		for(int i=0; i<this->contaEntity; i++){
			delete this->entity[i];
		}
		this->contaEntity=0;
	}
};

void DecodeObj(Livello* level, std::string tempString[32]){
	if(tempString[0] == "proprieta"){
		level->maxWidth=std::stoi(tempString[1]);
		level->maxHeight=std::stoi(tempString[2]);
		level->gravity=std::stof(tempString[3]);
		level->friction=std::stof(tempString[4]);
		Blocco* newBlocco[4]; //create level borders
		for(int i=0; i<4; i++){
			newBlocco[i] = new Blocco();
			newBlocco[i]->id="blocco";
			newBlocco[i]->color=sf::Color(255, 255, 0, 255);
			//newBlocco[i]->color=sf::Color(0, 0, 0, 0); //invisible level borders
			switch (i){
				case 0: newBlocco[i]->x=-1;
					newBlocco[i]->y=-1;
					newBlocco[i]->width=level->maxWidth+1;
					newBlocco[i]->height=1;
					break;
				case 1: newBlocco[i]->x=-1;
					newBlocco[i]->y=-1;
					newBlocco[i]->width=1;
					newBlocco[i]->height=level->maxHeight+1;
					break;
				case 2: newBlocco[i]->x=-1;
					newBlocco[i]->y=level->maxHeight;
					newBlocco[i]->width=level->maxWidth+1;
					newBlocco[i]->height=1;
					break;
				default: newBlocco[i]->x=level->maxWidth;
					newBlocco[i]->y=-1;
					newBlocco[i]->width=1;
					newBlocco[i]->height=level->maxHeight+1;
					break;
			}
			newBlocco[i]->CreateHitbox();
			level->entity.push_back(newBlocco[i]);
		}
		level->contaEntity+=4;

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
		level->entity.push_back(newBlocco);
		level->contaEntity++;
	}
}
