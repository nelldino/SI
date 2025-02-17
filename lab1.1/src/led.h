#ifndef LED_H
#define LED_H

class Led {
private:
  int pinNumber;
  bool state;

public:
  Led(int pin);
  void initialize();
  void turnOn();
  void turnOff();
  bool getState();
};

#endif