#include <LiquidCrystal.h>
LiquidCrystal lcd(12,11,5,4,3,2);

const int PIN_DOOR = 7;
const int PIN_TRIG = 13;
const int PIN_ECHO = 8;
const int PIN_LED_IN = 9;
const int PIN_LED_OUT = 10;

int door_state;
int cnt = 0;

void setup() {
  Serial.begin(9600);
  pinMode(PIN_DOOR, INPUT_PULLUP);
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
  pinMode(PIN_LED_IN, OUTPUT);
  pinMode(PIN_LED_OUT, OUTPUT);

  lcd.begin(16, 2);
  lcd.display();
}

void loop() {
  lcd.clear();
  
  door_state = digitalRead(PIN_DOOR);
  lcd.setCursor(0,0);
  if (door_state == HIGH) {
    lcd.print("Door: open");
  } else {
    lcd.print("Door: closed");
  }


  lcd.setCursor(0,1);
  long duration, distance;
  digitalWrite(PIN_TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(PIN_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);
  duration = pulseIn(PIN_ECHO, HIGH);

  distance = duration * 17 / 1000;

  if (distance >= 400 || distance <= 2) {
    lcd.print("Dist range over");
  } else {
    lcd.print("Dist: ");  
    lcd.setCursor(6,1);
    lcd.print(distance);
    if (distance < 10) {
      lcd.setCursor(8,1);
    } else if (distance < 100) {
      lcd.setCursor(9,1);
    } else {
      lcd.setCursor(10,1);
    }
    lcd.print("cm");
  }

  if (door_state == HIGH) {
    if (distance < 50) {
      digitalWrite(PIN_LED_IN, HIGH);
      digitalWrite(PIN_LED_OUT, LOW);
      delay(10000);
    } else {
      digitalWrite(PIN_LED_IN, LOW);
      digitalWrite(PIN_LED_OUT, HIGH);
      delay(10000);
    }
  }
  
  delay(1000);
}
