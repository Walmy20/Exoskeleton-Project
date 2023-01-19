// Walmy Marine ME-59904 Exoskeleton Virtual Wall Control
#include <Servo.h> 
#include "HX711.h"
#define calibration_factor -250.0 //This value is obtained using the SparkFun_HX711_Calibration sketch
#define DOUT  3
#define CLK  2

HX711 scale(DOUT, CLK);
int data=0;
uint8_t dataout[8];
int i=0;
Servo myservo;

float Weight;

void setup() {
  Serial.begin(9600);
  scale.set_scale(calibration_factor); //This value is obtained by using the SparkFun_HX711_Calibration sketch
  scale.tare();  //Assuming there is no weight on the scale at start up, reset the scale to 0
  myservo.attach(9);
  myservo.write(90); // set center position -> 90;
}

void loop() {

  delay(10);
  data=(int)scale.get_units();
  Serial.print("Grams = ");
  Serial.print(data);
  Serial.println();

  // maping the value of the force sensor which was calibrated using a water bottle
  int value = map(data,-500.0,500.0,10.0,-10.0);
  
  if (myservo.read()+value < 90)
  {
    myservo.write(myservo.read()+value);
    
    }
}
