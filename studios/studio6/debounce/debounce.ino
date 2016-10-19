// reference code from : https://www.arduino.cc/en/Tutorial/Debounce
// problem fixed by adding the variable lastReading

const int buttonPin = 3;
const int ledPin = 13;

int ledState = 0;         // the current state of the output pin
int buttonState = 1;             // the current button state
int lastButtonState = 1;   // the previous button state

int countPush = 0;         // number of times the button is pushed
int reading = 1;           // input reading: 0 when pushed, 1 when not
int lastReading = 1;

unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

void setup() {
	Serial.begin(9600); 
	pinMode(buttonPin, INPUT_PULLUP);// 0 when pushed, 1 when not
	pinMode(ledPin, OUTPUT);

	// set initial LED state
	digitalWrite(ledPin, LOW);
}

void loop() {
	reading = digitalRead(buttonPin);

	// check to see if you just pressed the button
	// (i.e. the input went from LOW to HIGH),  and you've waited
	// long enough since the last press to ignore any noise:

	// If the switch changed, due to noise or pressing:
	if (reading != lastReading) {
		// reset the debouncing timer
		lastDebounceTime = millis();
	}

	// if wait long enough, take the reading as the real button state
	if (millis() - lastDebounceTime > debounceDelay) {
		buttonState = reading;
		
		if (buttonState==0 && lastButtonState==1){
			ledState = 1;
			countPush = countPush + 1;
			Serial.println(countPush);
		}
		else{
			ledState = 0;
		}	
		
		lastButtonState = buttonState;
	}

	digitalWrite(ledPin, ledState);

	lastReading = reading;
}
