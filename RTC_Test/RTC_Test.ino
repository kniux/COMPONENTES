/*
 * Name: RTCDS3231
 * created: 24/08/2020
 * Author: NTJA
 */
#include "RTClib.h"
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); 
RTC_DS3231 rtc;

void setup() {
  Wire.begin();                             
  rtc.begin();
  /* obteniendo parametros de la PC */
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));  
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();                  
  delay(500);    
  lcd.setCursor(0, 0);
  lcd.print("TEST TEMPO Reloj");
  delay(2000);
  lcd.clear();
}

void loop() {
  displayFecha();
  displayHora();
  displayTemperatura();
  delay(1000);
}
void displayFecha(){
  DateTime now = rtc.now();
  char _bufferFecha[12];
  lcd.setCursor(0, 0);  
  formatoFecha( _bufferFecha, now.day(), now.month(), now.year() );
  lcd.print(_bufferFecha);
    Serial.print("Date: ");
    Serial.println(_bufferFecha);    
}
void displayHora(){
  DateTime now = rtc.now();
  char _bufferHora[10];
  lcd.setCursor(0, 1);  
  formatoHora( _bufferHora, now.hour(), now.minute(), now.second() );
  lcd.print(_bufferHora);

    Serial.print("Hora: ");
    Serial.println(_bufferHora);    
  
}
void formatoFecha(char bufferFecha[12], int numDia, int numMes, int numA){
  sprintf(bufferFecha, "%02d/%02d/%04d", numDia, numMes, numA);
}
void formatoHora(char bufferHora[10], int hora, int minu, int seg){
  sprintf(bufferHora, "%02d:%02d:%02d", hora, minu, seg);
}
void displayTemperatura(){
   char symbol = 223;
   
    Serial.print("Temperature: ");
    Serial.print(rtc.getTemperature());
    Serial.println(" C");
   
    lcd.setCursor(9, 1);  
    lcd.print(rtc.getTemperature());
    lcd.print(symbol);
    lcd.print("C");
}
