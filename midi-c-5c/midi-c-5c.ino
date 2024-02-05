#include "U8glib.h"

#define PIN_2 2
#define PIN_3 3
#define PIN_4 4
#define PIN_5 5 
#define PIN_6 6 
#define PIN_7 7 //LEFT
#define PIN_8 8 //RIGHT
#define PIN_9 9
#define PIN_10 10
#define PIN_11 11
#define PIN_12 12
#define PIN_13 13
#define PIN_14 14

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C //0x7A, 0x78, 0x3D, 0x3C Used File>Examples>Wire>i2c scanner.ino

U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_NONE); 

unsigned short offset = 16;
unsigned short step   = 14;

#define MIDI_BAUD_RATE 31250

#define PCH_IN_CHANNEL 1

#include <MIDI.h>
#include "pitches.h"

int potPin = A3;
int potVal = 0;

MIDI_CREATE_DEFAULT_INSTANCE();


int bankNumber = 0;
int currentPatch = 0;
int buttonNumber = 0;
char buf[16];

/* 
 * buttonNumber is 1 (left) or 2 (right)
 */
void handle_bank_change_button_event(){
  bankNumber = (bankNumber+1) % 7;
}

void handle_button_event(int button){
    buttonNumber = button;
    currentPatch = buttonNumber+(bankNumber*16);
    MIDI.sendProgramChange(currentPatch, PCH_IN_CHANNEL);
}

// int i = 0;
void draw(void) {
  // graphic commands to redraw the complete screen should be placed here  
  u8g.setFont(u8g_font_unifont);
  //u8g.setFont(u8g_font_osb21);
  u8g.drawStr( 0, offset+0*step, "joao midi v0.1.1");
  sprintf(buf, "Bank   #: %1d", bankNumber);
  u8g.drawStr( 0, offset+1*step, buf);
  sprintf(buf, "Button #: %1d", buttonNumber);
  u8g.drawStr( 0, offset+2*step, buf);
  sprintf(buf, "Patch  #: %1d", currentPatch);
  u8g.drawStr( 0, offset+3*step, buf);
  // u8g.drawStr( 0, offset+0*step, anim1_sux[i%7]);
  // u8g.drawStr( 0, offset+1*step, anim[(i+1) % 7]);
  // u8g.drawStr( 0, offset+2*step, anim[(i+2) % 7]);
  // u8g.drawStr( 0, offset+3*step, anim[(i+3) % 7]);
  // i++;
}

void setup() {

  // Serial.begin(9600);
  //Serial.begin(MIDI_BAUD_RATE);
  MIDI.begin(MIDI_CHANNEL_OMNI);

  pinMode(PIN_7, INPUT);
  pinMode(PIN_8, INPUT);
  pinMode(PIN_9, INPUT);
  pinMode(PIN_10, INPUT);
  pinMode(PIN_11, INPUT);
  pinMode(PIN_12, INPUT);
  pinMode(PIN_13, INPUT);
  pinMode(PIN_14, INPUT);


  if ( u8g.getMode() == U8G_MODE_R3G3B2 ) {
    u8g.setColorIndex(255);     // white
  }
  else if ( u8g.getMode() == U8G_MODE_GRAY2BIT ) {
    u8g.setColorIndex(3);         // max intensity
  }
  else if ( u8g.getMode() == U8G_MODE_BW ) {
    u8g.setColorIndex(1);         // pixel on
  }
  else if ( u8g.getMode() == U8G_MODE_HICOLOR ) {
    u8g.setHiColorByRGB(255,255,255);
  }

}

void loop() {

  u8g.firstPage();  
  do {
    draw();
  } while( u8g.nextPage() );


  int up = digitalRead(PIN_8);
  int b0 = digitalRead(PIN_9);
  int b1 = digitalRead(PIN_10);
  int b2 = digitalRead(PIN_11);
  int b3 = digitalRead(PIN_12);
  int b4 = digitalRead(PIN_13);

  if (up == HIGH){
    handle_bank_change_button_event();
  }
  else if(b1 == HIGH)
    handle_button_event(0);
  else if (b2 == HIGH)
    handle_button_event(1);
  else if(b3 == HIGH)
    handle_button_event(2);
  else if (b4 == HIGH)
    handle_button_event(3);
  else if(b5 == HIGH)
    handle_button_event(4);
}


