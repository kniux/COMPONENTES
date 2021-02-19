
#define redLED 9
#define greenLED 7
#define flameSensorA A0
#define flameSensorD 3

int flameDigital = 0;
float flameAnalog = 0; 

void setup(){
  pinMode(redLED, OUTPUT);	// initialize digital pin Red LED as an output.
  pinMode(greenLED, OUTPUT);  // initialize digital pin Red LED as an output.
  pinMode(flameSensorA, INPUT);  // initialize gas sensor pin input.    
  pinMode(flameSensorD, INPUT);  // initialize gas sensor pin input.    
  Serial.begin(9600);   // initialize serial for debugging
}

void loop(){
 delay(100);
 flameAnalog = analogRead(flameSensorA);
 flameDigital = digitalRead(flameSensorD);
 Serial.print("Valor Analogico: ");
 Serial.print(flameAnalog);
 Serial.print("   Valor Digital: ");
 Serial.println(flameDigital);
 
}
