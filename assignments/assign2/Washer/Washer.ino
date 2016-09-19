//Fill in the values below with the pins that you chose to use
const int POT_PIN = A0;
const int BUTTON_PIN = 3;

const int HOT_PIN = 8;
const int COLD_PIN = 9;
const int DRY_PIN = 10;
const int LOCK_PIN = 13;

int optionVal = 0;

void setup() {
	Serial.begin(9600);
	pinMode(BUTTON_PIN, INPUT_PULLUP);
	pinMode(LOCK_PIN, OUTPUT);
	//13: blue LED indicates locked
	digitalWrite(LOCK_PIN, LOW);
	//set to not locked, before pressing button
}

void loop() {
	int sensorValue = digitalRead(BUTTON_PIN);
	// Test how the button works: 1 as default, 0 when pushed
	//	Serial.print("Value:");
	//	Serial.println(sensorValue, DEC);

	// when button's not pressed -> locked, light on
	if (sensorValue == HIGH){
		digitalWrite(LOCK_PIN, HIGH);
	}
	else {
		digitalWrite(LOCK_PIN, LOW);
	}

	optionVal = analogRead(POT_PIN); 
	// read the value from the sensor
	// Test below
	Serial.println(optionVal);
	// print out values 0 - 1023 (counterclock)
	digitalWrite(HOT_PIN,HIGH);
	delay(100); // stop the program for 0.1 sec
}