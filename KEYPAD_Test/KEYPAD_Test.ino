
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

#define Password_Length 8 

int signalPin = 12;

char Data[Password_Length]; 
char Master[Password_Length] = "123A456"; 
byte data_count = 0, master_count = 0;
bool Pass_is_good;
char customKey;

const byte ROWS = 4;
const byte COLS = 4;

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {33,35,37,39}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {41,43,45,47}; //connect to the column pinouts of the keypad

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

LiquidCrystal_I2C lcd(0x27, 20, 4);  

void setup(){
  Serial.begin(9600);
  lcd.init(); 
  lcd.backlight();
  pinMode(signalPin, OUTPUT);
  digitalWrite(signalPin, LOW); 
 Serial.println("Enter Password:");
}

void loop(){

  lcd.setCursor(0,0);
  lcd.print("Enter Password:");
 
  customKey = customKeypad.getKey();
  if (customKey){
    Data[data_count] = customKey; 
    lcd.setCursor(data_count,1); 
    lcd.print(Data[data_count]); 
    Serial.print(Data[data_count]);    
    data_count++; 
    }

  if(data_count == Password_Length-1){
    lcd.clear();

    if(!strcmp(Data, Master)){
      lcd.setCursor(2,1);
      lcd.print("Correct  ");
      Serial.println("Correct");    
      digitalWrite(signalPin, HIGH); 
      delay(5000);
      digitalWrite(signalPin, LOW );
      }
    else{
      lcd.setCursor(2,1);
      lcd.print("Incorrect");
     Serial.println("Incorrect");    
      delay(1000);
      }    
    lcd.clear();
    clearData();  
  }
}

void clearData(){
  while(data_count !=0){
    Data[data_count--] = 0; 
  }
  return;
}
