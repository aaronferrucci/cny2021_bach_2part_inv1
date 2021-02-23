/* 
 *  J.S. Bach's Two Part Inventions #1 
 *  Right-hand part
 *  
 */

#include "TomatoCubeWorker.h"

const PROGMEM char inv1_rh[] = {
// measure 1
REST, 16, NOTE_C4, 16, NOTE_D4, 16, NOTE_E4, 16, NOTE_F4, 16, NOTE_D4, 16,
NOTE_E4, 16, NOTE_C4, 16, NOTE_G4, 8, NOTE_C5, 8, NOTE_B4, 32, NOTE_A4, 32, NOTE_B4, 16, NOTE_C5, 8,

// measure 2
NOTE_D5, 16, NOTE_G4, 16, NOTE_A4, 16, NOTE_B4, 16, NOTE_C5, 16, NOTE_A4, 16,
NOTE_B4, 16, NOTE_G4, 16, NOTE_D5, 8, NOTE_G5, 8, NOTE_F5, 32, NOTE_E5, 32, NOTE_F5, 16, NOTE_G5, 8,

// measure 3
NOTE_E5, 16, NOTE_A5, 16, NOTE_G5, 16, NOTE_F5, 16, NOTE_E5, 16, NOTE_G5, 16,
NOTE_F5, 16, NOTE_A5, 16, NOTE_G5, 16, NOTE_F5, 16, NOTE_E5, 16, NOTE_D5, 16,
NOTE_C5, 16, NOTE_E5, 16, NOTE_D5, 16, NOTE_F5, 16,

// measure 4
NOTE_E5, 16, NOTE_D5, 16, NOTE_C5, 16, NOTE_B4, 16, NOTE_A4, 16, NOTE_C5, 16,
NOTE_B4, 16, NOTE_D5, 16, NOTE_C5, 16, NOTE_B4, 16, NOTE_A4, 16, NOTE_G4, 16,
NOTE_FS4, 16, NOTE_A4, 16, NOTE_G4, 16, NOTE_B4, 16,

// measure 5
NOTE_A4, 8, NOTE_D4, 8, NOTE_C5, 136, NOTE_D5, 16, NOTE_B4, 16, NOTE_A4, 16,
NOTE_G4, 16, NOTE_FS4, 16, NOTE_E4, 16, NOTE_G4, 16, NOTE_FS4, 16, NOTE_A4, 16,

// measure 6
NOTE_G4, 16, NOTE_B4, 16, NOTE_A4, 16, NOTE_C5, 16, NOTE_B4, 16, NOTE_D5, 16,
NOTE_C5, 16, NOTE_E5, 16, NOTE_D5, 16, NOTE_B4, 32, NOTE_C5, 32, NOTE_D5, 16,
NOTE_G5, 16, NOTE_B4, 8, NOTE_A4, 16, NOTE_G4, 16,

// measure 7
NOTE_G4, 8
};

void setup() {
  initTomatoCube();
  pixelLED(0);
  setStarRGB(0x0, 0x0, 0x0);
}

void playTone2(int pinToneOut, unsigned char note, int duration) {
  // Adjust this value to be in tune with the other board.
  // Larger value -> lower pitch
  long tv = 540000;
  unsigned long startMillis = millis();
  if (note == REST) {
      while ( (millis() - startMillis) < duration) {
            digitalWrite(pinToneOut, LOW); 
      }
  } 
  else {
      // int msDelay = 500000/(freqLookup(note));
      int msDelay = tv/(freqLookup(note));
      while ( (millis() - startMillis) < duration) {
            digitalWrite(pinToneOut, HIGH);   // turn the LED on (HIGH is the voltage level)
            delayMicroseconds(msDelay);                       // wait for a second
            digitalWrite(pinToneOut, LOW);    // turn the LED off by making the voltage LOW
            delayMicroseconds(msDelay);  
      }
  }
}

// the loop function runs over and over again forever
void loop() {
     scanTouchButton();
     if (getTouchB1Transition()) {
          const char *songNotes = inv1_rh;
          unsigned char size = sizeof(inv1_rh);
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
            playTone2(TONE_PINOUT, songNotes[(thisNote * 2)], noteDuration);
            led <<= 1;
            if (led > 0x20) led = 1;
      
            // to distinguish the notes, set a minimum time between them.
            int pauseBetweenNotes = noteDuration * 1.30;
            delay(pauseBetweenNotes);
          
          }
          playTone2(TONE_PINOUT, REST, 100);
  
     }
     pixelLED(0);

}
