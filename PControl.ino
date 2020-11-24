#include <Servo.h>

// Arduino pin assignment

#define PIN_SERVO 10
#define PIN_IR A0

// configurable parameters

#define _DUTY_CW  1450 // clockwise position without breaking the framework
#define _DUTY_HOR 1600 // natural position of servo in which the framework remains horizontal  
#define _DUTY_CCW 1750 // counterclockwise position without breaking the framework

#define _IR_ALPHA 67 // one of the variables used to calculate the dist_cali
#define _IR_BETA 265 // one of the variables used to calculate the dist_cali

// global variables

Servo myservo;


void setup() 
{

  // initialize servo

  myservo.attach(PIN_SERVO);
  myservo.writeMicroseconds(_DUTY_HOR);

  // add your code

  // initialize serial port

  Serial.begin(57600);  

  delay(1000);
}

float ir_distance(void) // return value unit: mm
{ 
  float val;
  float volt = float(analogRead(PIN_IR));
  val = ((6762.0/(volt-9.0))-4.0) * 10.0;
  return val;
}

void loop() 
{
  float dist_raw = ir_distance();
  float dist_cali = 100 + 300.0 / (_IR_BETA - _IR_ALPHA) * (dist_raw - _IR_ALPHA);

  // add your code

  Serial.print("min:0,max:500,dist:");
  Serial.print(dist_raw);
  Serial.print(",dist_cali:");
  Serial.println(dist_cali);
}
