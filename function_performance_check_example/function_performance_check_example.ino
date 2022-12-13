void taskOneFunction() {
  //some task, for demonstration we will use a for loop
  for(int i=0;i<10;i++) {
    delay(100);
  }
}

void taskTwoFunction() {
  //some task, for demonstration we will use a for loop
  for(int i=0;i<10;i++) {
    Serial.print("The current iteration is: ");
    Serial.println(i);
    delay(100);
  }
}


void setup() {
  Serial.begin(9600);
}

void loop() {
  int startTime1=millis();
  taskOneFunction();
  int endTime1_startTime2=millis();
  taskTwoFunction();
  int endTime2=millis();

  Serial.print("Function one took this time to execute: ");
  // the time to execute function one is the time when it finished minus when it started
  Serial.println(endTime1_startTime2 - startTime1);
  
  Serial.print("Function two took this time to execute: ");
  // the time to execute function two is the time when it finished minus when it started
  Serial.println(endTime1_startTime2 - startTime1); 
  
  Serial.println(); // new line for tidy prints
}
