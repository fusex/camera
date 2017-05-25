#include <TimerOne.h>

const int ledPin = 13;     // Led pin
const int ButtonPin = 2;     // Sensor pin
const int onoffPin = 3;      // On/off pin  connect to transistor1 base with 1K resistor
const int shutterPin = 4;    // Shutter pin  connect to transistor2 base with 1K resistor

bool capturing = false;
bool startcapturing = false;
bool stopcapturing = false;

void setup() {
  pinMode(onoffPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(ButtonPin, INPUT);
  pinMode(shutterPin, OUTPUT);
  Serial.begin(9600);
  while (!Serial) ; // Wait for serial port to be available 
  Timer1.initialize(180000000);
  Timer1.attachInterrupt(togglecapturing); // attach the service routine here
}

int toverflow = 0;
void checktimer()
{
    if(toverflow++<3) return;
    toverflow=0;

    Serial.print((float)millis()/1000,6); 
}

void togglecapturing()
{
    checktimer();
    Serial.println(" timer handler");
    //Serial.print("Set capture to ");
    if(capturing) {
    	//Serial.println("OFF");
	//stopcapturing = true;

    } else {
    	//Serial.println("ON");
	startcapturing = true;
    }
    //capturing = !capturing;
}

void loop()
{
    delay(500);
    Serial.println("=== looping ===");
    if(startcapturing){
    noInterrupts();
	startcapturing = false;
    interrupts();
	Serial.println("=== Button pushed, initiate start sequence ===");
	capturing = true;
	digitalWrite(ledPin, HIGH);
	delay(300);

	digitalWrite(onoffPin, HIGH);    //Push on/off button 3sec for turn camcorder ON
	Serial.println("Push on/off button 3sec...");

	delay(3000);
	digitalWrite(onoffPin, LOW);    //Release button
	Serial.println("Release ON/OFF Button");
	delay(3000);

	digitalWrite(shutterPin, HIGH);  //Push record button 3 second to start video
	Serial.println("Push REC button 3 sec...");
	delay(3000);
	digitalWrite(shutterPin, LOW);    //Release button
	Serial.println("Release REC button");
    }
    if (stopcapturing) {
    noInterrupts();
	stopcapturing = false;
    interrupts();
	Serial.println("=== Button pushed, initiate stop sequence ===");
	digitalWrite(ledPin, LOW);
	capturing = false;

	digitalWrite(shutterPin, HIGH);  //Push record button once to stop video
	delay(300);
	Serial.println("Push REC button once");
	digitalWrite(shutterPin, LOW);    //Release button
	delay(2000);                      //Wait for copy to SD Card
	Serial.println("Should be copying to SD card...");
	// Shutdown
	digitalWrite(onoffPin, HIGH);    //Push on/off button 3sec for turn camcorder OFF
	Serial.println("Push OFF button 3sec");
	delay(3000);
	digitalWrite(onoffPin, LOW);     //Release button
	Serial.println("Camera should be turned off");
	digitalWrite(ledPin, LOW);
    }

    if(capturing){
	digitalWrite(ledPin, !digitalRead(ledPin));
    }

    delay(100);
}
