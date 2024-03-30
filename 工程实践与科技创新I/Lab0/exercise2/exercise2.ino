void setup() {                
  pinMode(RED_LED, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  digitalWrite(RED_LED, HIGH);
  delay(250);
  digitalWrite(RED_LED, LOW);
  delay(250);
}
