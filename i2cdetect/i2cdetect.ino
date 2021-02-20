#include <Wire.h>
#include <i2cdetect.h>

void setup() {
  Wire.begin();  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("i2cdetect example\n");
  Serial.println("Scanning address range 0x03-0x77\n\n");
}

void loop() {
  i2cdetect();
  delay(2000);
}
