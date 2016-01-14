/*
 * Simon written by liamsdomain for arduino
 * This code is public domain and free use
*/

//define button pins
#define butRed  8
#define butYel  9
#define butWhi  10
#define butGre  11

//define LED pins
#define ledRed  2
#define ledYel  3
#define ledWhi  4
#define ledGre  5

//variables used for button logic
//state is equal to the last state of the button
//lastMil is equal to the time when the button was last pressed, used to prevent bouncing
boolean state = false;
unsigned long lastMil = 0;
boolean state2 = false;
unsigned long lastMil2 = 0;
boolean state3 = false;
unsigned long lastMil3 = 0;
boolean state4 = false;
unsigned long lastMil4 = 0;

int order[20]; //keeps track of order of lights

int turn = 1; //turn number

int part = 0; //progress of current turn

boolean playing = true; //set to false when game has been lost/won

void setup() {
  pinMode(butRed, INPUT_PULLUP); //setup pins
  pinMode(butYel, INPUT_PULLUP);
  pinMode(butWhi, INPUT_PULLUP);
  pinMode(butGre, INPUT_PULLUP);

  pinMode(ledRed, OUTPUT);
  pinMode(ledYel, OUTPUT);
  pinMode(ledWhi, OUTPUT);
  pinMode(ledGre, OUTPUT);

  Serial.begin(9600); //setup for debugging, un-needed

  randomSeed(analogRead(0));

  for(int i=0; i<=20; i++){ //set light order before game
    order[i] = random(2,6); // 2 = red, 3 = yellow...
  }
}

void lightsOn(){ //turn all lights on
  for(int i = 2; i<=5; i++){
    digitalWrite(i, HIGH);
  }
}

void lightsOff(){ //turn all lights off
  for(int i = 2; i<=5; i++){
    digitalWrite(i, LOW);
  }
}

void loop() {
  if(playing && turn<=20){
    //show light pattern at start of each turn
    for(int i=0; i<turn; i++){
      digitalWrite(order[i], HIGH);
      delay(750);
      digitalWrite(order[i], LOW);
      delay(200);
    }

    //get button pushes
    while(part<turn){
      if(!digitalRead(butRed)!=state && lastMil+50<=millis()){
        Serial.println("RED");
        if(order[part]==2 && !state){
          part++;
          digitalWrite(2, HIGH); //flash light while button is down
        }else if(!state){
          //failure
          part=22;//end loop (doesn't matter what number is used as long as it's above 21)
          lightsOn();
          playing = false;
        } else {
          digitalWrite(2, LOW);
        }
        state = !state;
        lastMil = millis();
      }else if(!digitalRead(butYel)!=state2 && lastMil2+50<=millis()){
        Serial.println("YELLOW");
        if(order[part]==3 && !state2){
          part++;
          digitalWrite(3, HIGH);
        }else if(!state2){
          //failure
          part=22;//end loop
          lightsOn();
          playing = false;
        } else {
          digitalWrite(3, LOW);
        }
        state2 = !state2;
        lastMil2 = millis();
      } else if(!digitalRead(butWhi)!=state3 && lastMil3+50<=millis()){
        Serial.println("WHITE");
        if(order[part]==4 && !state3){
          part++;
          digitalWrite(4, HIGH);
        }else if(!state3){
          //failure
          part=22;//end loop
          lightsOn();
          playing = false;
        } else {
          digitalWrite(4, LOW);
        }
        state3 = !state3;
        lastMil3 = millis();
      } else if(!digitalRead(butGre)!=state4 && lastMil4+50<=millis()){
        Serial.println("GREEN");
        if(order[part]==5 && !state4){
          part++;
          digitalWrite(5, HIGH);
        }else if(!state4){
          //failure
          part=22;//end loop
          lightsOn();
          playing = false;
        } else {
          digitalWrite(5, LOW);
        }
        state4 = !state4;
        lastMil4 = millis();
      }
    }
    if(playing){
      part = 0;
      turn++;
      delay(500);
      lightsOff();
      delay(500);
    }
  }else if (playing==21){
    part = random(2,6);
    digitalWrite(part, HIGH);
    delay(250);
    digitalWrite(part, LOW);
  }
}
