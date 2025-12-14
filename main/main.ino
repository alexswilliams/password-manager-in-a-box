#include <Keyboard.h>
#include "pass.h"

const int LEFT_BUTTON = 2;
const int MIDL_BUTTON = 3;
const int RGHT_BUTTON = 4;

const int SIDE_LED = 23;

void setup() {
  pinMode(LEFT_BUTTON, INPUT_PULLUP);
  pinMode(MIDL_BUTTON, INPUT_PULLUP);
  pinMode(RGHT_BUTTON, INPUT_PULLUP);
  pinMode(SIDE_LED, OUTPUT);
  
  Keyboard.begin();
  Keyboard.releaseAll();
  digitalWrite(SIDE_LED, HIGH);
}

void printPassword(const char* password) {
  for (size_t i = 0; i < strlen(password); i++) {
    switch (password[i]) {
      case '#': // damned octothorpe
        Keyboard.press(KEY_RIGHT_ALT);
        Keyboard.press('3');
        break;
      default:
        Keyboard.press(password[i]);
    }
    delay(5);
    Keyboard.releaseAll();
    delay(10);
  }
}

void testKey(const int pin, const char* password) {
  if (digitalRead(pin) == LOW) {
    digitalWrite(SIDE_LED, LOW);
    
    printPassword(password);
    
    delay(250);
    while (digitalRead(pin) == LOW) { }
    delay(250);
    digitalWrite(SIDE_LED, HIGH);
  }
}

void loop() {
  delay(100);
  testKey(LEFT_BUTTON, PASS1);
  testKey(MIDL_BUTTON, PASS2);
  testKey(RGHT_BUTTON, PASS3);
}
