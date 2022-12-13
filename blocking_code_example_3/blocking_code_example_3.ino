
#include <U8g2lib.h>
#define START_BTN 4

U8X8_SSD1306_128X64_NONAME_HW_I2C display(U8X8_PIN_NONE);
int count = 10;
char buf[10]; // text buffer; to be able to use draw2x2String to show the value

void setup() {
  Serial.begin(9600);
  ////////// Display screen + Button initialization - not important //////////
  pinMode(START_BTN, INPUT_PULLUP);
  display.begin();
  display.setPowerSave(0);

  // wait until button pressed to proceed:
  // (this while statement halts the program, until the button is pressed)
  while(digitalRead(START_BTN)==HIGH) ; // note the empty statement: ';' does nothing, thus waits for START_BTN to be pressed (becomes LOW)
}

void loop() {
  if (count>=0) { // if counter not finished
    snprintf(buf, 10, "%2d", count);
    display.draw2x2String(4,3,buf); // show the counter
    count = count - 1; // decrease counter
  }
  delay(1000); // wait one second
}
