unsigned clock=0; // in 10ms
unsigned buttoncount=0;
unsigned buttonstate=0; // 0 for off and 1 for on

// the setup routine runs once when you press reset:
void setup() {
  // Serial.begin(9600);
  pinMode(PUSH2, INPUT_PULLUP);
  pinMode(RED_LED, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  // red
  int but = digitalRead(PUSH2);
  if (but!=buttonstate && but==LOW){
    delay(1);
    if(digitalRead(PUSH2)==LOW) buttoncount++;
  }
  buttonstate=but;
  if (buttoncount%4) digitalWrite(RED_LED, LOW);
  else digitalWrite(RED_LED, HIGH);
}
