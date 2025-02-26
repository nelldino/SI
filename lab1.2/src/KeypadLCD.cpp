#include "KeypadLCD.h"
#include <stdio.h>
#include <string.h>

// Keypad setup
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

// Pin definitions for LEDs
const int greenLED = 3;
const int redLED = 4;

// Passcode and input variables
const char passcode[] = "000A";
char inputPasscode[5] = "";
int inputIndex = 0;

// Redirect printf to LCD
int lcd_putchar(char c, FILE *stream) {
  if (c == '\n') {
    lcd.setCursor(0, 1);  // Move to next line
  } else {
    lcd.print(c);
  }
  return 0;
}

// Redirect scanf to read from Keypad
int keypad_getchar(FILE *stream) {
  char key = '\0'; // Default null character
  
  // Wait until a key is pressed
  while (key == '\0') {
    key = keypad.getKey();
  }
  
  return key; // Return the pressed key
}

// Setup Keypad and LCD
void setupKeypadLCD() {
  pinMode(greenLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  lcd.begin(16, 2);

  // Redirect stdout to lcd_putchar
  static FILE lcd_out = {0};
  fdev_setup_stream(&lcd_out, lcd_putchar, NULL, _FDEV_SETUP_WRITE);
  stdout = &lcd_out;

  // Redirect stdin to keypad_getchar
  static FILE keypad_in = {0};
  fdev_setup_stream(&keypad_in, NULL, keypad_getchar, _FDEV_SETUP_READ);
  stdin = &keypad_in;
}

// Handle passcode entry and validation
void handlePasscodeEntry() {
  lcd.clear();
  lcd.setCursor(0, 0);
  printf("Entered: %s\n", inputPasscode);

  if (strcmp(inputPasscode, passcode) == 0) { 
    lcd.clear();
    lcd.setCursor(0, 0);
    printf("Passcode Valid\n");
    digitalWrite(greenLED, HIGH);
    delay(1000);
    digitalWrite(greenLED, LOW);
  } else {
    lcd.clear();
    lcd.setCursor(0, 0);
    printf("Passcode Invalid\n");
    digitalWrite(redLED, HIGH);
    delay(1000);
    digitalWrite(redLED, LOW);
  }

  lcd.clear();
}

// Handle keypad input for passcode
void handleKeypadInput() {
  lcd.setCursor(0, 0);
  printf("Enter Code: ");

  // Read 4-digit passcode using scanf
  for (inputIndex = 0; inputIndex < 4; inputIndex++) {
    scanf(" %c", &inputPasscode[inputIndex]); // Read character from keypad
    printf("%c", inputPasscode[inputIndex]);  // Display it on LCD
  }

  inputPasscode[inputIndex] = '\0'; // Null-terminate the string
}
