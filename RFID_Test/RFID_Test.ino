/*  ___   ___  ___  _   _  ___   ___   ____ ___  ____  
 * / _ \ /___)/ _ \| | | |/ _ \ / _ \ / ___) _ \|    \ 
 *| |_| |___ | |_| | |_| | |_| | |_| ( (__| |_| | | | |
 * \___/(___/ \___/ \__  |\___/ \___(_)____)___/|_|_|_|
 *                  (____/ 
 * Use browser and OSOYOO MEGA-IoT extension shield to get message from remote browser
 * Tutorial URL  http://osoyoo.com/?p=28943
 * CopyRight www.osoyoo.com
 */
#include <SPI.h>
#include <RFID.h>           //48 52
  unsigned char my_rfid[] = {89,249,89,194,59}; // ID DEL LLAVERO
  
RFID rfid(48,49);  //D48--RFID module SDA pinã€D49 RFID module RST pin
void setup()
{
  Serial.begin(9600);
  SPI.begin();
  rfid.init();
}

void loop()
{
 //search card
  if (rfid.isCard()) {
    Serial.println("Find the card!");
   //read serial number
    if (rfid.readCardSerial()) {
      Serial.print("The card's number is  : ");
      Serial.print(rfid.serNum[0]);
         Serial.print(",");
      Serial.print(rfid.serNum[1]);
         Serial.print(",");
      Serial.print(rfid.serNum[2]);
          Serial.print(",");
      Serial.print(rfid.serNum[3]);
          Serial.print(",");
      Serial.print(rfid.serNum[4]);
      Serial.println(" ");
      if (compare_rfid(rfid.serNum,my_rfid))
       Serial.println("This card match our record!");
      else
       Serial.println("Not match!");
    }
 
    rfid.selectTag(rfid.serNum);
  }
  
  rfid.halt();
}
boolean compare_rfid(unsigned char x[],unsigned char y[])
{
  for (int i=0;i<5;i++)
  {
    if(x[i]!=y[i]) return false;
  }
  return true;
}
