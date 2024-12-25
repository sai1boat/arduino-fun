#define PIN_2 2
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

#include "pitches.h"
#include <IRremote.h>


bool mute = true;
unsigned int songIndex = 0;
unsigned int melodyIndex = 0;
unsigned long key_value = 0;

//Songs
int melody[] = {NOTE_C4, NOTE_E4, NOTE_G4};
int entertainerIntro[] = {NOTE_D6, NOTE_E6, NOTE_C6, NOTE_A5, NOTE_B5, NOTE_G5, NOTE_D5, NOTE_E5, NOTE_C5, NOTE_A4, NOTE_B4, NOTE_G4, NOTE_D4, NOTE_E4, NOTE_C4, NOTE_A3, NOTE_B3, NOTE_A3, NOTE_GS3, NOTE_G3};
int neverGonnaGiveYouUp_start[] = {NOTE_G4, NOTE_A4, NOTE_C4, NOTE_A4, NOTE_E4, NOTE_E4, NOTE_D4};
int neverGonnaGiveYouUp_0[] = {NOTE_G4, NOTE_A4, NOTE_C4, NOTE_A4, NOTE_D4, NOTE_D4, NOTE_C4,NOTE_B4,NOTE_A4};
int neverGonnaGiveYouUp_1[] = {NOTE_G4, NOTE_A4, NOTE_C4, NOTE_A4, NOTE_D4, NOTE_D4, NOTE_C4};
int neverGonnaGiveYouUp_2[] = {NOTE_G4, NOTE_A4, NOTE_C4, NOTE_A4, NOTE_C4, NOTE_D4, NOTE_B4, NOTE_A4, NOTE_G4, NOTE_G4, NOTE_D4, NOTE_C4};
int neverGonnaGiveYouUp_3[] = {NOTE_G4, NOTE_A4, NOTE_C4, NOTE_A4, NOTE_G5, NOTE_B4, NOTE_C4, NOTE_B4, NOTE_A4};
int neverGonnaGiveYouUp_4[] = {NOTE_G4, NOTE_A4, NOTE_C4, NOTE_A4, NOTE_C4, NOTE_D4, NOTE_B4, NOTE_A4, NOTE_G4, NOTE_G4,NOTE_D4,NOTE_C4};

int potPin = A3;
int potVal = 0;

IRrecv irrecv(PIN_4);
decode_results results;


void setup() {

  Serial.begin(9600);

  // pinMode(PIN_8, OUTPUT);
  // //3 LEDs R,G,B pins
  // pinMode(PIN_9, OUTPUT);
  // pinMode(PIN_10, OUTPUT);
  // pinMode(PIN_11, OUTPUT);
  pinMode(PIN_4, INPUT);
  pinMode(PIN_5, OUTPUT);

  irrecv.enableIRIn();
  irrecv.blink13(true);
  
}

void loop() {

  //10k pot is 0-1023
  potVal = analogRead(potPin);
  float potScalar = (float)potVal/1024;


  if (irrecv.decode(&results)){
        if (results.value == 0XFFFFFFFF)
          results.value = key_value;

        switch(results.value){
          case 0xFFA25D:
          Serial.println("CH-");
          break;
          case 0xFF629D:
          Serial.println("CH");
          break;
          case 0xFFE21D:
          Serial.println("CH+");
          break;
          case 0xFF22DD:
          Serial.println("|<<");
          break;
          case 0xFF02FD:
          Serial.println(">>|");
          break ;  
          case 0xFFC23D:
          Serial.println(">|");
          break ;               
          case 0xFFE01F:
          Serial.println("-");
          break ;  
          case 0xFFA857:
          Serial.println("+");
          break ;  
          case 0xFF906F:
          Serial.println("EQ");
          break ;  
          case 0xFF6897:
          Serial.println("0");
          break ;  
          case 0xFF9867:
          Serial.println("100+");
          break ;
          case 0xFFB04F:
          Serial.println("200+");
          break ;
          case 0xFF30CF:
          Serial.println("1");
          break ;
          case 0xFF18E7:
          Serial.println("2");
          break ;
          case 0xFF7A85:
          Serial.println("3");
          break ;
          case 0xFF10EF:
          Serial.println("4");
          break ;
          case 0xFF38C7:
          Serial.println("5");
          break ;
          case 0xFF5AA5:
          Serial.println("6");
          break ;
          case 0xFF42BD:
          Serial.println("7");
          break ;
          case 0xFF4AB5:
          Serial.println("8");
          break ;
          case 0xFF52AD:
          Serial.println("9");
          break ;
          case 0xF5202B4D:
          case 0xC9BE7574:
          case 0x33A6DB53:
          case 0xA6495C6E:
          Serial.print("vornado----> MINUS");
          break;

          case 0xC1319BB9:
          case 0x61048470:
          case 0x8506FBB5:
          case 0x3DD6A997:
          case 0x78A6B088:
          Serial.print("vornado----> UP");
          digitalWrite(PIN_5, HIGH);
          delay(500);
          digitalWrite(PIN_5, LOW);
          break;

          case 0xCC50F9:
          case 0x9233E352:
          case 0x2EEA376C:
          case 0x2EEA376D:
          case 0xD037EC09:
          case 0xBC2C9C5D:
          case 0x3B11A981:
          Serial.print("vornado----> PLUS");
          break;

          case 0xD51DC06D:
          case 0x35F0A978:
          case 0xC6140CB2:
          case 0xC4622513:
          Serial.print("vornado----> DOWN");
          break;

          case 0x55D25364:
          case 0x135BC1F:
          case 0x1294F19:
          case 0x6F4BCDA7:
          case 0x96228793:
          Serial.print("vornado----> POWER BUTTON");
          break;

          default:
          Serial.print("unrecognized hex:");
          Serial.println(results.value, HEX);  
          break ;
        }
        key_value = results.value;
        irrecv.resume(); 
  } 

 

  // if(mute==false){
    
  //   tone(PIN_8, entertainerIntro[melodyIndex]*(potScalar+1), 16);


  //   digitalWrite(PIN_9, potScalar<0.33? HIGH: LOW);
  //   digitalWrite(PIN_10, potScalar<0.66 && potScalar>=0.33? HIGH: LOW);
  //   digitalWrite(PIN_11, potScalar>=0.66? HIGH : LOW);

  //   melodyIndex = melodyIndex == 19? melodyIndex=0: melodyIndex+=1;
  //   delay(200);
  //   noTone(PIN_8);
  // }
    
}
