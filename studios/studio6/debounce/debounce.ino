// original code from : https://www.arduino.cc/en/Tutorial/Debounce
// edited

const int buttonPin = 3;
const int ledPin = 13;

int ledState = HIGH;         // the current state of the output pin
int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin
int countPush = 0;

unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

void setup() {
	Serial.begin(9600); 
//	pinMode(buttonPin, INPUT_PULLUP);// 0 when pushed, 1 when not
	pinMode(buttonPin, INPUT);
	pinMode(ledPin, OUTPUT);

	// set initial LED state
	digitalWrite(ledPin, LOW);
}

void loop() {
	int reading = digitalRead(buttonPin);
//	Serial.print("button reading: ");
//	Serial.println(reading);

	// check to see if you just pressed the button
	// (i.e. the input went from 1 to 0),  and you've waited
	// long enough since the last press to ignore any noise:

	// If the switch changed, due to noise or pressing:
	if (reading != lastButtonState) {
		// reset the debouncing timer
		lastDebounceTime = millis();
	}

	// PROBLEM: when you don't touch the button, the statement here is going to be true
	if ((millis() - lastDebounceTime) > debounceDelay) {

		// whatever the reading is at, it's been there for longer
		// than the debounce delay, so take it as the actual current state:

//		Serial.print("interval: ");
//		Serial.println(millis() - lastDebounceTime);
		
		// it will be longer and longer if you don't push the button
		
		// if the button state has changed:
		if (reading != buttonState) {
			buttonState = reading;
			countPush = countPush + 1;
			Serial.println(countPush);

			if (buttonState == HIGH) {
				ledState = !ledState;
			}
		}
	}

	// set the LED:
	digitalWrite(ledPin, ledState);

	// save the reading.  Next time through the loop,
	// it'll be the lastButtonState:
	lastButtonState = reading;
}
