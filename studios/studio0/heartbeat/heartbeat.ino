int i = 0;

void setup() {
	Serial.begin(9600);
}

void loop() {
	i = i + 1;
	Serial.print(i);
	Serial.println("sec have elapsed");
	delay(1000);
}
