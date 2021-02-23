/* 
 *  J.S. Bach's Two Part Inventions #1 
 *  Left-hand part
 *  
 */

#include "TomatoCubeWorker_v2.h"

const PROGMEM char inv1_lh[] = {
// measure 1
REST, 2, REST, 16, NOTE_C3, 16, NOTE_D3, 16, NOTE_E3, 16, NOTE_F3, 16, NOTE_D3, 16, NOTE_E3, 16, NOTE_C3, 16,

// measure 2
NOTE_G3, 8, NOTE_G2, 8 , REST, 4, REST, 16, NOTE_G3, 16, NOTE_A3, 16, NOTE_B3, 16, NOTE_C4, 16, NOTE_A3, 16, NOTE_B3, 16, NOTE_G3, 16,

// measure 3
NOTE_C4, 8, NOTE_B3, 8, NOTE_C4, 8, NOTE_D4, 8, NOTE_E4, 8, NOTE_G3, 8, NOTE_A3, 8, NOTE_B3, 8,

// measure 4
NOTE_C4, 8, NOTE_E3, 8, NOTE_FS3, 8, NOTE_G3, 8, NOTE_A3, 8, NOTE_B3, 8, NOTE_C4, 4,

// measure 5
NOTE_C4, 16, NOTE_D3, 16, NOTE_E3, 16, NOTE_FS3, 16, NOTE_G3, 16, NOTE_E3, 16,
NOTE_FS3, 16, NOTE_D3, 16, NOTE_G3, 8, NOTE_B2, 8, NOTE_C3, 8, NOTE_D3, 8,
// measure 6
NOTE_E3, 8, NOTE_FS3, 8, NOTE_G3, 8, NOTE_E3, 8, NOTE_B2, 136, NOTE_C3, 16, NOTE_D3, 8, NOTE_D2, 8,

// measure 7
REST, 16
};

void setup() {
  initTomatoCube();
  pixelLED(0);
  setStarRGB(0x00, 0x00, 0x00);
}

// the loop function runs over and over again forever
void loop() {
     scanTouchButton();
     if (getTouchB1Transition()) {
          const char *songNotes = inv1_lh;
          unsigned char size = sizeof(inv1_lh);
          int led = 1;

          size = (size/sizeof(unsigned char))/2;  // Number of music notes (freq + duration)
          
          for (int thisNote = 0; thisNote < size; thisNote++) {
        
            int noteDuration = 0;
            if (songNotes[(thisNote * 2) + 1] < 128) {
              // regular note, just proceed
              noteDuration = (getWholeNote()) / (songNotes[(thisNote * 2) + 1]);
            } else {
              noteDuration = (getWholeNote()) / ((songNotes[(thisNote * 2) + 1]) - 128);
              noteDuration *= 1.5; // increases the duration in half for dotted notes
            }

            pixelLED(led);
            playTone(TONE_PINOUT, songNotes[(thisNote * 2)], noteDuration);
            led <<= 1;
            if (led > 0x80) led = 1;

            // to distinguish the notes, set a minimum time between them.
            int pauseBetweenNotes = noteDuration * 1.30;
            delay(pauseBetweenNotes);
          
          }
          playTone(TONE_PINOUT, REST, 100);

     }
     pixelLED(0);
    setStarRGB(0x00, 0x00, 0x00);
      
  
}
