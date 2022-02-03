#include "../src/rsdl.hpp"
#include "gameplay.hpp"
#include "brickbreaker.hpp"


Station::Station()
{
  win = new Window(WINDOW_WIDTH, WINDOW_HEIGTH, "BrickBreaker");
  current_station=NEW_GAME;
  enterPressed = false;
}

GameWindow::GameWindow()
{
  station = new Station ();
  gameplay = new GamePlay();
  current_player = new Player();
}

void GameWindow::display()
{
  display_menue();
  while(station->get_current_station()!=QUIT){
    switch (station->get_current_station()){
      case NEW_GAME:
        gameplay->display(station->get_win());
        current_player->set_score(gameplay->get_score());
        display_endOfGame();
      break;
      case SCOREBOARD:
        display_scoreboard();
      break;
      case EDIT_NAME:
        display_editName();
      break;
      default :
        display_menue();
    }
    station->restart();
  }
}

void GameWindow::display_endOfGame(){
  station->set_current_station(NEW_GAME);
  station->reset_enterPressed();
  while(!station->getEnterPreesed())
  {
    station->EndOfGame_getAndProcessInput();
    station->EndOfGame_draw(current_player->get_score());
    Delay(TICK_DURATION);
  }
}


void GameWindow::display_scoreboard()
{
    station->reset_enterPressed();
    while(!station->getEnterPreesed())
    {
      station->ScoreBoard_getAndProcessInput();
      station->ScoreBoard_draw();
      Delay(TICK_DURATION);
    }
    station->set_current_station(MENUE);
}

void GameWindow::display_menue()
{
    station->set_current_station(NEW_GAME);
    while(!station->getEnterPreesed())
    {
      station->Menue_getAndProcessInput();
      station->Menue_draw();
      Delay(TICK_DURATION);
    }
}

void GameWindow::display_editName()
{
    station->reset_enterPressed();
    while(!station->getEnterPreesed())
    {
      station->EditName_getAndProcessInput();
      station->EditName_draw();
      Delay(TICK_DURATION);
    }
    station->set_current_station(MENUE);
}


void Station::Menue_next_station(){
  if(current_station==QUIT){
    current_station=NEW_GAME;
    return ;
  }
  current_station++;
}

void Station::Menue_last_station(){
  if(current_station==NEW_GAME){
    current_station=QUIT;
    return ;
  }
  current_station--;
}

void Station::Menue_draw()
{
  win->clear();
  win->draw_bg(IMG_BACKGROUND, 0, 0);
  win->draw_png(IMG_MENUE_NEW_GAME_BOX, MENUE_BOX_X, MENUE_BOX_Y, MENUE_BOX_WIDTH,  MENUE_BOX_HIGHT);
  win->draw_png(IMG_MENUE_SCOREBOARD_BOX, MENUE_BOX_X, 1 LEVEL_DOWN MENUE_BOX_Y, MENUE_BOX_WIDTH,  MENUE_BOX_HIGHT);
  win->draw_png(IMG_MENUE_EDIT_NAME_BOX, MENUE_BOX_X, 2 LEVEL_DOWN MENUE_BOX_Y, MENUE_BOX_WIDTH,  MENUE_BOX_HIGHT);
  win->draw_png(IMG_EDIT_NAME_BOX, MENUE_BOX_X,  3 LEVEL_DOWN MENUE_BOX_Y, MENUE_BOX_WIDTH,  MENUE_BOX_HIGHT);
  win->draw_png(IMG_FRAME, MENUE_BOX_X, STATION_LEVEL, MENUE_BOX_WIDTH,  MENUE_BOX_HIGHT);
  win->update_screen();
}

void Station::Menue_getAndProcessInput()
{
  lastEvent = win->pollForEvent();
  Menue_processLastEvent();
}

void Station::Menue_processLastEvent()
{
  if(lastEvent.type() == KEY_PRESS)
  {
    if(lastEvent.pressedKey() == DOWN)
      Menue_next_station();
    else if(lastEvent.pressedKey() == UP)
      Menue_last_station();
    else if(lastEvent.pressedKey() == RETURN)
      enterPressed = true;
  }
}

void Station::EndOfGame_next_station(){
  if(current_station==NEW_GAME){
    current_station=MENUE;
    return ;
  }
  current_station=NEW_GAME;
}


