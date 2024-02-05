#define PIN_2 2 // LEFT BUTTON (YELLOW)
#define PIN_3 3 // RIGHT BUTTON (YELLOW)
#define PIN_4 4
#define PIN_5 5 
#define PIN_6 6 
#define PIN_7 7 
#define PIN_8 8
#define PIN_9 9
#define PIN_10 10
#define PIN_11 11
#define PIN_12 12
#define PIN_13 13
#define PIN_14 14

#define MIDI_BAUD_RATE 31250

#define PCH_IN_CHANNEL 1

#include <MIDI.h>
#include "pitches.h"

int potPin = A3;
int potVal = 0;

MIDI_CREATE_DEFAULT_INSTANCE();

int leftButton  = PIN_2;
int rightButton = PIN_3;

int bankNumber = 0;

/* 
 * buttonNumber is 1 through 5
 */
void handle_button_event(int buttonNumber){
    MIDI.sendProgramChange(buttonNumber+(bankNumber*16), PCH_IN_CHANNEL);
}

void setup() {

  // Serial.begin(9600);
  //Serial.begin(MIDI_BAUD_RATE);
  MIDI.begin(MIDI_CHANNEL_OMNI);

  pinMode(leftButton, INPUT);
  pinMode(rightButton, INPUT);


  pinMode(PIN_9, INPUT);
  pinMode(PIN_10, INPUT);
  pinMode(PIN_11, INPUT);
  pinMode(PIN_12, INPUT);
  pinMode(PIN_13, INPUT);
  pinMode(PIN_14, INPUT);

}

void loop() {

  int left = digitalRead(leftButton);
  int right = digitalRead(rightButton);
  if(left == HIGH){
    bankNumber = bankNumber == 0? 6: bankNumber-1;
  }
  if (right == HIGH){
    bankNumber = bankNumber == 6? 0: bankNumber+1;
  }

  int b1 = digitalRead(PIN_9);
  int b2 = digitalRead(PIN_10);
  int b3 = digitalRead(PIN_11);
  int b4 = digitalRead(PIN_12);
  int b5 = digitalRead(PIN_13);
  if(b1 == HIGH)
    handle_button_event(1);
  else if (b2 == HIGH)
    handle_button_event(2);
  else if(b3 == HIGH)
    handle_button_event(3);
  else if (b4 == HIGH)
    handle_button_event(4);
  else if(b5 == HIGH)
    handle_button_event(5);
}


