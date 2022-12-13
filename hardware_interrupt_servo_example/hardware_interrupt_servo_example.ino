#include <ESP32Servo.h>

/*
Button struct with the following feature for each button:
  1. PIN - Button pin number
  2. numberKeyPresses - Counter that counts how many times the button has been pressed
  3. pressed - Boolean variable indicating wether the button has been pressed or not
*/

struct Button {
  const uint8_t PIN;
  uint32_t numberKeyPresses;
  bool pressed;
};

// initialization of a new button, button1, with pin=19, numberKeyPresses=0, pressed=false
Button button1 = {19, 0, false};

//defining servo pin number, and a new servo object 
const int servoPin = 18;
Servo servo;

//pos=index of current angle, deltaAngle=difference between current angle and previous angle 
int pos = 0;
int deltaAngle=10;

//state of the button - pressed or not
int state;

/*
PinMode(PIN,INPUT_PULLUP) Explanation

When we press the button, the value is always LOW, but when we release it it’s quite random: sometimes HIGH, sometimes LOW, and it moves a lot.

We see this because the voltage for the button is floating between 0 and 5V.

If the voltage is below a certain amount of V, the Arduino will read LOW.

And if it is above a certain amount of V, the Arduino will read HIGH.

As there is no internal or external voltage reference for the push button, the value will oscillate a lot in a random way.

And as you can foresee, we can’t rely on this data to take decisions inside our Arduino program.

What we need to do is to “force” the default state (button not pushed) to be close to HIGH or LOW, which will make it quite stable.

Then, when we press the button the state will simply go to the opposite of the default state.

When you set the mode to INPUT_PULLUP, an internal resistor – inside the Arduino board – will be set between the digital pin 4 and VCC (5V).

This resistor will make sure the state stays HIGH. When you press the button, the states becomes LOW.
*/


/*
attachInterrupt(pin, ISR, mode) Explanation
  1. pin = which pin will trigger the interrupt
  2. ISR = interrupt handler function - the function that will execute once the interrupt arises 
  3. mode = when to trigger an interrupt - FALLING mode = when the pin goes from digital HIGH to digital LOW

  for more information: https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/
*/
void setup() {
  Serial.begin(115200);
  servo.attach(servoPin); //attach servoPin to servo object
  servo.write(0);
  pinMode(button1.PIN, INPUT_PULLUP);
  attachInterrupt(button1.PIN, buttonPressHandler, FALLING); 
  state=digitalRead(button1.PIN);
}

// interrupt handler
void buttonPressHandler() {
  button1.numberKeyPresses++;
  button1.pressed = true;
  
  state=!state;

  if (state == LOW) {
    deltaAngle = 0;
    Serial.println("Interrupt Triggered to stop motor!");
    Serial.print("Button has been pressed ");
    Serial.print(button1.numberKeyPresses);
    Serial.println(" times!");
  }
  else {
    deltaAngle = 10;
    Serial.println("Interrupt Triggered to restart motor!");
    Serial.print("Button has been pressed ");
    Serial.print(button1.numberKeyPresses);
    Serial.println(" times!");
  }

  pos = 0;
}

void loop() {
  int angle;

  //rotate servo every 1 second by 10 degrees
  for(pos=0;pos<=18;pos++) {
    angle=pos*deltaAngle;
    servo.write(angle);
    Serial.print("Current Angle: ");
    Serial.println(angle);
    delay(1000);
  }

  //rotate servo every 1 second by 10 degrees in the opposite direction
  for(pos=18;pos>=0;pos--) {
    angle=pos*deltaAngle;
    servo.write(angle);
    Serial.print("Current Angle: ");
    Serial.println(angle);
    delay(1000);
  }
}
