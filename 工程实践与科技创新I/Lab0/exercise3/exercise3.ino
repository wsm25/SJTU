
void setup() {                
  pinMode(GREEN_LED, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  digitalWrite(GREEN_LED, HIGH);
  delay(1000);
  digitalWrite(GREEN_LED, LOW);
  delay(1000);
}
