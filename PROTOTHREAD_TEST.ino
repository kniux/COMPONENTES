/*
 * NAME: PROTOTHREAD_TEST
 * AUTHOR: EDGAR CANO
 * DATE: 07/06/2021
 * VER: 0.1
 * DESCR:   - Para mostrar la ejecuión concrrente,
 *          - tres leds parpadean asincronamente
 *          - 1.0 s, 0.5 s y 0.25 s, respectivamente.
 */

#include <pt.h>
struct pt hilo1;    // Equivale  a un proceso concurrente 
struct pt hilo2;
struct pt hilo3;

#define redPin   9
#define yellowPin 8
#define greenPin  7

void setup(){
  PT_INIT(&hilo1);   // Exige inicializar la variable utilizando un macro
  PT_INIT(&hilo2);   // requiere un puntero (valor de la DIR. MEMORIA)
  PT_INIT(&hilo3);   // donde se almacena el valor de la estructura.
}
void loop() {
  blinking1(&hilo1);   
  blinking2(&hilo2);
  blinking3(&hilo3);
}

// Pasar como un parametro un puntero
void blinking1(struct pt *pt){
  /*Aqui inicia protothread*/
  PT_BEGIN(pt);                       //donde comienza el proto, pero requiere un puntero a la estructura
  static long previousMillis = 0;   
  //void setup
   pinMode(redPin,OUTPUT);
 //  void loop() {
  do{
      digitalWrite(redPin,HIGH);
     //equivalente a delay(1000);
      previousMillis= millis();
      PT_WAIT_WHILE(pt, (millis()-previousMillis)<1000);       // espera un segundo.
      digitalWrite(redPin,LOW);
      previousMillis = millis();
      PT_WAIT_UNTIL(pt, (millis()-previousMillis)>=1000);       // espera un segundo.     
   }while(true);
  PT_END(pt);   
}

void blinking2(struct pt *pt){
  /*Aqui inicia protothread*/
  PT_BEGIN(pt);     
  static long previousMillis = 0;   
  //void setup
   pinMode(yellowPin,OUTPUT);
 //  void loop() {
  do{
      digitalWrite(yellowPin,HIGH);     
      previousMillis = millis();
      PT_WAIT_WHILE(pt, (millis()-previousMillis)<500);      
      digitalWrite(yellowPin,LOW);
      previousMillis = millis();
      PT_WAIT_UNTIL(pt, (millis()-previousMillis)>=500);       
   }while(true);
  PT_END(pt);   
}
void blinking3(struct pt *pt){
  /*Aqui inicia protothread*/
  PT_BEGIN(pt);     
  static long previousMillis = 0;   
  //void setup
   pinMode(greenPin,OUTPUT);
 //  void loop() {
  do{
      digitalWrite(greenPin,HIGH);     
      previousMillis = millis();
      PT_WAIT_WHILE(pt, (millis()-previousMillis)<250);       
      digitalWrite(greenPin,LOW);
      previousMillis = millis();
      PT_WAIT_UNTIL(pt, (millis()-previousMillis)>=250);      
   }while(true);
  PT_END(pt);   
}
//End of Code
