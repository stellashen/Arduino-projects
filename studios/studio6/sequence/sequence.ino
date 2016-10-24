// store row pins in an array, and column pins in another array
int row[7] = {2,3,4,5,6,7,8};
int col[5] = {9,10,11,12,13};
int count = 0;
unsigned long accumulator = 0;

void setup() {
	Serial.begin(9600);
	for(int i = 0; i < 7; i++){
		pinMode(row[i], OUTPUT);
	}
	for(int i = 0; i < 5; i++){
		pinMode(col[i], OUTPUT);
	}

	// all LEDs off
	for(int i = 0; i < 7; i++){
		digitalWrite(row[i],LOW);
	}
	for(int i = 0; i < 5; i++){
		digitalWrite(col[i],HIGH);
	}
}

void loop() {
	//	// all LEDs off
	//	for(int i = 0; i < 7; i++){
	//		digitalWrite(row[i],LOW);
	//	}
	//	for(int i = 0; i < 5; i++){
	//		digitalWrite(col[i],HIGH);
	//	}
	//	delay(500);
	//	
	//	// all LEDs in first column on
	//	for(int i = 0; i < 7; i++){
	//		digitalWrite(row[i],HIGH); //R1-7 to HIGH
	//	}
	//	digitalWrite(col[0],LOW); //C1 to LOW
	//	delay(500);
	//	
	//	// only keep the LED (C1,R1) on, others off
	//	for(int i = 1; i < 7; i++){
	//		digitalWrite(row[i],LOW); //R2-7 to LOW
	//	}
	//	delay(500);
	//	
	//	Serial.println(count);

	if(count & B00000001){
		digitalWrite(row[0],HIGH);
	}
	else{
		digitalWrite(row[0],LOW);
	}
	if(count & B00000010){
		digitalWrite(row[1],HIGH);
	}
	else{
		digitalWrite(row[1],LOW);
	}
	if(count & B00000100){
		digitalWrite(row[2],HIGH);
	}
	else{
		digitalWrite(row[2],LOW);
	}
	digitalWrite(col[0],LOW);

	if (millis()-accumulator > 1000){
		accumulator += 1000;
		if (count < 7){
			count = count + 1;
		}
		else{
			count = 0;
		}
	}
}
