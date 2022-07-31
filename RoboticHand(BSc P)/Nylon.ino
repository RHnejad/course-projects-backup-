
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
  analogWrite(ID,pos);
}


Finger thumb(180,255,4); //kham shdan
Finger index_finger(180,255,9);
Finger middle_finger(180,255,13);
Finger ring_finger(180,255,2);
Finger baby_finger(180,255,11);

void fist() {
  index_finger.set_position(100);
  middle_finger.set_position(100);
  ring_finger.set_position(100);
  baby_finger.set_position(100);
  thumb.set_position(100);
}

void rest() {
  index_finger.set_position(0);
  middle_finger.set_position(0);
  ring_finger.set_position(0);
  baby_finger.set_position(0);
  thumb.set_position(0);
}

void tripod() {
  index_finger.set_position(60);
  middle_finger.set_position(80);
  ring_finger.set_position(100);
  baby_finger.set_position(100);
  thumb.set_position(50);
}

void point() {
  index_finger.set_position(0);
  middle_finger.set_position(100);
  ring_finger.set_position(100);
  baby_finger.set_position(100);
  thumb.set_position(100);
}

void grasp() {
  //thumbC.set_position(60);
  //delay(1000);
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
  thumb.set_position(0);
}

void victory() {
  index_finger.set_position(0);
  middle_finger.set_position(0);
  ring_finger.set_position(100);
  baby_finger.set_position(100);
  thumb.set_position(100);
}

void hand_shake() {
  index_finger.set_position(0);
  middle_finger.set_position(20);
  ring_finger.set_position(60);
  baby_finger.set_position(100);
  //thumbC.set_position(0);
  thumb.set_position(100);
}

void precision_grip() {
  index_finger.set_position(100);
  //delay(500);
  middle_finger.set_position(0);
  ring_finger.set_position(0);
  baby_finger.set_position(0);
  //thumbC.set_position(65);
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
    point();
    grasp();
    delay(3000);
}


void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  
 //get_EMG();
 //get_command();

 rest();
 delay(15000);
 fist();
 delay(150000);

}