void Station::EndOfGame_draw(int _score)
{
  win->clear();
  win->draw_bg(IMG_BACKGROUND, 0, 0);
  win->draw_png(IMG_YASI, MENUE_BOX_X, MENUE_BOX_Y, MENUE_BOX_WIDTH,  MENUE_BOX_HIGHT*2);
  win->draw_png(IMG_MENUE_NEW_GAME_BOX, MENUE_BOX_X,  3 LEVEL_DOWN MENUE_BOX_Y, MENUE_BOX_WIDTH,  MENUE_BOX_HIGHT);
  win->draw_png(IMG_MENUE , MENUE_BOX_X,  2 LEVEL_DOWN MENUE_BOX_Y, MENUE_BOX_WIDTH,  MENUE_BOX_HIGHT);
  win->show_text("score: ",MENUE_BOX_X*1.4,1 LEVEL_DOWN MENUE_BOX_Y,BLACK,FONT,40);
  win->show_text(int_to_string(_score),3*MENUE_BOX_X,1 LEVEL_DOWN MENUE_BOX_Y,BLACK,FONT,40);
  win->show_text("GAME OVER !!!",MENUE_BOX_X*1.4,0.5 LEVEL_DOWN MENUE_BOX_Y,BLACK,FONT,40);
  win->draw_png(IMG_FRAME, MENUE_BOX_X, (current_station+2) LEVEL_DOWN MENUE_BOX_Y, MENUE_BOX_WIDTH,  MENUE_BOX_HIGHT);
  win->update_screen();
}

void Station::EndOfGame_getAndProcessInput()
{
  lastEvent = win->pollForEvent();
  EndOfGame_processLastEvent();
}

void Station::EndOfGame_processLastEvent()
{
  if(lastEvent.type() == KEY_PRESS)
  {
    if(lastEvent.pressedKey() == UP || lastEvent.pressedKey() == DOWN){
      EndOfGame_next_station();
    }else if(lastEvent.pressedKey() == RETURN){
      enterPressed = true;
    }
  }
}


void Station::ScoreBoard_draw(){
  win->clear();
  win->draw_bg(IMG_BACKGROUND_W, 0, 0);
  win->draw_png(IMG_MENUE, MENUE_BOX_X, 3 LEVEL_DOWN MENUE_BOX_Y, MENUE_BOX_WIDTH,  MENUE_BOX_HIGHT);
  win->draw_png(IMG_FRAME, MENUE_BOX_X, 3 LEVEL_DOWN MENUE_BOX_Y, MENUE_BOX_WIDTH,  MENUE_BOX_HIGHT);
  win->draw_png(IMG_YASI, MENUE_BOX_X, 0 LEVEL_DOWN MENUE_BOX_Y, MENUE_BOX_WIDTH,  MENUE_BOX_HIGHT*3.5);
  win->update_screen();
}

void Station::ScoreBoard_getAndProcessInput()
{
  lastEvent = win->pollForEvent();
  ScoreBoard_processLastEvent();
}

void Station::ScoreBoard_processLastEvent()
{
  if(lastEvent.type() == KEY_PRESS)
  {
    if(lastEvent.pressedKey() == RETURN)
      enterPressed = true;
  }
}

void Station::EditName_draw(){
  win->clear();
  win->draw_bg(IMG_BACKGROUND_W, 0, 0);
  win->draw_png(IMG_SAVE, MENUE_BOX_X, 2 LEVEL_DOWN MENUE_BOX_Y, MENUE_BOX_WIDTH,  MENUE_BOX_HIGHT);
  win->draw_png(IMG_CANCEL, MENUE_BOX_X, 3 LEVEL_DOWN MENUE_BOX_Y, MENUE_BOX_WIDTH,  MENUE_BOX_HIGHT);
  win->draw_png(IMG_FRAME, MENUE_BOX_X, 3 LEVEL_DOWN MENUE_BOX_Y, MENUE_BOX_WIDTH,  MENUE_BOX_HIGHT);
  win->draw_png(IMG_YASI, MENUE_BOX_X, 0 LEVEL_DOWN MENUE_BOX_Y, MENUE_BOX_WIDTH,  MENUE_BOX_HIGHT*0.5);
  win->update_screen();
}

void Station::EditName_getAndProcessInput()
{
  lastEvent = win->pollForEvent();
  EditName_processLastEvent();
}

void Station::EditName_processLastEvent()
{
  if(lastEvent.type() == KEY_PRESS)
  {
    if(lastEvent.pressedKey() == RETURN)
      enterPressed = true;
  }
}

/////////////////

string Player::give_player_info(){
  string info;
  info.append(name);
  info.append(" :        ");
  info+=int_to_string(score);
  return info;
}
