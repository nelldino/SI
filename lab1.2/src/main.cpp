#include <Keypad.h>
#include <LiquidCrystal.h>
#include <stdio.h>
#include <string.h>

#define greenLED 3
#define redLED 4

const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {13, 12, 11, 10};
byte colPins[COLS] = {9, 8, 7, 6};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);

const char passcode[] = "000A";  
char inputPasscode[5] = "";     
int inputIndex = 0;              

void setup() {
  Serial.begin(9600); // Initialize Serial for printf/scanf simulation
  pinMode(greenLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  lcd.begin(16, 2);
  
  // Simulate printf for LCD output
  lcd.setCursor(0, 0);
  printf("Enter Passcode\n");
  lcd.print("Enter Passcode");
  
  lcd.setCursor(0, 1);
  printf("Then Press #\n");
  lcd.print("Then Press #");
  
  delay(2000);
  lcd.clear();
}

void loop() {
  char key = keypad.getKey();
  if (key) {
    if (key == '#') {  // Check passcode
      inputPasscode[inputIndex] = '\0';  // Null-terminate input string

      printf("Entered: %s\n", inputPasscode);  // Simulate printf output

      if (strcmp(inputPasscode, passcode) == 0) {  // Use strcmp() for comparison
        lcd.clear();
        lcd.setCursor(4, 0);
        printf("Passcode Valid\n");
        lcd.print("Passcode");
        lcd.setCursor(5, 1);
        lcd.print("Valid");
        digitalWrite(greenLED, HIGH);
        delay(1000);
        digitalWrite(greenLED, LOW);
        lcd.clear();
      } else {
        lcd.clear();
        lcd.setCursor(4, 0);
        printf("Passcode Invalid\n");
        lcd.print("Passcode");
        lcd.setCursor(4, 1);
        lcd.print("Invalid");
        digitalWrite(redLED, HIGH);
        delay(1000);
        digitalWrite(redLED, LOW);
        lcd.clear();
      }

      inputIndex = 0;  // Reset input
      inputPasscode[0] = '\0';
    } 
    else if (key == '*') {  // Clear input and show a message
      inputIndex = 0;
      inputPasscode[0] = '\0';

      lcd.clear();
      lcd.setCursor(0, 0);
      printf("Input Cleared\n");
      lcd.print("Input Cleared");  // Display message on LCD
      delay(2000);
      lcd.clear();
    } 
    else if (inputIndex < 4) {  // Append character if within limit
      inputPasscode[inputIndex++] = key;
      inputPasscode[inputIndex] = '\0';  // Keep null-terminated
      lcd.print(key);
      printf("Key Pressed: %c\n", key);
    }
  }
}
