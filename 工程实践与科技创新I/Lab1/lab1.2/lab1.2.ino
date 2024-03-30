void setup() {                
  pinMode(RED_LED, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  digitalWrite(RED_LED, HIGH);
  delay(2000);
  digitalWrite(RED_LED, LOW);
  delay(2000);
  digitalWrite(RED_LED, HIGH);
  delay(100);
  digitalWrite(RED_LED, LOW);
  delay(100);
}
