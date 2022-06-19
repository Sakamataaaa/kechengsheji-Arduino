#include <Wire.h>
#include <LiquidCrystal_IC2.h>
#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT11
#define BUZ 10
#define REDLED 7
#define GREENLED 6
#define INCREASE 12
#define REDUCE 12

int MAX = 30;
int MIN = 10;

byte sheshidu[8] = {
  0b10000,
  0b00110,
  0b01001,
  0b01000,
  0b01001,
  0b00110,
  0b00000,
};

LiquidCrystal_I2C lcd(0x27, 16, 2);
DHT dht(DHTPIN DHTTYPE);

void lcdstart() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Welcome");
  lcd.setCursor(0, 1);
  lcd.print("Now Loading");
  lcd.createChar(0, wendu);
  delay(5000);
  lcd.clear();
}

void pinstart() {
  pinMode(BUZ, OUTPUT);
  pinMode(REDLED, OUTPUT);
  pinMode(GREENLED, OUTPUT);
  pinMode(INCREASE, INPUT);
  pinMode(REDUCE, INPUT);
}
void setup() {
  Serial.begin(9600);
  pinstart();
  lcdstart();
}

void loop() {
  int increase = digitalRead(INCREASE);
  int reduce = digitalRead(REDUCE);
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if (increase == HIGH) {
    MAX += 1;
  }
  if (reduce == HIGH) {
    MIN -= 1;
  }
  if (isnan(h) || isnan(t)) {
    Serial.println("Faild to Read");
    lcd.setCursor(0, 0);
    lcd.print("ERROR");
    tone(BUZ, 1);
    digitalWrite(REDLED, HIGH);
    digitalWrite(GREENLED, LOW);
  }
  else
  {
    if (t >= MAX) {
      digitalWrite(REDLED, HIGH);
      digitalWrite(GREENLED, LOW);
      tone(BUZ, 1);
    }
    if (t <= MIN) {
      digitalWrite(REDLED, HIGH);
      digitalWrite(GREENLED, LOW);
      tone(BUZ, 1);
    }
    digitalWrite(REDLED, LOW);
    digitalWrite(GREENLED, HIGH);
    notone(BUZ);
    lcd.setCursor(0, 0);
    lcd.print("Hum:     %MAX:");
    lcd.setCursor(0, 1);
    lcd.print("Tem:      MIN:");
    lcd.setCursor(9, 1);
    lcd.write(byte(0));
    lcd.setCursor(4, 0);
    lcd.print(h);
    lcd.setCursor(4, 1);
    lcd.print(t);
    lcd.setCursor(14, 0);
    lcd.print(MAX);
    lcd.setCursor(14, 1);
    lcd.print(MIN);
  }
  delay(2000);
  lcd.clear();
}
