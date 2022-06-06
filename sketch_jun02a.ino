#include <Wire.h>

#define m3 10
#define m1 5
#define m2 6
#define m4 11
#define Echo A0
int distance;
#define Speed 100
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(m1, OUTPUT);
  pinMode(m2, OUTPUT);
  pinMode(m3, OUTPUT);
  pinMode(m4, OUTPUT);
}

void loop()
{
  Obstacle();
  voicecontrol();
  // put your main code here, to run repeatedly:
}
void voicecontrol()
{
    if (Serial.available() == 1)
  {
    String val = Serial.readString();
    Serial.println(val);
    if (val == "forward")
    {
      Stop();
      Forward();
    }
    if (val == "backward")
    {
      Stop();
      Backward();
    }
    if (val == "left")
    {
      Stop();
      Left();
    }
    if (val == "right")
    {
      Stop();
      Right();
    }
    if(val == "stop")
    {
      Stop();
    }
  }

}
void Obstacle()
{
  distance = ultrasonic();
  if(distance <= 20)
  {
    Stop();
    Backward();
    delay(1000);
    Stop();
    int L = ultrasonic();
    delay(800);
    int R = ultrasonic();
    delay(800);
    if( L < R)
    {
      Right();
      delay(500);
      Stop(); 
    }
    else if(L > R)
    {
      Left();
      delay(500);
      Stop();
    }
    else
    {
      Forward();
    }
  }
}

int ultrasonic()
{
  digitalWrite(Trig, LOW);
  delayMicroseconds(4);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);
  long t = pulseIn(Echo, HIGH);
  long cm = t/29/2;
  return cm;
}
void Forward()
{
  analogWrite(m1, Speed);
  analogWrite(m3, Speed);
}
void Backward()
{
  analogWrite(m2, Speed);
  analogWrite(m4, Speed);
}
void Right()
{
  analogWrite(m3, Speed);
}

void Left()
{
  analogWrite(m1, Speed);
}
void Stop()
{
   analogWrite(m1, 0);
   analogWrite(m2, 0);
   analogWrite(m3, 0);
   analogWrite(m4, 0);
}
