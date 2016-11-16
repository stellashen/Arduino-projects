//from sender.ino
//potentiometer
const int potPin = A5;
int potVal = 0;
int p1 = 0;
//delta time
unsigned long timeStamp = 0;
unsigned long t1=0;
unsigned long t2=0;
unsigned long t3=0;
unsigned long accumulator = 0;
const int interval = 1000;

void setup() {
	// put your setup code here, to run once:
	Serial.begin(9600);
}

void loop() {
	// put your main code here, to run repeatedly:
	if(timeStamp - accumulator > interval) { 
		accumulator += interval; 
		//0. debugging string
		Serial.write(0x21);
		Serial.write(0x30);
		Serial.write(0x00);
		Serial.write(0x04);
		Serial.write("Test");
		//1. timestamp: timeStamp
		Serial.write(0x21);
		Serial.write(0x32);
		t1 = timeStamp >> 24;
		t2 = timeStamp >> 16;
		t3 = timeStamp >> 8;
		Serial.write(t1);
		Serial.write(t2);
		Serial.write(t3);
		Serial.write(timeStamp);
		//2. the potentiometer reading: potVal
		potVal = analogRead(potPin);
		Serial.write(0x21);
		Serial.write(0x33);
		p1 = potVal >> 8;
		Serial.write(p1);
		Serial.write(potVal);
	}
}
