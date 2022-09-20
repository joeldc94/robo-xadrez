/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 https://www.arduino.cc/en/Tutorial/LibraryExamples/Sweep
*/

#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position
int cmd = 0;
int inByte = 0; 

void setup() {
    myservo.attach(10);  // attaches the servo on pin 9 to the servo object
    Serial.begin(9600);
    while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("Iniciado");
}

void loop() {
  if(cmd >= 0 && cmd <=180){
    //pos = inByte;
    //Serial.print("OK - pos:");
    //Serial.println(pos);
    if(cmd != pos){
      pos = cmd;
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
    }
  }
  else
    Serial.println("Valor inválido");

}



void serialEvent() {
  if(Serial.available()){
    inByte = Serial.parseInt(); // read the incoming byte:
    if(inByte > 0){
      Serial.print(" I received:");
      Serial.println(inByte);
      cmd = inByte;
    }
    if(inByte < 0){
      cmd = 0;
      Serial.print(" I received:");
      Serial.println(inByte);
    }
    //Serial.println(Serial.available());
  }
}
