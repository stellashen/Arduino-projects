//Fill in the values below with the pins that you chose to use
const int POT_PIN = A0;
const int BUTTON_PIN = 3;

const int HOT_PIN = 8;
const int COLD_PIN = 9;
const int DRY_PIN = 10;
const int LOCK_PIN = 13;

int optionVal = 0;
//int option = 0;
int sensorValue = 0;

enum State {
	// 0: idle state - wait for the next cycle
	// 1-2 : Economy cycle
	// 3-4 : Deluxe cycle
	// 5-7 : Super Delxue cycle
	up0,        
	up1,        
	up2,        
	up3,        
	up4,        
	up5,
	up6,
	up7
};

State counterState = up0; // current state

void setup() {
	Serial.begin(9600);
	pinMode(BUTTON_PIN, INPUT_PULLUP);
	pinMode(LOCK_PIN, OUTPUT);
	//13: blue LED indicates locked
	digitalWrite(LOCK_PIN, LOW);
	//set to not locked, before pressing button
}

void loop() {
	sensorValue = digitalRead(BUTTON_PIN);
	// Test how the button works: 1 as default, 0 when pushed
	//	Serial.print("Value:");
	//	Serial.println(sensorValue, DEC);

	// start push button
	// when button's pressed -> locked, light on
	//	if (sensorValue == LOW){
	//		digitalWrite(LOCK_PIN, HIGH);
	//	}

	counterState = nextState(counterState);
}

State nextState(State state){
	switch (state) {
	case up0:             

		digitalWrite(LOCK_PIN, LOW);
		digitalWrite(HOT_PIN, LOW);
		digitalWrite(COLD_PIN, LOW);
		digitalWrite(DRY_PIN, LOW);

		if (sensorValue == HIGH){
			state = up0;
			digitalWrite(LOCK_PIN, LOW);
		}
		else {
			//			digitalWrite(LOCK_PIN, HIGH);
			if (option() == 1){
				state = up1;
			}
			else if (option() == 2){
				state = up3;
			}
			else if (option() == 3){
				state = up5;
			}
			else{
				state = up0;
			}
		}
		break;                       

	case up1:              
		digitalWrite(LOCK_PIN, HIGH);
		digitalWrite(HOT_PIN, LOW);
		digitalWrite(COLD_PIN, HIGH);
		digitalWrite(DRY_PIN, LOW);
		delay(5000); // use 5s instead of 5min
		if (option() == 2){
			state = up4;
		}
		else if (option() == 3){
			state = up7;
		}
		else{
			state = up2;
		}
		break;

	case up2:
		digitalWrite(LOCK_PIN, LOW);
		digitalWrite(HOT_PIN, LOW);
		digitalWrite(COLD_PIN, LOW);
		digitalWrite(DRY_PIN, HIGH);
		delay(2000);
		state = up0;
		break;

	case up3:
		digitalWrite(LOCK_PIN, HIGH);
		digitalWrite(HOT_PIN, HIGH);
		digitalWrite(COLD_PIN, LOW);
		digitalWrite(DRY_PIN, LOW);
		delay(7000);
		if (option() == 1){
			state = up2;
		}
		else{
			state = up4;
		}
		break;

	case up4:
		digitalWrite(LOCK_PIN, HIGH);
		digitalWrite(HOT_PIN, LOW);
		digitalWrite(COLD_PIN, LOW);
		digitalWrite(DRY_PIN, HIGH);
		delay(7000);
		state = up0;
		break;

	case up5:
		digitalWrite(LOCK_PIN, HIGH);
		digitalWrite(HOT_PIN, HIGH);
		digitalWrite(COLD_PIN, LOW);
		digitalWrite(DRY_PIN, LOW);
		delay(7000);
		if (option() == 1){
			state = up2;
		}
		else{
			state = up6;
		}
		break;

	case up6:
		digitalWrite(LOCK_PIN, HIGH);
		digitalWrite(HOT_PIN, HIGH);
		digitalWrite(COLD_PIN, HIGH);
		digitalWrite(DRY_PIN, LOW);
		delay(7000);
		state = up7;
		break;

	case up7:
		digitalWrite(LOCK_PIN, HIGH);
		digitalWrite(HOT_PIN, LOW);
		digitalWrite(COLD_PIN, LOW);
		digitalWrite(DRY_PIN, HIGH);
		delay(7000);
		state = up0;
		break;
	}
	return state;
}

int option(){
	// Cycle knob
	optionVal = analogRead(POT_PIN); 
	// read the value from the sensor
	// Test below
	//Serial.println(optionVal);
	// print out values 0 - 1023 (counterclock)
	// 1023:economy, 400-600:deluxe, 0: super deluxe
	if (optionVal > 900){
		return 1; //economy
	}
	if (optionVal > 400 && optionVal < 600){
		return 2; //deluxe
	}
	if (optionVal < 100){
		return 3; //super deluxe
	}
}
