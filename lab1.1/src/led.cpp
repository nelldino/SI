#include "led.h"
#include <Arduino.h>

Led::Led(int pin) {
  pinNumber = pin;
  state = false;
}

void Led::initialize() {
  pinMode(pinNumber, OUTPUT);
  digitalWrite(pinNumber, LOW);
}

void Led::turnOn() {
  digitalWrite(pinNumber, HIGH);
  state = true;
}

void Led::turnOff() {
  digitalWrite(pinNumber, LOW);
  state = false;
}

bool Led::getState() {
  return state;
}