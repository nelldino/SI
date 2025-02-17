#include <Arduino.h>
#include <stdio.h>
#include "led.h"

#define LED_PIN 13
#define BAUD_RATE 9600
#define MAX_BUFFER 50

Led statusLed(LED_PIN);
char inputBuffer[MAX_BUFFER];

FILE serial_stdout;

static int uart_putchar(char c, FILE *stream) {
  Serial.write(c);
  return 0;
}

static int uart_getchar(FILE *stream) {
  while (!Serial.available());  
  return Serial.read();
}

void setup() {
  Serial.begin(BAUD_RATE);
  statusLed.initialize();

  fdev_setup_stream(&serial_stdout, uart_putchar, uart_getchar, _FDEV_SETUP_RW);
  stdout = &serial_stdout;
  stdin = &serial_stdout;

  printf("LED Control System Ready\n");
  printf("Commands: 'led on' or 'led off'\n");
}

void loop() {
  if (Serial.available()) {
    int len = Serial.readBytesUntil('\n', inputBuffer, MAX_BUFFER - 1);
    inputBuffer[len] = '\0';  // Null-terminate input

    // Remove '\r' if it exists
    for (int i = 0; i < len; i++) {
      if (inputBuffer[i] == '\r') { 
        inputBuffer[i] = '\0';
        break;  // Stop checking once '\r' is removed
      }
    }

    if (strcmp(inputBuffer, "led on") == 0) {
      statusLed.turnOn();
      printf("LED is on\n");
    } else if (strcmp(inputBuffer, "led off") == 0) {
      statusLed.turnOff();
      printf("LED is off\n");
    } else {
      printf("Invalid command.\n");
    }
  }
}