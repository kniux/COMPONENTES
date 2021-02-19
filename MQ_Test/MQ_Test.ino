int VALOR;      // almacena valor leido del sensor

void setup(){
  Serial.begin(9600);   // inicializa comunicacion serie a 9600 bps
  // entradas analogicas no requieren inicializacion
}

void loop(){
  VALOR = analogRead(A0); // lee entrada A0 y asigna a variable VALOR
  Serial.println(VALOR);  // imprime en monitor serial el valor
  delay(500);     // breve demora de medio segundo
}
