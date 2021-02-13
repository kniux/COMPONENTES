 /* From:
      How To Mechatronics
*/
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd (0x27, 16, 2);

#define outputA 4
#define outputB 3
#define outputSW 5

int counter = 0;
int aState;
int aLastState;
uint8_t button_state=1;

uint8_t Falling_edge(int btn) {
  uint8_t newValue = digitalRead(btn);
  uint8_t result = button_state!=newValue && newValue == 0;
  button_state = newValue;
  return result;
}

void setup(){ 
  pinMode(outputA, INPUT_PULLUP);
  pinMode(outputB, INPUT_PULLUP);
  pinMode(outputSW, INPUT_PULLUP);
  Serial.begin(9600);  
  lcd.init();
  lcd.clear();
  lcd.backlight();

  aLastState = digitalRead(outputA);
}

void loop(){
  aState = digitalRead(outputA);
  /* Hubo un cambio en la señal A*/
  
  if(Falling_edge(outputSW)){
   Serial.println("SW"); 
   lcd.setCursor(12,1);
   lcd.print("SW"); 
  }
  if( aState != aLastState ){
    lcd.clear();
    if( digitalRead(outputB) != aState ){   // en sentido CW siempre A!=B
      counter ++;
    }else{
      counter --;
    }  
    Serial.print("Position: ");   
    Serial.println(counter);
    lcd.setCursor(12,0);
    lcd.print(counter); 
  }
  aLastState = aState;                  // Actualizando última lectura de A
}
