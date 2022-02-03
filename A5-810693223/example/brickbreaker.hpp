#include "../src/rsdl.hpp"
#include "gameplay.hpp"
#include <cstdlib>
#include <vector>
#include <cmath>
#include <string>

using namespace std;


#define WINDOW_TITLE "RSDL Tutorial"



#define BACK_SPACE 8
#define RETURN 13


#define IMG_SQUARE "example/assets/square.png"

#define IMG_BACKGROUND "example/assets/telegram.jpeg"
#define IMG_MENUE_NEW_GAME_BOX "example/assets/my-assets/newgame.png"
#define IMG_MENUE_SCOREBOARD_BOX "example/assets/my-assets/scoreboard.png"
#define IMG_MENUE_EDIT_NAME_BOX "example/assets/my-assets/editname.png"
#define IMG_EDIT_NAME_BOX "example/assets/my-assets/quit.png"
#define IMG_MENUE "example/assets/my-assets/menue.png"
#define IMG_SAVE "example/assets/my-assets/save.png"
#define IMG_CANCEL "example/assets/my-assets/cancel.png"

#define IMG_FRAME "example/assets/my-assets/frame.png"
#define IMG_YASI "example/assets/my-assets/yasi.png"


#define MENUE_BOX_X 120
#define MENUE_BOX_Y 140
#define LEVEL_DOWN *220+
#define MENUE_BOX_WIDTH 400
#define MENUE_BOX_HIGHT 170

#define STATION_LEVEL (current_station-1) LEVEL_DOWN MENUE_BOX_Y


#define UP 'R'
#define DOWN 'Q'

#define MENUE 0
#define NEW_GAME 1
#define SCOREBOARD 2
#define EDIT_NAME 3
#define QUIT 4

class Station
{
private:
  Window* win;
  bool enterPressed;
  int current_station;
  Event lastEvent;
  void Menue_processLastEvent();
  void Menue_next_station();
  void Menue_last_station();
  void ScoreBoard_processLastEvent();
  void EditName_processLastEvent();
  void EndOfGame_processLastEvent();
  void EndOfGame_next_station();
public:
  Station () ;
  int get_current_station(){return current_station;}
  void set_current_station(int new_s){current_station=new_s;}
  void reset_enterPressed(){enterPressed=false;}
  bool getEnterPreesed(){return enterPressed;}
  void restart(){enterPressed=false;}
  void Menue_getAndProcessInput();
  void Menue_draw();
  void ScoreBoard_getAndProcessInput();
  void ScoreBoard_draw();
  void EditName_getAndProcessInput();
  void EditName_draw();
  void EndOfGame_getAndProcessInput();
  void EndOfGame_draw(int score);


  Window* get_win (){return win;}
};

class Player
{
public:
  Player (){score=0; name="";}
  int get_score(){return score;}
  void set_score(int _score){score=_score;}
  string give_player_info();
private:
  string name;
  int score;
};

class GameWindow
{
  private:
    vector<Player*> players;
    Player* current_player;
    Station* station;
    GamePlay* gameplay;
  public:
    GameWindow();
    void display();
    void display_menue();
    void display_scoreboard();
    void display_editName();
    void display_endOfGame();
};
string int_to_string(int num);
