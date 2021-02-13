/*
 * Name: millis vs Delay
 * created: 24/08/2020
 * Author: NTJA
 */
#include <DHT.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

#define DHTPin  12
#define DHTType DHT11

LiquidCrystal_I2C lcd(0x27, 16, 2); 
DHT dht11(DHTPin, DHTType);

unsigned long previousMillis = 0;
long interval = 2000;     // leer cada 2 seg.

void setup() {
  Serial.begin(9600);
  dht11.begin();
  lcd.init();
  lcd.backlight();                  
  delay(500);  
}

void loop() {
 unsigned long currentMillis = millis();
 int tempC;
 int hum;
 char symbol = 223;
 
  if ( (currentMillis - previousMillis) >= interval ){
    previousMillis = currentMillis;

    tempC = dht11.readTemperature();
    hum = dht11.readHumidity();

    lcd.setCursor(0,0);
    Serial.print(" Temperatura: "); 
    Serial.print(tempC);
    lcd.print("tempC: ");
    lcd.print(tempC);
    lcd.print(symbol);
    lcd.print("C");
    
    lcd.setCursor(0,1);
    Serial.print("°C /");  
    Serial.print(" Humedad: "); 
    Serial.print(hum);
    Serial.println("%");  
    lcd.print("Humedad: ");
    lcd.print(hum);
    lcd.print("%");     
    Serial.print("Millisegundos "); 
    Serial.println(previousMillis); 
  }
}
