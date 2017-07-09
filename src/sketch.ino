#include <TimerOne.h>

const int     ledPin = 13;   // Led pin
const int   onoffPin = 8;    // On/off button pin
const int shutterPin = 3;    // camera/video button pin

#define ON   HIGH
#define OFF  LOW

void CAMERA_TURNON()
{
    Serial.print((float)millis()/1000,6); 
    Serial.println("=== initiate turnon sequence ===");
    digitalWrite(ledPin, ON);

    Serial.print((float)millis()/1000,6); 
    Serial.println(" Push on/off button for 5sec (long press) ...");
    digitalWrite(onoffPin, ON);    //Push on/off button 3sec for turn camcorder ON

    delay(5000);

    Serial.print((float)millis()/1000,6); 
    Serial.println(" Release ON/OFF Button");
    digitalWrite(onoffPin, OFF);    //Release button
    delay(3000);
    //YelOFF led on camera should be on
}

void CAMERA_TURNOFF()
{
    Serial.print((float)millis()/1000,6); 
    Serial.println("=== initiate turnoff sequence ===");
    digitalWrite(ledPin, ON);

    Serial.print((float)millis()/1000,6); 
    Serial.println(" Push on/off button for 5sec (long press)...");
    digitalWrite(onoffPin, ON);    //Push on/off button 5sec for turn camcorder ON

    delay(5000);

    Serial.print((float)millis()/1000,6); 
    Serial.println(" Release ON/OFF Button");
    digitalWrite(onoffPin, OFF);    //Release button
    delay(3000);
    //YelOFF led on camera should be off
}


void CAMERA_STARTREC()
{
    Serial.print((float)millis()/1000,6); 
    Serial.println("=== intiate video recording start sequence ===");

    Serial.print((float)millis()/1000,6); 
    Serial.println(" Push video/camera button 3sec (long press) ...");
    digitalWrite(shutterPin, ON);    //Push video/camera button for 10sec to start recording. 

    delay(3000);

    Serial.print((float)millis()/1000,6); 
    Serial.println(" Release video/camera Button");
    digitalWrite(shutterPin, OFF);    //Release button
    //YelOFF led should flash 3 times and off. 
}

void CAMERA_STOPREC()
{
    Serial.print((float)millis()/1000,6); 
    Serial.println("=== initiate video recording stop sequence ===");
    digitalWrite(ledPin, ON);

    Serial.print((float)millis()/1000,6); 
    Serial.println(" Push video/camera button for 300 msec (sort press)...");
    digitalWrite(shutterPin, ON);    //Push video/camera button for 300msec to stop recording. 

    delay(300);

    Serial.print((float)millis()/1000,6); 
    Serial.println(" Release video/camera Button");
    digitalWrite(shutterPin, OFF);    //Release button
    //YelOFF led on camera should be on
}

void CAMERA_WAIT()
{
    Serial.print((float)millis()/1000,6); 
    Serial.println("=== recording for 60 secs ===");
    delay(60000); //60sec
}

void setup() {
  pinMode(onoffPin, OUTPUT);
  digitalWrite(onoffPin, OFF);

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, OFF);

  pinMode(shutterPin, OUTPUT);
  digitalWrite(shutterPin, OFF);

  Serial.begin(9600);
  while (!Serial) ; // Wait for serial port to be available 
}

#define MAX 100
void loop()
{
    CAMERA_TURNON();

    for (int i=0;i<MAX;i++) {
	CAMERA_STARTREC();
	CAMERA_WAIT();
	CAMERA_STOPREC();
    }

    delay(1000);
    CAMERA_TURNOFF();

    while(1);
}
