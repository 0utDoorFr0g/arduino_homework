#include <Servo.h>

// Arduino pin assignment

#define PIN_SERVO 10
#define PIN_IR A0

// configurable parameters

#define _DUTY_HOR 1500 // natural position of servo in which the framework remains horizontal  
#define _DUTY_CW  _DUTY_HOR - 150 // clockwise position without breaking the framework
#define _DUTY_CCW _DUTY_HOR + 150 // counterclockwise position without breaking the framework

#define _IR_ALPHA 67 // one of the variables used to calculate the dist_cali
#define _IR_BETA 265 // one of the variables used to calculate the dist_cali

#define _DIST_MIN 100 // minimum distance a table-tenis ball can be detected in the framework
#define _DIST_TGT 255 // distance at which the table-tenis ball should be located in the framework
#define _DIST_MAX 400 // maximum distance a table-tenis ball can be detected in the framework

#define _EMA_ALPHA 0.1 // constant used when calculating EMA

// global variables

Servo myservo;
float EMA_S;


void setup() 
{

  // initialize servo

  myservo.attach(PIN_SERVO);
  myservo.writeMicroseconds(_DUTY_HOR);

  // initialize EMA filter's variable

  EMA_S = 0.0;

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

  // calculate EMA
  
  EMA_S = (_EMA_ALPHA * dist_cali) + ((1-_EMA_ALPHA)*EMA_S); 

  // calculate servo duty

  float servo_duty = -0.8 * EMA_S + (float)_DUTY_CCW + 50;

  // control servo motor
  
   myservo.writeMicroseconds((int)servo_duty);

 // debug code

  Serial.print("min:0,max:500");
//  Serial.print(dist_raw);
//  Serial.print(",dist_cali:");
//  Serial.print(dist_cali);
  Serial.print(",EMA:");
  Serial.print(EMA_S);
  Serial.print(",DUTY:");
  Serial.println(servo_duty);
}
