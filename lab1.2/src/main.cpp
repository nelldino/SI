#include "KeypadLCD.h"

void setup() {
  Serial.begin(9600); 
  setupKeypadLCD();  
  delay(2000);  

void loop() {
  handleKeypadInput();  
  handlePasscodeEntry(); 
}
