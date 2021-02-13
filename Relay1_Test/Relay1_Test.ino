

//the relays connect to
int IN1 = 7;

#define ON   0
#define OFF  1
void setup()
{
  relay_init();//initialize the relay
}

void loop() {
  relay_SetStatus(ON);   //turn on RELAY_1
  delay(2000);
  relay_SetStatus(OFF);  //turn off RELAY_1
  delay(2000);
}
void relay_init(void){
  //set all the relays OUTPUT
  pinMode(IN1, OUTPUT);
  relay_SetStatus(OFF); //turn off all the relay
}
//set the status of relays
void relay_SetStatus( unsigned char status_1){
  digitalWrite(IN1, status_1);
}
