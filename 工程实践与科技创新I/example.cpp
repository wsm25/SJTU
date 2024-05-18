void cb1();

void setup() {                
  pinMode(RED_LED, OUTPUT);
  pinMode(PUSH1, INPUT_PULLUP);
  attachInterrupt(PUSH2, cb1, FALLING);
}

// the loop routine runs over and over again forever:
void loop() {
  digitalWrite(GREEN_LED, HIGH);
  digitalRead(PUSH1); // HIGH is up, LOW is down
}
