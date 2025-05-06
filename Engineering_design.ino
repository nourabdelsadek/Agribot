#include <SoftwareSerial.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
SoftwareSerial espSerial(2 , 12);
#define SERVOMIN  150 
#define SERVOMAX  600 
#define USMIN     600 
#define USMAX     2400
#define SERVO_FREQ 50
#define ENs 3  
#define msf 4  
#define msb 7  
#define m1f 11
#define m1b 10
#define EN1 6
#define m2f 9
#define m2b 8
#define EN2 5

void seed(){
  analogWrite(ENs , 170);
  digitalWrite(msf , HIGH);
  digitalWrite(msb , LOW);
  delay(180);
  digitalWrite(ENs , LOW);
}
void forward(){
  analogWrite(EN1 , 170);
  analogWrite(EN2 , 170);
  digitalWrite(m1f , HIGH);
  digitalWrite(m1b , LOW);
  digitalWrite(m2f , HIGH);
  digitalWrite(m2b , LOW);
}
void stop(){
  digitalWrite(EN1 , LOW);
  digitalWrite(EN2 , LOW);
}
void backward(){
  analogWrite(EN1 , 170);
  analogWrite(EN2 , 170);
  digitalWrite(m1f , LOW);
  digitalWrite(m1b , HIGH);
  digitalWrite(m2f , LOW);
  digitalWrite(m2b , HIGH);
} 
void setServoAngle(uint16_t angle) {
    if (angle > 180) angle = 180;
    uint16_t pulse = map(angle, 0, 180, SERVOMIN, SERVOMAX);
    pwm.setPWM(0, 0, pulse);
}
void cut(){
for(int i = 0 ; i <= 80 ; ++i){
    setServoAngle(i);
    delay(10);
  }
  for(int i = 80 ; i >= 0 ; --i){
    setServoAngle(i);
    delay(10);
  }
}
void setup() {
  Serial.begin(9600);
  espSerial.begin(9600);
  pinMode(m1f , OUTPUT);
  pinMode(m1b , OUTPUT);
  pinMode(EN1 , OUTPUT);
  pinMode(m2f , OUTPUT);
  pinMode(m2b , OUTPUT);
  pinMode(EN2 , OUTPUT);
  pinMode(msf , OUTPUT);
  pinMode(msb , OUTPUT);
  pinMode(ENs , OUTPUT);
  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(SERVO_FREQ);
}
String Read(){
    String x = espSerial.readStringUntil('\n');
    x.trim();
    return x;
}
void loop() {
  if(espSerial.available()) {
    String R = Read();
    if(R == "F") forward();
    else if(R == "B") backward();
    else if(R=="C") cut();
    else if(R=="S") seed();
    else stop();
  }
}