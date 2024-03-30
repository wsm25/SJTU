const int  buttonPin = PUSH2;    // the pin that the pushbutton is attached to
const int ledPin = RED_LED;       // the pin that the LED is attached to

int buttonPushCounter = 0;   // counter for the number of button presses
int lastButtonState = 0;     // previous state of the button

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int buttonState = digitalRead(buttonPin);

  // compare the buttonState to its previous state
  if (buttonState != lastButtonState) {
    // if the state has changed, increment the counter
    if (buttonState == LOW) { // button down
      buttonPushCounter++;
      Serial.print("times of button pushes:  ");
      Serial.println(buttonPushCounter);
    } 
    else { // button up
      Serial.println("button up"); 
    }
  }
  lastButtonState = buttonState;

  if (buttonPushCounter % 4 == 0) {
    digitalWrite(ledPin, HIGH);
  } else {
   digitalWrite(ledPin, LOW);
  }
  
}








