
#define redLED 9
#define greenLED 7
#define gasSensor A0
int gasStatus=0;

void setup(){
  pinMode(redLED, OUTPUT);	// initialize digital pin Red LED as an output.
  pinMode(greenLED, OUTPUT);  // initialize digital pin Red LED as an output.
  pinMode(gasSensor, INPUT);  // initialize gas sensor pin input.    
  Serial.begin(9600);   // initialize serial for debugging
}

void loop(){
  gasStatus=digitalRead(gasSensor);
  if (gasStatus==0) {
    digitalWrite(redLED,LOW);
    digitalWrite(greenLED,HIGH);   
  } else {
    digitalWrite(redLED,HIGH);
    digitalWrite(greenLED,LOW);   
  }
}
