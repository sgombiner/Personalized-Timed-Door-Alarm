#include "arduino_secrets.h"

/*
  Control the color of an RGB LED using an ultrasonic distance sensor. When an object is close to the sensor, buzz the buzzer. Control the amount of time between buzzes with the potentiometer. 
*/

int potPosition;       //this variable will hold a value based on the position of the potentiometer
const int trigPin = 12;           //connects to the trigger pin on the distance sensor
const int echoPin = 11;           //connects to the echo pin on the distance sensor

const int redPin = 3;             //pin to control the red LED inside the RGB LED
const int greenPin = 5;           //pin to control the green LED inside the RGB LED
const int bluePin = 6;            //pin to control the blue LED inside the RGB LED

const int buzzerPin = 10;         //pin that will drive the buzzer

float distance = 0;               //stores the distance measured by the distance sensor


void setup()
{
  Serial.begin (9600);        //set up a serial connection with the computer

  pinMode(trigPin, OUTPUT);   //the trigger pin will output pulses of electricity
  pinMode(echoPin, INPUT);    //the echo pin will measure the duration of pulses coming back from the distance sensor

  //set the RGB LED pins to output
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  pinMode(buzzerPin, OUTPUT);   //set the buzzer pin to output
}

void loop() {
  distance = getDistance();   //variable to store the distance measured by the sensor
 potPosition = analogRead(A0);    //set potPosition to a number between 0 and 1023 based on how far the knob is turned
  Serial.print(distance);     //print the distance that was measured
  Serial.println(" in");      //print units after the distance
  Serial.print("  Potentiometer value:");
  Serial.println(potPosition);          //print the potentiometer value to the serial monitor

  if (distance <= 10) {                       //if the object is close

    //make the RGB LED Green

    analogWrite(redPin, 0);
    analogWrite(greenPin, 255);
    analogWrite(bluePin, 0);
    
    noTone(buzzerPin);            //turn the buzzer off
    delay(100);                   //wait 100 milliseconds
    
  } else if (10 < distance && distance < 20) { //if the object is a medium distance
  
   noTone(buzzerPin);
   delay(100);
    
    //make the RGB LED yellow
    analogWrite(redPin, 255);
    analogWrite(greenPin, 50);
    analogWrite(bluePin, 0);
    
    if (potPosition > 0 && potPosition <= 100)
      delay(1000);
    if (potPosition > 100 && potPosition <= 200)
      delay(2000);
    if (potPosition > 200 && potPosition <= 300)
      delay(3000);
    if (potPosition > 300 && potPosition <= 400)
      delay(4000);
    if (potPosition > 400 && potPosition <= 500)
      delay(5000);
    if (potPosition > 500 && potPosition <= 600)
      delay(6000);
    if (potPosition > 600 && potPosition <= 700)
      delay(7000);
    if (potPosition > 700 && potPosition <= 800)
      delay(8000);
    if (potPosition > 800 && potPosition <= 900)
      delay(9000);
    if (potPosition > 900 && potPosition <= 1023)
      delay(10000);

  } else {                                    //if the object is far away

    //make the RGB LED Red

    analogWrite(redPin, 255);
    analogWrite(greenPin, 0);
    analogWrite(bluePin, 0);
    
    //this code beeps the buzzer

    tone(buzzerPin, 1000);         //buzz the buzzer pin
    delay(100);                   //wait 100 milliseconds
  }

  delay(100);      //delay 50ms between each reading
}








//------------------FUNCTIONS-------------------------------

//RETURNS THE DISTANCE MEASURED BY THE HC-SR04 DISTANCE SENSOR
float getDistance()
{
  float echoTime;                   //variable to store the time it takes for a ping to bounce off an object
  float calculatedDistance;         //variable to store the distance calculated from the echo time

  //send out an ultrasonic pulse that's 10ms long
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  echoTime = pulseIn(echoPin, HIGH);      //use the pulsein command to see how long it takes for the
                                          //pulse to bounce back to the sensor

  calculatedDistance = echoTime / 148.0;  //calculate the distance of the object that reflected the pulse (half the bounce time multiplied by the speed of sound)

  return calculatedDistance;              //send back the distance that was calculated
}

