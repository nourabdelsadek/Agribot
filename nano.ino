#define IR 2
#define whiteLed 4
#define greenLed 5
int planting_time = 10000;
struct ultrasonic {
  int trig;
  int echo;
  ultrasonic(int T , int E) {
    trig = T;
    echo = E;
  }
  
  float dist() {
    digitalWrite(trig, LOW);
    delayMicroseconds(2);
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);
    long duration = pulseIn(echo, HIGH);
    float distance = (duration * 0.034) / 2.0;
    return distance;
  }
};

ultrasonic rear(12 , 11);
ultrasonic front(10 , 9);
ultrasonic seeds(8 , 7);
void func(){
  if(seeds.dist() < 5) digitalWrite(whiteLed , HIGH);
  while(front.dist() > 20){
    Serial.println("F");
    delay(500);
    Serial.println("Stop!");
    delay(250);
    Serial.println("S");
    delay(250);
  }
  Serial.println("Stop!");
  while(rear.dist() > 6) Serial.println("B");
  digitalWrite(whiteLed , LOW);
  digitalWrite(greenLed , HIGH);
  Serial.println("Stop!");
  delay(planting_time);
  digitalWrite(greenLed , LOW);
  while(rear.dist() < 75){
    if(!digitalRead(IR)){
      Serial.println("Stop!");
      delay(100);
      Serial.println("C");
      delay(100);
    }
    else{
      Serial.println("F");
    }
  }
  Serial.println("Stop!");
  while(rear.dist() > 6) Serial.println("B");
  Serial.println("Stop!");
  digitalWrite(greenLed , HIGH);
}
void setup() {
  Serial.begin(9600);
  pinMode(12 , OUTPUT);
  pinMode(11 , INPUT);
  pinMode(10 , OUTPUT);
  pinMode(9 , INPUT);
  pinMode(8 , OUTPUT);
  pinMode(7 , INPUT);
  pinMode(IR , INPUT);
  pinMode(whiteLed , OUTPUT);
  pinMode(greenLed , OUTPUT);
  func();
}

void loop() {}