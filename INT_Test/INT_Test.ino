volatile int cont = 0;
int anterior = 0;

void setup() {
  pinMode(2, INPUT_PULLUP);  
  pinMode(10, OUTPUT);  
  
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(2),service, RISING);
}

void loop() {
  if (anterior != cont){
    Serial.println(cont);
    anterior = cont;
  }
}
// Interrupt Service Routine
void service(){
  cont++;
}
