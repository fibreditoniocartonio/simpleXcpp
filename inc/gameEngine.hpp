class GameEngine {
 public:
	bool debugMode = false;
	const int frameLimit = 60;
	const int windowWidth=360, windowHeight=270;
	
	int gamestate = -1;
	//stato -1: in partita
	//stato 0: nel menu principale - var nelMenuPrincipale=true; 
	//stato 1: selezione del livello - var stageSelection=false; 
	//stato 2: menu di pausa - var menuDiPausa=false; 
	//stato 3: menu opzioni - var nelMenuOpzioni=false; 
	//stato 4: opzioni nelle stage selection - var nelleOpzioniStageSelect=false; 
	//stato 5: c'e' un alert aperto - var alertAperto=false; 
	//stato 6: nel menu carica partita - var nelMenuCaricaPartita=false; 
	//stato 7: menu Mappa - map menu

	//input key settings
	int ultimoTastoLetto;
	bool keys[11]={
		false, //0 = su
		false, //1 = giu
		false, //2 = destra
		false, //3 = sinistra
		false, //4 = jump 
		false, //5 = dash
		false, //6 = sparo
		false, //7 = start
		false, //8 = map 
		false, //9 = l
		false  //10= r
	};
	sf::Keyboard::Key keySettings[11][2]={
 		{sf::Keyboard::Up,	sf::Keyboard::Numpad8},
	 	{sf::Keyboard::Down,	sf::Keyboard::Numpad5},
	 	{sf::Keyboard::Right,	sf::Keyboard::Numpad6},
	 	{sf::Keyboard::Left,	sf::Keyboard::Numpad4},
	 	{sf::Keyboard::Z,	sf::Keyboard::Space},
	 	{sf::Keyboard::X,	sf::Keyboard::LShift},
	 	{sf::Keyboard::A,	sf::Keyboard::LControl},
	 	{sf::Keyboard::Enter,	sf::Keyboard::Escape},
	 	{sf::Keyboard::RShift,	sf::Keyboard::M},
	 	{sf::Keyboard::D,	sf::Keyboard::L},
	 	{sf::Keyboard::C,	sf::Keyboard::R}
	};
	void updateKeys(sf::Keyboard::Key keyInput, bool isPressed){
		for (int keyIndex=0; keyIndex < sizeof(keys)/sizeof(bool); keyIndex++){
			if(keyInput==keySettings[keyIndex][0] || keyInput==keySettings[keyIndex][1]){
				if(isPressed){
					keys[keyIndex]=true;
					ultimoTastoLetto=keyIndex;
				}else{
					keys[keyIndex]=false;
				}
			}
		}
	}
};
