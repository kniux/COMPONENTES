/*  ___   ___  ___  _   _  ___   ___   ____ ___  ____  
 * / _ \ /___)/ _ \| | | |/ _ \ / _ \ / ___) _ \|    \ 
 *| |_| |___ | |_| | |_| | |_| | |_| ( (__| |_| | | | |
 * \___/(___/ \___/ \__  |\___/ \___(_)____)___/|_|_|_|
 *                  (____/ 
 *As an example for this lesson I will make a circuit 
 *that will turn on a relay to control some high voltage 
 *things when the sensor will detect an object.
 * Tutorial URL http://osoyoo.com/2017/07/27/arduino-lesson-pir-motion-sensor/
 * CopyRight www.osoyoo.com
 */
int ledPin = 13;                // choose the pin for the LED
int relayInput = 12;             // choose the pin for the relay
int inputPin = 11;               // choose the input pin (for PIR sensor)
int pirState = LOW;             // we start, assuming no motion detected
int val = 0;                    // variable for reading the pin status
 
void setup() {
  pinMode(ledPin, OUTPUT);      // declare LED as output
  pinMode(inputPin, INPUT);     // declare sensor as input
  pinMode(relayInput, OUTPUT);  // declare relay as output
  digitalWrite(relayInput, HIGH);//assuming relay is off
  Serial.begin(9600)
  ;
}
 
void loop(){
  val = digitalRead(inputPin);  // read input value
  if (val == HIGH) {            // check if the input is HIGH
    digitalWrite(ledPin, HIGH);  // turn LED ON
    if (pirState == LOW) {
      // we have just turned on
      Serial.println("Motion detected!");
      // We only want to print on the output change, not state
      pirState = HIGH;
      digitalWrite(relayInput, LOW); // The Relay Input works Inversly
      Serial.println("Turn on the Lamp!");
      Serial.println("Wait for 1 seconds");
      delay(1000);              // delay for 30 seconds
      digitalWrite(relayInput, HIGH);// Relay input operation is positive
      Serial.println("Turn off the Lamp!");
    }
  } 
  else 
  {
    digitalWrite(ledPin, LOW); // turn LED OFF
    if (pirState == HIGH)
    {
      // we have just turned of
      Serial.println("Motion ended!");
      // We only want to print on the output change, not state
      pirState = LOW;
    }
  }
}
