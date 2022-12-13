/*
  Advanced countdown timer of which the time can be set with up/down/set buttons.

  Author: F. van Slooten
*/
#include <U8g2lib.h>
#include <Bounce2.h>

byte button_pins[] = {4, 5, 6 }; // button pins; 4/5 up/down, 6 = set

#define NUMBUTTONS sizeof(button_pins)

Bounce * buttons = new Bounce[NUMBUTTONS];

U8X8_SSD1306_128X64_NONAME_HW_I2C display(U8X8_PIN_NONE);

int min = 1, sec = 0; // start with one minute

unsigned long previousMillis = 0, previousMillis2 = 0; // will store last time timer was updated

const unsigned long interval = 1000; // 1 second

char buf[10]; // text buffer; to be able to use draw2x2String to show the value

int state = 0; // 0 = set minutes, 1 = set seconds, 2 = run timer (countdown), 3 = pause, 4 = finished

bool blink = true;

void setup() {
  Serial.begin(9600);

  // Make input & enable pull-up resistors on switch pins
  for (int i = 0; i < NUMBUTTONS; i++) {
    buttons[i].attach( button_pins[i] , INPUT_PULLUP  );       //setup the bounce instance for the current button
    buttons[i].interval(25);              // interval in ms
  }

  display.begin();
  display.setPowerSave(0);
  display.setFont(u8x8_font_pxplusibmcgathin_f);
  display.drawString(0, 7, "set minutes");
  sprintf(buf, "%02d:%02d", min, sec);
  display.draw2x2String(2, 3, buf);
}

void loop() {
  unsigned long currentMillis = millis();

  // blink time on display every 300ms when setting it:
  if (currentMillis - previousMillis2 > 300 ) { // 300ms passed?
    previousMillis2 = currentMillis; // save the last time
    blink = !blink;
    if (state == 0) { // set min
      if (blink) sprintf(buf, "%02d", min); // blink minutes
      else strcpy(buf, "  ");
      display.draw2x2String(2, 3, buf);
      sprintf(buf, "%02d", sec);
      display.draw2x2String(8, 3, buf);
    }
    else if (state == 1) { // set seconds
      sprintf(buf, "%02d", min);
      display.draw2x2String(2, 3, buf);
      if (blink) sprintf(buf, "%02d", sec);  // blink seconds
      else strcpy(buf, "  ");
      display.draw2x2String(8, 3, buf);
    }
  }

  // update countdown timer every second
  if (currentMillis - previousMillis > interval) { // interval passed?
    previousMillis = currentMillis; // save the last time
    if (state == 2) { // countdown running?
      if (min >= 0 && sec >= 0) { // if counter not finished
        sec--; // decrease timer
        if (sec < 0) {
          if (min > 0 ) {
            min--;
            sec = 59;
          }
          else sec = 0;
        }
      }
      if (min == 0 && sec == 0) { // if counter finished
        display.drawString(0, 7, "finished    ");
        state = 4;
      }
      sprintf(buf, "%02d:%02d", min, sec);
      display.draw2x2String(2, 3, buf);
    }
  }

  // check for pressed buttons
  for (int i = 0; i < NUMBUTTONS; i++) {
    // Update the Bounce instance :
    buttons[i].update();
    if ( buttons[i].fell() ) { // a button was pressed
      if (i == 2) { // select
        state++; // to next state
        if (state == 4) state = 2;
        if (state == 5) { // restart
          state = 0;
          min = 1; sec = 0;
          display.drawString(0, 7, "set minutes");
        }
        if (state == 1) display.drawString(0, 7, "set seconds");
        else if (state == 2) {
          sprintf(buf, "%02d:%02d", min, sec);
          display.draw2x2String(2, 3, buf);
          display.drawString(0, 7, "running     ");
        }
        else if (state == 3) display.drawString(0, 7, "pause       ");
      }
      else { // up / down
        if (state == 0) { // setting minutes
          if (i == 0) min++; // up
          else min--; // down
        }
        else { // setting seconds
          if (i == 0) sec++; // up
          else sec--; // down
          if (sec < 0) {
            sec = 59;
            min--;
          } else if (sec > 59) {
            sec = 0;
            min++;
          }
        }
        if (min < 0) min = 0;
      }
    }
  } // end for
}
