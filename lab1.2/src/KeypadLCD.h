#ifndef KEYPADLCD_H
#define KEYPADLCD_H

#include <Keypad.h>
#include <LiquidCrystal.h>

// Define ROWS and COLS as compile-time constants
constexpr byte ROWS = 4;
constexpr byte COLS = 4;

extern char keys[ROWS][COLS];
extern byte rowPins[ROWS];
extern byte colPins[COLS];

extern Keypad keypad;
extern LiquidCrystal lcd;

// Pin definitions for LEDs
constexpr int greenLED = 3;
constexpr int redLED = 4;

// Passcode and input variables
extern const char passcode[];
extern char inputPasscode[5];
extern int inputIndex;

// Function prototypes
int lcd_putchar(char c, FILE *stream);
int keypad_getchar(FILE *stream);
void setupKeypadLCD();
void handlePasscodeEntry();
void setupLCD();
void handleKeypadInput();

#endif  // KEYPADLCD_H
