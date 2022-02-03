#include "gameplay.hpp"

string int_to_string(int num){
  string st;
  int temp;
  string source_string = "0123456789";
  while(num>0){
    temp=num%10;
    num=num/10;
    st+=source_string[temp];
    }
  string temp_st;
  for(int i=0;i<st.size();i++){
    temp_st+=st[st.size()-i-1];
  }
  return temp_st ;
}

Ball::Ball (){
  x=ORIGIN_X;
  y=ORIGIN_Y;
  dx=0;
  dy=0;
  board = new Board(WINDOW_WIDTH,BOARD_Y_UP,ORIGIN_Y);
}
Board::Board (int w,int h_u,int h_d){
  width=w;
  height_up=h_u;
  height_down=h_d;
}

void Ball::draw(Window* win){
  win->draw_png(IMG_BALL, x, y, BALL_R, BALL_R);
  win->update_screen();
}
void Ball::clear(Window* win){
  win->draw_png(IMG_BALL_CLEAR, x, y, BALL_R, BALL_R);
  win->update_screen();
}


void Ball::move(double angle,Window* win){
  dx=SPEED*cos( IN_RADIAN angle);
  dy=SPEED*sin( IN_RADIAN angle);
    while(y<=ORIGIN_Y){
      clear(win);
      x+=dx;
      y-=dy;
    if(x>board->get_width()){
      x=-1*x+2*board->get_width();
      dx=-1*dx;
    }else if(x<0){
      x=-1*x;
      dx=-1*dx;
    }
    if(y<board->get_height_up()){
      y=-1*y+2*board->get_height_up();
      dy=-1*dy;
    }
    draw(win);
  }
}

Brick::Brick (double _x,double _y,int _resistance):color(10,245,5){
  x=_x;
  y=_y;
  resistance=_resistance;
  RGB new_color(R, G, B);
  color=new_color;

}

GamePlay::GamePlay (){
  Ball* first_ball = new Ball();
  balls.push_back(first_ball);
  angle=START_ANGLE;
  score=1;
  SpacePressed=false;
  srand (time(NULL));
  Brick* first_brick = new Brick((rand()%4)*128,FIRST_ROW,1);
  bricks.push_back(first_brick);
}

void GamePlay::draw_balls(Window* win){
  for(int i=0 ; i<balls.size();i++){
    balls[i]-> draw(win);
  }
}

void GamePlay::draw_bricks(Window* win){
  for(int i=0;i<bricks.size();i++){
    win->fill_rect(bricks[i]->get_x(),bricks[i]->get_y(),BRICK_WIDTH, BRICK_HEIGHT,bricks[i]->get_color());
    win->draw_rect(bricks[i]->get_x(),bricks[i]->get_y(),BRICK_WIDTH, BRICK_HEIGHT,BLACK);
    string res=int_to_string(bricks[i]->get_resistance());
    win->show_text(res,bricks[i]->get_x()+50,bricks[i]->get_y()+8,BLACK, FONT,35);
  }
}

void GamePlay::move_balls(Window* win){
  for(int i=0 ; i<balls.size();i++){
      balls[0]->move(angle,win);
  }
}

void GamePlay::reset_balls(){
  for(int i=0 ; i<balls.size();i++){
    balls[i]->reset_y();
  }
}

void GamePlay::generate_next_level(){
  for(int i=0;i<bricks.size();i++)
    bricks[i]->go_next_level();

  srand (time(NULL));
  Brick* new_brick = new Brick((rand()%4)*128,FIRST_ROW,score);
  bricks.push_back(new_brick);
}

void GamePlay::clear_board(){
  while(bricks.size()>0){
    bricks.pop_back();
  }
}
void GamePlay::display (Window* win)
{
  int j=0;
    angle=START_ANGLE;
    while(j<=TEMP_END){
      while(!SpacePressed)
      {
        getAndProcessInput(win);
        draw(win);
        Delay(TICK_DURATION);
      }
      SpacePressed=false;
      move_balls(win);
      reset_balls();
      score++;
      generate_next_level();
      j++;
    }
    clear_board();
}

void GamePlay::draw (Window* win){
  win->clear();
  win->draw_bg(IMG_BACKGROUND_GP, 0, 0);
  win->draw_png(IMG_ARROW,ORIGIN_X_ARROW,ORIGIN_Y_ARROW,ARROW_WIDTH,ARROW_HEIGHT,angle);
  draw_balls(win);
  draw_bricks(win);
  win->show_text(int_to_string(score),SCORE_X,SCORE_Y,BLACK,FONT,40);
  win->update_screen();
  Delay(TICK_DURATION);
}

void GamePlay::getAndProcessInput(Window* win)
{
  lastEvent = win->pollForEvent();
  processLastEvent();
}

void GamePlay::processLastEvent()
{
  int keeped_angle=angle;
  if(lastEvent.type() == KEY_PRESS)
  {
    if(lastEvent.pressedKey() == RIGHT)
      angle++;
    else if(lastEvent.pressedKey() == LEFT)
      angle--;
    else if(lastEvent.pressedKey() == ' ')
      SpacePressed = true;
  }
  if(angle<0 || angle>180)
    angle = keeped_angle;
}




MyString::MyString(int _x, int _y, int _fontSize): x(_x), y(_y), fontSize(_fontSize){}

string MyString::textToDisplay()
{
  return "  Your name: " + inputString;
}

void MyString::eraseLastChar()
{
  if(inputString.size() > 0)
      inputString.erase(inputString.size() - 1);
}

void MyString::addChar(char c)
{
  if(inputString.size() < MAX_STRING_LENGTH)
    inputString += c;
}

void MyString::drawString(Window* win)
{
  win->show_text(textToDisplay(), x, y, WHITE, FONT_FREESANS, fontSize);
}

string MyString::getString()
{
  return inputString;
}
