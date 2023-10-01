#include "game.h"
using namespace std;
using namespace sf;

int main(){

    srand(static_cast<unsigned>(time(NULL)));

    Game game;

    Music music;

    if(!music.openFromFile("ES_Sosso - Magnus Ludvigsson.wav"))
        cout<<"Error Opening ES_Sosso - Magnus Ludvigsson.wav"<<endl;


    music.play();

    //Game Loop

    while(game.getwindowisOpen() /*&& !game.getEndgame()*/){

        //Update
        game.update();

        //Render
        game.render();

    }

}