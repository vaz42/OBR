#include <FalconRobot.h>
FalconRobotMotors motors(5, 7, 6, 8);


FalconRobotDistanceSensor distanceSensor(2, 3);

#define DISTANCETHRESHOLD 20 

int distance;  // variable to store the distance value

void setup() {
  Serial.begin(9600);
  Serial.println("Welcome to experiment 6.2 - Obstacle Avoidance!");
  delay(2000);
  Serial.println("Distance Sensor Readings: ");
  delay(500);
}

void loop() {

  // by default, returns the distance in cm. Try read(INCH) to get inches
  distance = distanceSensor.read();

  // Print the sensor distance value
  Serial.print(distance);
  Serial.println(); // new line

  if (distance <= DISTANCETHRESHOLD) { // The obstacle is really very close
    reverse();    // backs up
    turnRight();  // Can be replaced by  turnLeft();
  }
  else { // otherwise, go forward
      motors.drive(50, FORWARD);
  }

  delay(60);  // delay to wait sensor reading, suggested by datasheet
}

// reverse() function -- backs up at full power
void reverse() {
  motors.stop();
  delay(500);  // short delay to let robot fully stop
  motors.drive(50, BACKWARD);
  delay(500);
  motors.stop();
  delay(500);  // short delay to let robot fully stop
}

// turnRight() function -- turns FalconRobot to the Right
void turnRight() {
  motors.leftDrive(50, FORWARD);  // spin CCW
  motors.rightDrive(50, BACKWARD); // spin CCW
  delay(250);
  motors.stop();
  delay(250);  // short delay to let robot fully stop
}

// turnLeft() function -- turns FalconRobot to the Left
void turnLeft() {
  motors.leftDrive(50, BACKWARD);  // spin CW
  motors.rightDrive(50, FORWARD); // spin CW
  delay(250);
  motors.stop();
  delay(250);  // short delay to let robot fully stop
}
