void setup() {                
  pinMode(RED_LED, OUTPUT);
  pinMode(PUSH2, INPUT_PULLUP);
}

void blink(uint32_t latency){
  digitalWrite(RED_LED, HIGH);
  delay(latency);
  digitalWrite(RED_LED, LOW);
  delay(latency);
}

void loop() {
  // read the state of the pushbutton value:
  int buttonState = digitalRead(PUSH2);

  if (buttonState == HIGH) { // not pressed
    blink(2000);
  } 
  else {
    blink(100);
  }
}
