const int BUTTON_PIN = 3;
const int LED_PIN = 13;
int sensorValue1 = 1;
int sensorValue2 = 1;
int count = 0;
int countPush = 0;

void setup() {
	// put your setup code here, to run once:
	Serial.begin(9600);
	pinMode(BUTTON_PIN, INPUT_PULLUP);
	//digitalRead(BUTTON_PIN) would be 0 when pushed, 1 when not
	pinMode(BUTTON_PIN, INPUT);
	pinMode(LED_PIN, OUTPUT);
	digitalWrite(LED_PIN,LOW); 
}

void loop() {
	// put your main code here, to run repeatedly:
	// use sensorValue1 to store the value for the 0th,2th,4th,...time the loop runs
	if (count%2 == 0){
		sensorValue1 = digitalRead(BUTTON_PIN);
		//flash LED when the button is pushed
		if (sensorValue1 == 0){
			digitalWrite(LED_PIN,HIGH);
		}
		else{
			digitalWrite(LED_PIN,LOW); 
		}

		if (sensorValue1 == 0 && sensorValue2 == 1){
			countPush = countPush + 1;
			Serial.println(countPush);
		}
	}
	// use sensorValue2 to store the value for the 1th,3th,5th,...time the loop runs
	else {
		sensorValue2 = digitalRead(BUTTON_PIN);
		if (sensorValue2 == 0){
			digitalWrite(LED_PIN,HIGH);
		}
		else{
			digitalWrite(LED_PIN,LOW); 
		}

		if (sensorValue1 == 1 && sensorValue2 == 0){
			countPush = countPush + 1;
			Serial.println(countPush);
		}
	}
	
	count = count + 1;// record number of times the loop runs
}
