/* stoplight
 *  
 *  CSE 132 - Studio 3
 *  
 *  Fill this out so we know whose studio this is.
 *  
 *  Name: Yangchen Shen
 *  WUSTL Key: sheny
 *  
 *  Name:
 *  WUSTL Key:
 *  
 *  Name:
 *  WUSTL Key:
 *  
 *  Name:
 *  WUSTL Key:
 */
enum State {
	up0,        // NSG
	up1,        // NSY
	up2,        // EWG
	up3,        // EWY
	up4,        // PED
};

State counterState = up0; 

unsigned long accumulator = 0;
const int interval = 3041;
void setup() {
	// put your setup code here, to run once:
	pinMode(12,OUTPUT);//blue - walk
	pinMode(11,OUTPUT);//yellow - don't walk

	pinMode(10,OUTPUT);//EW green
	pinMode(9,OUTPUT);//EW yellow
	pinMode(8,OUTPUT);//EW red

	pinMode(6,OUTPUT);//NS red
	pinMode(5,OUTPUT);//NS yellow
	pinMode(4,OUTPUT);//NS green

}

void loop() {
	// put your main code here, to run repeatedly:
	if(millis() - accumulator > interval) { 
		accumulator += interval; 
		counterState = nextState(counterState);
	}
}

State nextState(State state) {
	switch (state) {
	case up0:               
		digitalWrite(4,HIGH);
		digitalWrite(8,HIGH);
		digitalWrite(11,HIGH);
		state = up1;
		break;                       

	case up1:               
		digitalWrite(4,LOW);
		digitalWrite(5,HIGH);
		state = up2;
		break;

	case up2:
		digitalWrite(5,LOW);
		digitalWrite(8,LOW);
		digitalWrite(6,HIGH);
		digitalWrite(10,HIGH);
		state = up3;
		break;

	case up3:
		digitalWrite(10,LOW);
		digitalWrite(9,HIGH);
		state = up4;
		break;

	case up4:
		digitalWrite(9,LOW);
		digitalWrite(8,HIGH);
		digitalWrite(12,HIGH);
		state = up5;
		break;
	}
	return state;
}

