
#include <LiquidCrystal_I2C.h>
#include <Wire.h>


//--- RGB&Buzzer PINS----------------------------------------------------------------------------------
int redPin = 24;      //Define el pin del arduino en que estará conectado el pin del led RGB rojo.
int greenPin = 23;    //Define el pin del arduino en que estará conectado el pin del led RGB verde.
int bluePin = 22;     //Define el pin del arduino en que estará conectado el pin  del led RGB azul.

//---------------------DEFINIENDO BOTONES --------------------------------------------------------------
#define BTN_GREEN 0
#define BTN_RED   1
#define BTN_BLUE  2

// Este arreglo contiene los pines utilizados para los botones
uint8_t button[3] = {
  5,
  4,
  3
};

// Este arreglo contiene el último state conocido de cada línea
uint8_t button_state[3];

LiquidCrystal_I2C lcd(0x27, 20, 4); //set the LCD address to 0x27 for a 16 chars and 2 line display
/*---------------------------------------------------------------------------------------------*/
/*                               Control_Subsystem
/*---------------------------------------------------------------------------------------------*/
void setup() {
  // Configurar como PULL-UP para ahorrar resistencias
  pinMode(button[BTN_RED], INPUT_PULLUP);
  pinMode(button[BTN_BLUE], INPUT_PULLUP);
  pinMode(button[BTN_GREEN], INPUT_PULLUP);

  // Se asume que el state inicial es HIGH
  button_state[0] = HIGH;
  button_state[1] = HIGH;
  button_state[2] = HIGH;
  
  lcd.init();
  lcd.backlight();
  delay(500);

  LCD_screenHOME();  
}

// Facilita la detección de flancos de subidan en los pines
// monitoreados. Asume la existencia de un arreglo button
// con la asignación actual de pines y un arreglo button_state
// con los valores de línea
uint8_t Rising_edge(int btn) {
  uint8_t newValue = digitalRead(button[btn]);
  uint8_t result = button_state[btn]!=newValue && newValue == 1;
  button_state[btn] = newValue;
  return result;
}
void RGB_setColor(int r, int g, int b) {
  analogWrite(redPin, r);
  analogWrite(greenPin, g);
  analogWrite(bluePin, b);
}
/******************* DRAW_Management ****************************/
void LCD_screenHOME(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(" Set RGB");
}
void LCD_screenRED(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Set RED");
}
void LCD_screenGREEN(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Set GREEN");
}
void LCD_screenBLUE(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Set BLUE");
}

void loop() {
 if(Rising_edge(BTN_RED)) { 
   RGB_setColor(255,0,0);
   LCD_screenRED();        
 }  
  if(Rising_edge(BTN_BLUE)) { 
   RGB_setColor(0,0,255);
   LCD_screenBLUE();        
 }
  if(Rising_edge(BTN_GREEN)) { 
   RGB_setColor(0,255,0);
   LCD_screenGREEN();        
 }
}
  
