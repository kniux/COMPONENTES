
int MIC = 11;        // D11 de modulo a pin 2
int LED = 10;        // anodo de LED a pin 3
int VALOR;        // variable para almacenar valor de D0
int ESTADO;       // variable para almacenar estado del LED


void setup(){
  pinMode(MIC, INPUT);      // pin 11 como entrada
  pinMode(LED, OUTPUT);     // pin 10 como salida
}


void loop(){
  VALOR = digitalRead(MIC);   // obtiene valor de A0
  if (VALOR == LOW){     // si A0 tiene un valor alto
    ESTADO = digitalRead(LED);    // almacena estado del led (encendido o apagado)
    digitalWrite(LED, !ESTADO);   // escribe en LED el valor opuesto al que tenia
    delay(500);       // demora de medio seg. para evitar pulsos espureos
  }
}
