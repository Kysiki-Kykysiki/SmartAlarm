#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const long max_time = 60000;
long delalay = 0;
long cur_time = 0;
byte moves = 0;

void setup() {
  Serial.begin(9600);
  lcd.backlight();
  // put your setup code here, to run once:
  lcd.init();
  lcd.print("-SmartAlarm-");
  lcd.setCursor(0,1);
  lcd.print("Status: Calm");
  pinMode(2, INPUT);
  pinMode(7, INPUT);
  pinMode(9, OUTPUT);
  pinMode(3, OUTPUT);
}

void Alert(){
  if(digitalRead(2)==HIGH){
  lcd.setCursor(0,0);
  lcd.print("AUTOMATIC ALERT");
  lcd.setCursor(0,1);
  lcd.print("Status: Alert");
  tone(9,31);
  digitalWrite(3,HIGH);
  delay(10000);
  }
  if (digitalRead(7)==HIGH){
  lcd.setCursor(0,0);
  lcd.print("MANUAL ALERT");
  lcd.setCursor(0,1);
  lcd.print("Status: Alert");
  digitalWrite(9,HIGH);
  digitalWrite(3,HIGH);
  delay(15000);
  }
}

void Time() {
  cur_time = millis() - delalay;
  if(max_time - cur_time <= 0){
    delalay = millis();
  }else{
    if(digitalRead(2)==HIGH){
      moves += 1;
    }
    if(moves >= 5){
    moves = 0;
    lcd.setCursor(0,0);
    lcd.print("INTRUDER ALERT");
    lcd.setCursor(0,1);
    lcd.print("Status: Alert");
    tone(9,31);
    digitalWrite(3,HIGH);
    delay(10000);
    }
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.clear();
  Serial.println(digitalRead(7));
  Alert();
  // Time();
  noTone(9);
  lcd.setCursor(0,0);
  lcd.print("-SmartAlarm-");
  lcd.setCursor(0,1);
  lcd.print("Status: Calm");
  digitalWrite(9,LOW);
  digitalWrite(3,LOW);
  delay(100);
}
