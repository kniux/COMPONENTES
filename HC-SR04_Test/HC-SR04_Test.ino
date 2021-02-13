#define echoPin 26
#define trigPin 25
#define LED     10

void setup() {
  Serial.begin (9600);
  pinMode(LED, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  float duration, distance;
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
 
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) * 0.0344;
  
  if (distance >= 400 || distance <= 2){
    Serial.print("Distance = ");
    Serial.println("Out of range");
  }
  else {
    Serial.print("Distance = ");
    Serial.print(distance);
    Serial.println(" cm");
    delay(500);

    if (distance <= 20 && distance >= 0){  // si distancia entre 0 y 20 cms.
       digitalWrite(LED, HIGH);      // enciende LED
       delay(distance * 10);        // demora proporcional a la distancia
       digitalWrite(LED, LOW);     // apaga LED
    }
    
  }
  delay(500);
}
