void setup() {
  Serial.begin(9600);

}

void loop() {
  Serial.println("Hello!");
  for(int i=0; i<1000; i++) {
    Serial.println("This Loop Is A Blocking Code!");
  }
  Serial.println("Hello Again!");
}
