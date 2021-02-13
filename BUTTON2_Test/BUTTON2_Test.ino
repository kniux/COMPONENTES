/*
  maneja el brillo del LED mediante el potenciometro.
  Autor: bitwiseAr  
*/

int sensorPin = A0;    // select the input pin for the potentiometer
int ledPin = 9;      // select the pin for the LED
int sensorValue = 0;  // variable to store the value coming from the sensor

void setup(){
  pinMode(ledPin, OUTPUT);   // pin 3 como salida
  Serial.begin (9600);  
  // las entradas analogicas no requieren inicializacion
}

void loop(){
  sensorValue = analogRead(sensorPin)/4;  // valor leido de entrada analogica divido por 4
  analogWrite(ledPin, sensorValue);    // brillo del LED proporcional al giro del potenciometro
  Serial.print("Valor = ");
  Serial.println(sensorValue);    
}
