volatile int state=HIGH;
volatile int intbutton=LOW;
int count=0;

void blink(){
    state=!state;
    intbutton=HIGH;
}

void setup(){
    Serial.begin(9600);
    pinMode(GREEN_LED, OUTPUT);
    digitalWrite(GREEN_LED, state);
    pinMode(PUSH2, INPUT_PULLUP);
    attachInterrupt(PUSH2, blink, FALLING);
}

void loop(){
    if(!intbutton) return;
    digitalWrite(GREEN_LED, state);
    Serial.println(count++);
    intbutton=LOW;
}