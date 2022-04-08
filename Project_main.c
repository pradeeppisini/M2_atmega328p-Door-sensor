
#include <LiquidCrystal.h>

#include <Servo.h>
Servo myservo;

const int rs = A0, en = A1, d4 = A2, d5 = A3, d6 = A4, d7 = A5;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int pos = 120;
#define trigPin 7
#define echoPin 6
#define trigPin1 4
#define echoPin1 5

#define led 13
//#define led2 11


int sonerCheak = 1, sc, count = 0, sonerCheak1 = 1, sc1;
void setup() {
  lcd.begin(16, 2);
  Serial.begin (9600);
  myservo.attach(9);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(led, OUTPUT);
  //pinMode(led2, OUTPUT);
  myservo.write(pos);
  lcd.print("Welcome!!");

}


long microsecondsToCentimeters(long microseconds)
{

  return microseconds / 29 / 2;
}




void loop() {
  long duration, distance, duration1, distance1;
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
  //  delayMicroseconds(1000); - Removed this line
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = microsecondsToCentimeters(duration);

  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  duration1 = pulseIn(echoPin1, HIGH);
  distance1 = microsecondsToCentimeters(duration1);


  if (distance < 10) {
    sc = 1;
  } else {
    sc = 0;
  }

  if (distance1 < 10) {
    sc1 = 1;
  } else {
    sc1  = 0;
  }

  if (sonerCheak == sc) {

    if (count < 6) {
      count++;
      lcd.setCursor(0, 1);
      lcd.print("Car=");
      lcd.print(count);
    } else {
      count == 6;
    }

  }
  sonerCheak = sc + 1;


  if (sonerCheak1 == sc1) {

    if (count > 0) {
      count--;
      lcd.setCursor(0, 1);
      lcd.print("Car=");
      lcd.print(count);
    } else {
      count = 0;
      lcd.setCursor(8, 1);

    }

  }
  sonerCheak1 = sc1 + 1;
Serial.println(distance);
 
  if (distance <= 10 && distance1 >= 10 && count <= 6) {
    pos = 50;
    digitalWrite(led, HIGH);
    myservo.write(pos);
    delay(1000);

  } else {
    pos = 120;
    myservo.write(pos);
    if (count >= 6) {
      lcd.setCursor(8, 1);
      lcd.print("FULL");
    }

  }


  if (distance1 <= 10 && distance >= 10&& count <= 6) {
    pos = 50;

    digitalWrite(led, HIGH);
    myservo.write(pos);


  } else {
    pos = 120;
    myservo.write(pos);
 
  }



}
