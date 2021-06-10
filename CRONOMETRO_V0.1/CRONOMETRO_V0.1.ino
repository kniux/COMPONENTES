/*
 * NAME:    CRONOMETRO
 * AUTHOR:  EDGAR CANO
 * DATE:    09/06/2021
 * VER:     0.1
 * DESCR: - Cronometro implementado con la librería protothread (pt)
 *        - Para visualizar la ejecución de multitareas:
 *          * Se visualiza cronometro ascendente
 *          * boton 1 / reset de cronometro
 *          * boton 2 / pausa de cronometro   (en pausa se ejecuta secuencia de leds)       
 *          * boton 3 / para el manejo de opciones (funcionalidad no implementada)
 *          
 */

#include <pt.h>
#include <LiquidCrystal_I2C.h>

struct pt pt1;            // hilo para reloj
struct pt pt2;            // hilo para boton1
struct pt pt3;            // hilo para boton2
struct pt pt4;            // hilo para boton3
struct pt pt5;            // hilo para secuencia leds
struct pt pt6;            // hilo para Opciones 

int redPin    = 9;
int yellowPin = 8;
int greenPin  = 7;
int relePin   = 10;

// buffer 
char str_time[11] = "00:00:00.0";

LiquidCrystal_I2C lcd(0x27, 20,4);

// Funciones utilitarias
void formatTime(long timechrono, char *str_buffer) {
  int hours = (timechrono/36000)%24;
  int minutes = (timechrono/600)%60;
  int seconds = (timechrono/10)%60;
  int decimals = timechrono%10;  
  sprintf(str_buffer, "%02d:%02d:%02d.%01d", hours, minutes, seconds, decimals);
}

// Hilos
void reloj(struct pt *pt, long &counter, int &is_running, long &prog){
  PT_BEGIN(pt);
  static long v = 0;
  do{
    lcd.setCursor(0,0);
    formatTime(counter, str_time);
    lcd.print(str_time);

    if(is_running){
      counter++;
      /* Compararción entre (counter ==  prog)  RELE ON    */      
    }
    v = millis();
    PT_WAIT_WHILE(pt, ((millis() - v) < 100));
  }while(true);
  PT_END(pt);
}

void button1(struct pt *pt, int pin, long &counter, long &prog ){
  PT_BEGIN(pt);
  static long v = 0;         
  static int oldVal = 0; 
  static int newVal = 0;
  do{
    newVal = digitalRead(pin);
    // Detección de flanco con XOR
    if(((newVal ^ oldVal) == 1) && newVal == 0){
      //counter = 0;      // reinicio del crono
       counter = prog;
      
      // ignorando lecturas 200ms para descartar rebotes
      v = millis();
      PT_WAIT_WHILE(pt, ((millis() - v) < 200));
    }
    oldVal = newVal;
    PT_YIELD(pt);  // Cede el hilo permitiendo que tenga lugar otro proceso en el sistema
  }while(true);
  PT_END(pt);
}
void button2(struct pt *pt, int pin, int &is_running){
  PT_BEGIN(pt);
  static long v = 0;         
  static int oldVal = 0; 
  static int newVal = 0;
  do{
    newVal = digitalRead(pin);
    // Detección de flanco con XOR
    if(((newVal ^ oldVal) == 1) && newVal == 0){
      is_running ^= 1;      // intercambiando el valor con una asignación XOR por bit.
      // ignorando lecturas 200ms para descartar rebotes
      v = millis();
      PT_WAIT_WHILE(pt, ((millis() - v) < 200));
    }
    oldVal = newVal;
    PT_YIELD(pt);  // Cede el hilo permitiendo que tenga lugar otro proceso en el sistema
  }while(true);
  PT_END(pt);
}

void button3(struct pt *pt, int pin, int &is_running, int &tempo){
  PT_BEGIN(pt);
  static long v = 0;         
  static int oldVal = 0; 
  static int newVal = 0;
  do{
    newVal = digitalRead(pin);
    // Detección de flanco con XOR
    if(((newVal ^ oldVal) == 1) && newVal == 0){
      tempo++;
      // ignorando lecturas 200ms para descartar rebotes
      v = millis();
      PT_WAIT_WHILE(pt, ((millis() - v) < 200));
      Serial.println(tempo);
    }
    oldVal = newVal;    
    PT_YIELD(pt);  // Cede el hilo permitiendo que tenga lugar otro proceso en el sistema
  }while(true);
  PT_END(pt);
}
void led_sequence(struct pt *pt,int &is_running){
  PT_BEGIN(pt);
  static long v = 0;         
  static int ledVal = 1;   
  do{
    if(ledVal > 4){
      ledVal = 1;       // led a encender
    }
    if(is_running){    // Mientras este corriendo el cronometro, apagar leds
      digitalWrite(redPin,    LOW);
      digitalWrite(yellowPin, LOW);
      digitalWrite(greenPin,  LOW);
    }else{            // Mientras el cronometro este pausado, realizar secuencia
      // Mascara (AND)
      digitalWrite(redPin,  ledVal  & 1);      // primer  led ( 0000 0000 0000 0001)
      digitalWrite(yellowPin,  ledVal  & 2);   // segundo led ( 0000 0000 0000 0010)
      digitalWrite(greenPin,  ledVal  & 4);    // tercer  led ( 0000 0000 0000 0100)      
    }
    // Corrimiento a la izquierda de ledVal (multiplicación x 2)
    // Valor de  LedVAL antes de corrimiento 001, después 010, etc.
    ledVal = ledVal << 1;  
    
    v = millis();
    PT_WAIT_WHILE(pt, ((millis() - v) < 100));  // ejecución cada 100 mseg.
  }while(true);
  PT_END(pt);  
}
void screenTempo(struct pt *pt, int &tempo, long &prog){
  PT_BEGIN(pt);
  static long v = 0;
 do{
  lcd.setCursor(0,1);
  //lcd.clear();
  if(tempo == 0){
    lcd.print("TEMPO OFF");
    prog = 0;
  }
  if(tempo == 1){
    lcd.print("10 seg     ");
    prog = 100;
  }
  if(tempo == 2){
    lcd.print("20 seg     ");
    prog = 200;
  }
  if(tempo == 3){
    lcd.print("30 seg     ");
    prog = 300;
  }
  if(tempo == 4){    
    prog = 0;
  }   
    v = millis();
    PT_WAIT_WHILE(pt, ((millis() - v) < 100));  // ejecución cada 100 mseg. 
 }while(true);
  PT_END(pt); 
}

// Subsistema: Control
void setup() {
  PT_INIT(&pt1);
  PT_INIT(&pt2);
  PT_INIT(&pt3);
  PT_INIT(&pt4);
  PT_INIT(&pt5);
  PT_INIT(&pt6);
  pinMode(5, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(relePin, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  Serial.begin(9600);
  digitalWrite(relePin,HIGH);
  lcd.init();
  lcd.backlight();
  delay(500);
}

void loop() {
  static long t_sec = 0;
  static int is_running = 1;
  static int option = 0;
  static long timer = 0;
  reloj(&pt1, t_sec, is_running,timer);
  button1(&pt2, 5, t_sec,timer);                // Reset  
  button2(&pt3, 4, is_running);           // Inicio/pausa
  button3(&pt4, 3, is_running, option);   // opciones
  led_sequence(&pt5, is_running);         // secuencia de leds
  screenTempo(&pt6, option, timer);       // 
}

// End of code
