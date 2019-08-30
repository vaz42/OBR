#include <FalconRobot.h>
#include <Wire.h>

FalconRobotMotors motors(5, 7, 6, 8);
FalconRobotDistanceSensor distanceSensor(2, 3);
FalconRobotLineSensor left(A2);
FalconRobotLineSensor right(A3);

#define DISTANCETHRESHOLD 8 //distância em cm limite do obstáculo
#define LINETHRESHOLD 800
#define SPEED 30


int leftSpeed;   // variable used to store the leftMotor speed
int rightSpeed;  // variable used to store the rightMotor speed
int distance;  // variable to store the distance value
int leftValue;
int rightValue;
int speed;


/* GYROSCOPE STUFF */
const int MPU_ADDR = 0x68; // I2C address of the MPU-6050. If AD0 pin is set to HIGH, the I2C address will be 0x69.
int16_t accelerometer_x, accelerometer_y, accelerometer_z; // variables for accelerometer raw data
int16_t gyro_x, gyro_y, gyro_z; // variables for gyro raw data
int16_t temperature; // variables for temperature data
char tmp_str[7]; // temporary variable used in convert function
char* convert_int16_to_str(int16_t i) { // converts int16 to string. Moreover, resulting strings will have the same length in the debug monitor.
  sprintf(tmp_str, "%6d", i);
  return tmp_str;
}


void setup() {
  Serial.begin(9600);
  Wire.begin();
  Wire.beginTransmission(MPU_ADDR); // Begins a transmission to the I2C slave (GY-521 board)
  Wire.write(0x6B); // PWR_MGMT_1 register
  Wire.write(0); // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  empurraozada();
}

void loop(){
    Wire.beginTransmission(MPU_ADDR);
    Wire.write(0x3B); 
    Wire.endTransmission(false); 
    Wire.requestFrom(MPU_ADDR, 7*2, true);

    accelerometer_x = Wire.read()<<8 | Wire.read();
    distance = distanceSensor.read();
    leftValue = left.read();
    rightValue = right.read();

    /* TESTING SENSORS
    Serial.print("leftV = "); Serial.print(leftValue);  
    Serial.print(" | rightV = "); Serial.print(rightValue);
    Serial.print(" | dist = "); Serial.print(distance);
    Serial.print(" | aX = "); Serial.print(convert_int16_to_str(accelerometer_x));
    */


   if(distance <= DISTANCETHRESHOLD && distance != 4 && distance != 0) {
       motors.stop();
       delay(500);

       reverse();

       turnRight();
       motors.drive(100, FORWARD);
       delay(200);
       motors.stop();
       
       turnLeft();
       motors.drive(100, FORWARD);
       delay(300);
       motors.stop();

       turnLeft();
       motors.drive(100, FORWARD);
       delay(200);
       motors.stop();

       turnRight();

       empurraozada();
    }
    else{
        if(accelerometer_x < 10000)
            speed = 100;
        else
            speed = SPEED;
        
        if((leftValue > LINETHRESHOLD) && (rightValue > LINETHRESHOLD)) {
  	        leftSpeed = speed;
  	        rightSpeed = speed;
        }
        else if(rightValue > LINETHRESHOLD) {
  	        leftSpeed = speed;
  	        rightSpeed = speed - 10;
        }
        else if(leftValue > LINETHRESHOLD) {
  	        leftSpeed = speed - 10 ;
  	        rightSpeed = speed;
        }

        motors.leftDrive(leftSpeed, FORWARD);
        motors.rightDrive(rightSpeed, FORWARD);
    }
}

void empurraozada(){
    motors.drive(100, FORWARD);
    delay(60);
    motors.stop();
}

void reverse() {
  motors.stop();
  //delay(500); 
  motors.drive(50, BACKWARD);
  delay(200);
  motors.stop();
  delay(500);  
}

void turnRight() {
  motors.leftDrive(50, FORWARD); 
  motors.rightDrive(50, BACKWARD); 
  delay(250);
  motors.stop();
  delay(1000);  
}

void turnLeft() {
  motors.leftDrive(50, BACKWARD); 
  motors.rightDrive(50, FORWARD); 
  delay(250);
  motors.stop();
  delay(1000);  
}
