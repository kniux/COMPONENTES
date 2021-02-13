/*  ___   ___  ___  _   _  ___   ___   ____ ___  ____  
 * / _ \ /___)/ _ \| | | |/ _ \ / _ \ / ___) _ \|    \ 
 *| |_| |___ | |_| | |_| | |_| | |_| ( (__| |_| | | | |
 * \___/(___/ \___/ \__  |\___/ \___(_)____)___/|_|_|_|
 *                  (____/ 
 * This is the Arduino Hello Worls sketch.
 *This example will show you how to read IR remote codes 
 *from any IR remote using the VS1838B IR receiver and 
 *an Arduino. Once you can receive codes from individual 
 *button presses, your remote control and Arduino become 
 *a general purpose, short range, communication interface!
 * Tutorial URL http://osoyoo.com/2017/07/20/arduino-lesson-ir-remotecontrol/
 * CopyRight www.osoyoo.com
 */
#include <IRremote.h>  // use the IRRemote.h

const int irReceiverPin = 6;  //the SIG of receiver module attach to pin2
unsigned long codigo;

IRrecv irrecv(irReceiverPin); //Creates  a variable of type IRrecv
decode_results results;    

void setup()
{
  Serial.begin(9600);    //initialize serial,baudrate is 9600
  irrecv.enableIRIn();   // enable ir receiver module
}

void loop() 
{
  if (irrecv.decode(&results)) //if the ir receiver module receiver data
  {  
    Serial.print("irCode: ");    //print "irCode: "        
    Serial.print(results.value, HEX); //print the value in hexdecimal 
    Serial.print(",  bits: ");  //print" , bits: "         
    Serial.println(results.bits); //print the bits
      if (codigo == results.value){
          Serial.print("Es el Codigo: ");    //print "irCode: "        
          Serial.println(codigo);
          Serial.println(codigo,HEX);
      }

    
    irrecv.resume();    // Receive the next value 
  }  
  delay(600); //delay 600ms
}
