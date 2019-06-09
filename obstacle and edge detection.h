#include <AFMotor.h> //import your motor shield library
#include <Servo.h>
#define trigPin A2// define the pins of your obstacle sensor
#define echoPin A3
#define trigPin1 A5
#define echoPin1 A4
AF_DCMotor motor1(1, MOTOR12_64KHZ); // set up motors.
AF_DCMotor motor2(2, MOTOR12_8KHZ);
AF_DCMotor motor3(3, MOTOR34_64KHZ);
AF_DCMotor motor4(4, MOTOR34_8KHZ);
Servo myservo;
int pos = 0;
int tooCloseMovedLeft = 0;
int motSpeed = 110;
int noObstacle = -1, obsDetected = -1;
int noEdge = -1, edgeDetected = -1;
int rotationTime = 550;

void setup() {
  Serial.begin(9600); // begin serial communitication
  Serial.println("Motor test!");
  pinMode(trigPin, OUTPUT);// set the - pin to output (Send sound waves)
  pinMode(echoPin, INPUT); // set the echo pin to input (recieve sound waves)
  pinMode(trigPin1, OUTPUT);// set the - pin to output (Send sound waves)
  pinMode(echoPin1, INPUT); // set the echo pin to input (recieve sound waves)
  motor1.setSpeed (motSpeed);   //set the speed of the motors, between 0-255
  motor2.setSpeed (motSpeed);
  motor3.setSpeed (motSpeed);
  motor4.setSpeed (motSpeed);
}

void loop() {
  delay(15);                       // waits 15ms for the servo to reach the position
  mainTask();
}

void goLeft()
{
  motor1.run(FORWARD);
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  motor4.run(FORWARD);
  Serial.println("Going Left!");
}

void goRight()
{
  motor1.run(BACKWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(BACKWARD);
  Serial.println("Going Right!");
}

void goForward()
{
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
  Serial.println("Going Forward!");
}

void allMotorStop()
{
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
  Serial.println("Stop all motors!");
}

long obsDist()
{
    long duration, distance, distanceEdge;
  
  //For obstacle distance // start the scan
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2); // delays are required for a successful sensor operation.
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10); //this delay is required as well!
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = (duration / 2) / 29.1; // convert the distance to centimeters.
    Serial.print("Obstacle distance:");
    Serial.println(distance);
    return distance;
}

long edgeDist()
{
  long duration, distance, distanceEdge;
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2); // delays are required for a successful sensor operation.
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10); //this delay is required as well!
  digitalWrite(trigPin1, LOW);
  duration = pulseIn(echoPin1, HIGH);
  distanceEdge = (duration / 2) / 29.1; // convert the distance to centimeters.
  Serial.print("Edge distance:");
  Serial.println(distanceEdge);
  return distanceEdge;
}



void mainTask()
{
  goForward();
  long duration, distance, distanceEdge;
  
//For obstacle distance // start the scan
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2); // delays are required for a successful sensor operation.
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); //this delay is required as well!
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1; // convert the distance to centimeters.
  Serial.print("Obstacle distance:");
  Serial.println(distance);

//For edge distance
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2); // delays are required for a successful sensor operation.
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10); //this delay is required as well!
  digitalWrite(trigPin1, LOW);
  duration = pulseIn(echoPin1, HIGH);
  distanceEdge = (duration / 2) / 29.1; // convert the distance to centimeters.
  Serial.print("Edge distance:");
  Serial.println(distanceEdge);
  
//  obstacle detected
  if (distance < 40) // obstacle detected
  {
    noObstacle = 0;
    allMotorStop();
    delay(1000);
    goLeft();
    delay(rotationTime);
    goForward();
    delay(550);
    goRight();
    delay(rotationTime);
    allMotorStop();
    delay(1000);
    obsDetected = 1;
    Serial.println(1);
  }
  else  // obstacle not detected
  {
    noObstacle = 1;
    Serial.println(2);
  }


//  //edge detected
  
  if(distanceEdge > 4)
  {
    allMotorStop();
    delay(1000);
    noEdge = 0;
    goRight();
    delay(rotationTime);
    goForward();
    delay(550);
    goLeft();
    delay(rotationTime);
    allMotorStop();
    delay(1000);
    edgeDetected = 1;
  }
  else  // obstacle not detected
  {
    noEdge = 1;
  }
}