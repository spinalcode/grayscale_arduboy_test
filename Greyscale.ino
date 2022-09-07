#define ABG_IMPLEMENTATION
#define ABG_SYNC_SLOW_DRIVE
//#define ABG_L4_Triplane
#define ABG_TIMER4
#include "ArduboyG.h"
// ArduboyG a;
ArduboyG_Config<ABG_Mode::L3> a;

#include <Arduboy2.h>
#include <ArduboyPlaytune.h>
#include "gfx.h"
#include "music.h"

unsigned char * screenBuffer;
int frameNumber = 0;
byte curLev[16 * 8];
long int myDelay;
unsigned char numTiles = 0;
unsigned char levelNum = 0;
unsigned char maxLevels = 4;
long int tempTime;

// Make an instance of arduboy used for many functions
Arduboy2 arduboy;
ArduboyPlaytune tunes(arduboy.audio.enabled);

void drawTile(int16_t x, int16_t y, const uint8_t *bitmap) {
  int offset = (x * 8) + (y * 128);
  for (byte t = 0; t < 8; t++) {
    screenBuffer[offset++] = pgm_read_byte(bitmap++);
  }
}

void render() {

  //int offset=0;
  //int mt = frameNumber * 1024;
  //for(int y=0; y<8; y++){
  //  for(int x=0; x<1024; x++){
  //    screenBuffer[offset++] = pgm_read_byte(background + mt++);
  //  }
  //}

  a.drawOverwrite(0, 0, background, 0);
  //a.drawBitmap(0,0, background,128,64);
  if(++frameNumber==3) frameNumber=0;
}


void setup() {
  a.begin();
  screenBuffer = a.getBuffer();

  // audio setup
  tunes.initChannel(PIN_SPEAKER_1);
#ifndef AB_DEVKIT
  // if not a DevKit
  tunes.initChannel(PIN_SPEAKER_2);
#else
  // if it's a DevKit
  tunes.initChannel(PIN_SPEAKER_1); // use the same pin for both channels
#endif

    a.startGray();
   
}

void loop() {

    if(!a.nextFrame())
        return;

  render();
  if (!tunes.playing()){
    tunes.playScore(score);
  }


}
