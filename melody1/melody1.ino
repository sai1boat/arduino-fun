#define PIN_2 2
#define PIN_6 6
#define PIN_7 7
#define PIN_8 8
#define PIN_9 9
#define PIN_10 10
#define PIN_11 11
#define PIN_12 12
#define PIN_13 13

#include "pitches.h"
#include <IRremote.h>


bool mute = true;
unsigned int songIndex = 0;
unsigned int melodyIndex = 0;

//Songs
int melody[] = {NOTE_C4, NOTE_E4, NOTE_G4};
int entertainerIntro[] = {NOTE_D6, NOTE_E6, NOTE_C6, NOTE_A5, NOTE_B5, NOTE_G5, NOTE_D5, NOTE_E5, NOTE_C5, NOTE_A4, NOTE_B4, NOTE_G4, NOTE_D4, NOTE_E4, NOTE_C4, NOTE_A3, NOTE_B3, NOTE_A3, NOTE_GS3, NOTE_G3};

int potPin = A3;
int potVal = 0;

IRrecv irrecv(PIN_7);
decode_results results;


void setup() {

  Serial.begin(9600);

  pinMode(PIN_8, OUTPUT);
  //3 LEDs R,G,B pins
  pinMode(PIN_9, OUTPUT);
  pinMode(PIN_10, OUTPUT);
  pinMode(PIN_11, OUTPUT);

  irrecv.enableIRIn();
  irrecv.blink13(true);
  
}

void loop() {

  //10k pot is 0-1023
  potVal = analogRead(potPin);
  float potScalar = (float)potVal/1024;


  if (irrecv.decode(&results)){
        Serial.println(results.value, HEX);
        irrecv.resume();
  } 

  int buttonState = digitalRead(PIN_2);
  if(buttonState == HIGH){
    mute = !mute;
    delay(1000);
  }

  if(mute==false){
    
    tone(PIN_8, entertainerIntro[melodyIndex]*(potScalar+1), 16);


    digitalWrite(PIN_9, potScalar<0.33? HIGH: LOW);
    digitalWrite(PIN_10, potScalar<0.66 && potScalar>=0.33? HIGH: LOW);
    digitalWrite(PIN_11, potScalar>=0.66? HIGH : LOW);

    melodyIndex = melodyIndex == 19? melodyIndex=0: melodyIndex+=1;
    delay(200);
    noTone(PIN_8);
  }
    
}
