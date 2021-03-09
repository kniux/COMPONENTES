int SENSOR = 0; // pin S de modulo a entrada analogica A0
int LED = 10;   // LED en pin 10
int VALOR;      // almacena valor leido de entrada A0

void setup(){
  pinMode(LED, OUTPUT);   // pin 10 como salida
  // entradas analogicas no requieren inicialización
}

void loop(){
  VALOR = analogRead(SENSOR); // lee valor de entrada A0
  if (VALOR < 500){   // un valor bajo representa oscuridad
    digitalWrite(LED, HIGH);  // enciende LED
    delay(1000);    // demora de 1 seg. para evitar parpadeo de LED
  }
  digitalWrite(LED, LOW); // apaga LED
}
