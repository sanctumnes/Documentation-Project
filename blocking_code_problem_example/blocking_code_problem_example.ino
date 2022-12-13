const int buttonPin = 5;
bool flag = true;
void setup() {
  Serial.begin(9600);
}

void loop() {
  if(flag) {
    Serial.println("Executing Task 1 Every 5 Seconds");
    /*
    SOME CODE FOR TASK 1 
    SOME CODE FOR TASK 1
    SOME CODE FOR TASK 1
    */
    Serial.println("Task 1 Done");
    delay(5000);
  
    if(digitalRead(buttonPin) == LOW) {
      flag = false;
    }  
  }
  else {
    Serial.println("Task 1 Stopped Executing!");
  }
}
