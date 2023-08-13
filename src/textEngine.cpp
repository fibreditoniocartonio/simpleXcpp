#include <filesystem>

#include "../inc/textEngine.hpp"
#include "../inc/gameEngine.hpp"
#include "../inc/menu.hpp"

TextEngine::TextEngine(GameEngine* game){
    this->game = game;
    this->ReadHowManyLang();
}

void TextEngine::LoadText(std::string language){
    this->CleanText();
    std::fstream fileLivello(("./res/language/"+language));
    if(!fileLivello.is_open()){
        //this alert isn't reading the string from file for obvious reason. The only downside is that it will always be in english.
        Alert* alert = new Alert(game, 16, "Error while opening the file at:\n./res/language/"+language+"\n\nWithout opening that file it's impossible to load texts. There will be unexpected behaviors.");
    }else{
        std::string stringaTemp;
        while(std::getline(fileLivello, stringaTemp)){
            this->testo.push_back(stringaTemp.substr(6));
            this->contaTesto++;
        }
    }
    fileLivello.close();
}

void TextEngine::CleanText(){
    std::vector<std::string> nuovoVettore;
    this->testo=nuovoVettore;
}

void TextEngine::ReadHowManyLang(){
    auto dirIter = std::filesystem::directory_iterator("./res/language");
    this->languagesFoundCount = 0;
    for (auto& entry : dirIter){
        if (entry.is_regular_file()){
            this->languagesFound.push_back(entry.path().filename().string());
            this->languagesFoundCount++;
        }
    }  
}