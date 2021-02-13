/*

  Autor: bitwiseAr  

*/

#define PULSADOR 5      // pulsador en pin 2
#define BUZZER_ACTIVO 12     // buzzer activo en pin 8

void setup (){
  pinMode (PULSADOR, INPUT_PULLUP); // pin 2 como entrada con resistencia de pull-up
  pinMode (BUZZER_ACTIVO, OUTPUT);  // pin 12 como salida
}

void loop (){
  if(digitalRead(PULSADOR) == LOW){   // si se ha presionado el pulsador
    for(int i = 0; i < 5; i++){     // bucle repite 5 veces
      digitalWrite(BUZZER_ACTIVO, HIGH);  // activa buzzer
      delay (500);        // demora de medio segundo
      digitalWrite(BUZZER_ACTIVO, LOW);   // apaga buzzer
      delay (500);        // demora de medio segundo
    }
  } 
}
