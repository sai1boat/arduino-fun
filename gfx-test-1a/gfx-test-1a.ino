
#include <SPI.h>
#include <Wire.h>
// #include <Adafruit_GFX.h>
// #include <Adafruit_SSD1306.h>

#include "U8glib.h"

#define PIN_2 2
#define PIN_4 4
#define PIN_6 6
#define PIN_7 7
#define PIN_8 8
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
// Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

//////U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NO_ACK);
//U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_NO_ACK);
////// U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE);
U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_NONE); 

unsigned short offset = 16;
unsigned short step   = 14;

char anim1_sux[][8] = {"|", "/", "--", "\\", "|", "/", "--", "\\"};
char anim2[][14] = {'▁','▂', '▃', '▄', '▅', '▆', '▇', '█', '▇', '▆', '▅', '▄', '▃', '▁'};

int i = 0;
void draw(void) {
  // graphic commands to redraw the complete screen should be placed here  
  u8g.setFont(u8g_font_unifont);
  //u8g.setFont(u8g_font_osb21);
  // u8g.drawStr( 0, offset+0*step, "Line 1");
  // u8g.drawStr( 0, offset+1*step, "Line 2");
  // u8g.drawStr( 0, offset+2*step, "Line 3");
  // u8g.drawStr( 0, offset+3*step, "Line 4");
  u8g.drawStr( 0, offset+0*step, anim1_sux[i%7]);
  // u8g.drawStr( 0, offset+1*step, anim[(i+1) % 7]);
  // u8g.drawStr( 0, offset+2*step, anim[(i+2) % 7]);
  // u8g.drawStr( 0, offset+3*step, anim[(i+3) % 7]);
  i++;
}

void setup() {

  Serial.begin(9600);
  // Start I2C communication with the Multiplexer
  // Wire.begin();
    // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  // if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) { // Address 0x3D for 128x64
  //   Serial.println(F("SSD1306 allocation failed"));
  //   for(;;); // Don't proceed, loop forever
  // }
  
    // flip screen, if required
  // u8g.setRot180();
  
  // set SPI backup if required
  //u8g.setHardwareBackup(u8g_backup_avr_spi);

  // assign default color value
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
}

