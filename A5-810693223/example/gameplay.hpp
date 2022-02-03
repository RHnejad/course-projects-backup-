#ifndef __MY_STRING__
#define __MY_STRING__
#include<string>
#include <vector>
#include <math.h>
#include <time.h>
#include"../src/rsdl.hpp"

using namespace std;

#define TICK_DURATION 10
#define PI 3.1415
#define IN_RADIAN PI-PI/180*
#define IN_DEGREE *180/PI+180
#define SPEED 3

#define MAX_STRING_LENGTH 10
#define FONT_FREESANS "example/assets/OpenSans.ttf"


#define IMG_BACKGROUND_GP "example/assets/my-assets/gp-bg-s.jpeg"
#define IMG_BACKGROUND_W "example/assets/my-assets/white.jpeg"
#define IMG1_BACKGROUND "example/assets/11.png"
#define IMG_BALL "example/assets/ball.png"
#define IMG_BALL_CLEAR "example/assets/clear-ball.png"
#define IMG_FIRE_BALL "example/assets/ball.png"
#define IMG_ARROW "example/assets/arrow-png.png"
#define FONT "example/assets/OpenSans.ttf"

#define LEFT 'P'
#define RIGHT 'O'

#define WINDOW_WIDTH 640
#define WINDOW_HEIGTH 1135
#define BALL_R 30
#define ARROW_WIDTH 210
#define ARROW_HEIGHT 55
#define BOARD_Y_UP 300

#define ORIGIN_X WINDOW_WIDTH/2
#define ORIGIN_X_ARROW balls[0]->get_x()-90
#define ORIGIN_Y WINDOW_HEIGTH-237
#define ORIGIN_Y_ARROW ORIGIN_Y-10

#define TEMP_END 7
#define BRICK_WIDTH 125
#define BRICK_HEIGHT 70

#define FIRST_ROW 300
#define SCORE_X  200
#define SCORE_Y  115
#define NAME_X
#define NAME_Y
#define RECORD_X
#define RECORD_Y
#define START_ANGLE 90
#define R (resistance%50)*5//resistance/256*resistance/256 //
#define G 255-(resistance%25)*10//resistance/256 % resistance*resistance //
#define B (resistance%25)*5//resistance%256 //

class Board
{
private:
  int width;
  int height_up;
  int height_down;
public:
  Board(int w,int h_u,int h_d);
  int get_width(){return width;}
  int get_height_up(){return height_up;}
};

class Ball
{
private:
  double x;
  double y;
  double dx;
  double dy;
  Board* board;
public:
  Ball();
  double get_x(){return x;}
  double get_y(){return y;}
  void reset_y(){y=ORIGIN_Y;}
  void move(double angle,Window* win);
  void draw(Window* win);
  void clear(Window* win);
};

class Brick
{
private:
  double x ;
  double y ;
  int resistance;
  RGB color;
  bool state;
public:
  Brick(double _x,double _y,int _resistance);
  RGB get_color(){return color; }
  double get_x(){return x;}
  double get_y(){return y;}
  void go_next_level(){y+=BRICK_HEIGHT;}
  int get_resistance(){return resistance;}
  void draw_brick();
  void decrease_resistance();
  void set_resistance(int _resistance){resistance=_resistance;}
protected:
};

class MagicBall : public Brick
{

};

class FirePower : public Brick
{

};

class LifeBall : public Brick
{

};

class GamePlay
{
private:
  int score;
  bool SpacePressed;
  vector< Brick* > bricks;
  vector<Ball*> balls;
  void generate_next_level();
  double angle;
  Event lastEvent;
  void draw_balls(Window* win);
  void draw_bricks(Window* win);
  void getAndProcessInput(Window* win);
  void processLastEvent();
  void draw (Window* win);
  void move_balls(Window* win);
  void reset_balls();
  void clear_board();
public:
  GamePlay();
  void display(Window* win);
  int get_score() {return score;}
};




class MyString
{
  public:
    MyString(int _x, int _y, int _fontSize);
    string textToDisplay();
    void eraseLastChar();
    void addChar(char c);
    void drawString(Window* win);
    string getString();
  private:
    string inputString;
    int fontSize;
    int x;
    int y;
};

#endif
