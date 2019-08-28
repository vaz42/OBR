#include <FalconRobot.h>

FalconRobotMotors motors(5, 7, 6, 8);

// Criação de algumas constantes.
const int ledPin = 13;
const int buttonPin = A0;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP); // configures the button as an INPUT
  // INPUT_PULLUP defaults it to HIGH.
  pinMode(ledPin, OUTPUT);  // configures the ledPin as an OUTPUT
}

void loop() {
  if ( digitalRead(buttonPin) == LOW ) { // if the button is pushed (LOW)
    digitalWrite(ledPin, HIGH); // Turns LED ON - HIGH puts 5V on pin 13.

    motors.drive(100, FORWARD);     // Start the motors.
    delay(1000);   // delay for 1000 ms (1 second)

    digitalWrite(ledPin, LOW);  // Turns LED OFF - LOW puts 0V on pin 13.
    motors.stop();          // stop() or stop the motors.
  }
  else  { // otherwise, do this.

  }
}
