#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

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

void loop() {
  // put your main code here, to run repeatedly:
  lcd.clear();
  Serial.println(digitalRead(7));
  if(digitalRead(2)==HIGH){
    lcd.setCursor(0,0);
    lcd.print("INTRUDER ALERT");
    lcd.setCursor(0,1);
    lcd.print("Status: Alert");
    digitalWrite(9,HIGH);
    digitalWrite(3,HIGH);
  }else if (digitalRead(7)==HIGH){
    lcd.setCursor(0,0);
    lcd.print("MANUAL ALERT");
    lcd.setCursor(0,1);
    lcd.print("Status: Alert");
    digitalWrite(9,HIGH);
    digitalWrite(3,HIGH);
    }else{
    lcd.setCursor(0,0);
    lcd.print("-SmartAlarm-");
  lcd.setCursor(0,1);
  lcd.print("Status: Calm");
  digitalWrite(9,LOW);
  digitalWrite(3,LOW);
  }
  delay(100);
}
