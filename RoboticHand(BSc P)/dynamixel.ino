#include "AX12A.h"

#define DirectionPin 	(10u)
#define BaudRate  		(1000000ul)

char val1=' ';
char command;

class Finger {
  public:
    Finger(int _open_pos, int _close_pos, int _ID) {
      open_pos = _open_pos;
      close_pos = _close_pos;
      ID = _ID;
    };
    void set_position(int pos);
    int get_ID() {
      return ID;
    };
    int close_position() {
      return close_pos;
    };
    int open_position() {
      return open_pos;
    };
  private:
    int ID;
    int open_pos;
    int close_pos;
    bool is_pos_valid(int pos);
};


bool Finger::is_pos_valid(int pos) {
  if (open_pos < close_pos)
    return (pos >= open_pos && pos <= close_pos);
  if (open_pos > close_pos)
    return (pos >= close_pos && pos <= open_pos);
}

void Finger::set_position(int percent) {
  int pos = open_pos + percent * (close_pos - open_pos) / 100;
  Serial.print(ID);
  Serial.print(" : ");
  Serial.println(pos);
  if (!is_pos_valid(pos))
    return;
  ax12a.moveSpeed(ID, pos, 200);
}


Finger thumb( 512 , 824 , 5); //kham shdan
Finger index_finger( 512 , 200 , 2 );
Finger middle_finger( 512 , 200 , 4);
Finger ring_finger( 512 , 200 , 3);
Finger baby_finger( 512 , 250 , 6);
Finger thumbC(512,200, 1);


void fist() {
  index_finger.set_position(100);
  middle_finger.set_position(100);
  ring_finger.set_position(100);
  baby_finger.set_position(100);
  thumbC.set_position(100);
  thumb.set_position(100);
}

void rest() {
  index_finger.set_position(0);
  middle_finger.set_position(0);
  ring_finger.set_position(0);
  baby_finger.set_position(0);
  thumbC.set_position(0);
  thumb.set_position(0);
}

void tripod() {
  index_finger.set_position(60);
  middle_finger.set_position(80);
  ring_finger.set_position(100);
  baby_finger.set_position(100);
  thumbC.set_position(80);
  thumb.set_position(50);
}

void point() {
  index_finger.set_position(0);
  middle_finger.set_position(100);
  ring_finger.set_position(100);
  baby_finger.set_position(100);
  thumbC.set_position(100);
  thumb.set_position(100);
}

void grasp() {
  thumbC.set_position(60);
  delay(1000);
  index_finger.set_position(70);
  middle_finger.set_position(70);
  ring_finger.set_position(70);
  baby_finger.set_position(70);
  thumb.set_position(80);
}

void hook() {
  index_finger.set_position(100);
  middle_finger.set_position(100);
  ring_finger.set_position(100);
  baby_finger.set_position(100);
  thumbC.set_position(0);
  thumb.set_position(0);
}

void victory() {
  index_finger.set_position(0);
  middle_finger.set_position(0);
  ring_finger.set_position(100);
  baby_finger.set_position(100);
  thumbC.set_position(100);
  thumb.set_position(100);
}

void hand_shake() {
  index_finger.set_position(0);
  middle_finger.set_position(20);
  ring_finger.set_position(60);
  baby_finger.set_position(100);
  thumbC.set_position(0);
  thumb.set_position(100);
}

void precision_grip() {
  index_finger.set_position(100);
  //delay(500);
  middle_finger.set_position(0);
  ring_finger.set_position(0);
  baby_finger.set_position(0);
  thumbC.set_position(100);
  thumb.set_position(85);

}

void get_EMG() {
  Serial.begin(9600);
  while (Serial.available() == 0) { //digitalWrite(LED_BUILTIN, HIGH);
  //delay(500);
  //digitalWrite(LED_BUILTIN, LOW);
  //delay(500);
  }
  if (Serial.available() > 0) {
    //digitalWrite(LED_BUILTIN, LOW);
    //delay(2000);
    //digitalWrite(LED_BUILTIN,HIGH);
    //delay(2000);
    val1 = Serial.read();
  }

  ax12a.begin(BaudRate, DirectionPin, &Serial1);

  if (val1 == 'R') {
   // digitalWrite(LED_BUILTIN, HIGH);
    rest();
  }else if (val1 == 'F') {
    //digitalWrite(LED_BUILTIN, LOW);
    fist();
  }else if (val1 == 'P') {
    point();
  }else if(val1=='E'){
    grasp();
  }
  delay(200);
  Serial.flush();
  Serial.end();
  
}


void get_command() {
  command = Serial.read();
  if (command == 'r') {
    rest();
  } else if ( command == 'f') {
    fist();
  } else if (command == 'p') {
    point();
  } else if (command == 'g') {
    grasp();
  } else if (command == 'h') {
    hook();
  } else if (command == 'v') {
    victory();
  } else if (command == 's') {
    hand_shake();
  } else if (command == 'e') {
    precision_grip();
  }
}


void seq(){
    delay(3000);
    rest();
    delay(3000);
    fist();
    delay(3000);
    rest();
    delay(3000);
    point();
    delay(3000);
    rest();
    delay(3000);
    precision_grip();
    delay(3000);
    rest();
    delay(3000);
    hand_shake();
    delay(3000);
    rest();
    delay(3000);
    grasp();
    
}


void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  ax12a.begin(BaudRate, DirectionPin, &Serial1);
}

void loop()
{
  
 //get_EMG();
 //get_command();
 seq();
 

}
