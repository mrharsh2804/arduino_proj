#include <AFMotor.h> //import your motor shield library
#include <Servo.h>
#define trigPin A2 // define the pins of your obstacle sensor
#define echoPin A5
AF_DCMotor motor1(1, MOTOR12_64KHZ); // set up motors.
AF_DCMotor motor2(2, MOTOR12_8KHZ);
AF_DCMotor motor3(3, MOTOR34_64KHZ);
AF_DCMotor motor4(4, MOTOR34_8KHZ);
Servo myservo;
int pos = 0;
int tooCloseMovedLeft = 0;

void setup() {
  Serial.begin(9600); // begin serial communitication
  Serial.println("Motor test!");
//  myservo.attach(10);
//  myservo.write(0);
  pinMode(trigPin, OUTPUT);// set the - pin to output (Send sound waves)
  pinMode(echoPin, INPUT); // set the echo pin to input (recieve sound waves)
  motor1.setSpeed (150);   //set the speed of the motors, between 0-255
  motor2.setSpeed (150);
  motor3.setSpeed (150);
  motor4.setSpeed (150);
}

void loop() {
//  for (pos = 0; pos <= 70; pos += 3) {
//    //Turn servo to angle "pos"
//    myservo.write(pos);              // tell servo to go to position in variable 'pos'
//    delay(15);                       // waits 15ms for the servo to reach the position
//    mainTask();   //For motor
//  }
//  for (pos = 70; pos >= 0; pos -= 3) {
//
//    //Turn servo to angle "pos"
//    myservo.write(pos);              // tell servo to go to position in variable 'pos'
//    delay(15);                       // waits 15ms for the servo to reach the position
//    mainTask();
//  }
      delay(15);                       // waits 15ms for the servo to reach the position
      mainTask();
}

void goLeft()
{
  motor1.run(FORWARD);
  motor2.run(BACKWARD);
  motor3.run(FORWARD);
  motor4.run (BACKWARD);
  Serial.println("Going Left!");
}

void goRight()
{
  motor1.run(BACKWARD);
  motor2.run (FORWARD);
  motor3.run(BACKWARD);
  motor4.run (FORWARD);
  Serial.println("Going Right!");
}

void goForward()
{
  motor1.run(FORWARD);
  motor2.run (FORWARD);
  motor3.run(FORWARD);
  motor4.run (FORWARD);
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

void mainTask()
{
  //For obstacle
  long duration, distance; // start the scan
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2); // delays are required for a succesful sensor operation.
  digitalWrite(trigPin, HIGH);

  delayMicroseconds(10); //this delay is required as well!
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1; // convert the distance to centimeters.

  if (distance > 0 && distance < 30)
  {
    Serial.println("Too close! at ");
    Serial.println(distance);
    allMotorStop();
    delay(2000);
    goLeft();
    delay(1000);
    tooCloseMovedLeft = 1;
  }
  else {
    Serial.println ("No obstacle.");
    delay (15);
    if ( tooCloseMovedLeft == 1)
    {
      motor1.run(FORWARD);
      motor2.run (FORWARD);
      motor3.run(FORWARD);
      motor4.run (FORWARD);
      delay(1000);
      goRight();
      delay(1000);
      tooCloseMovedLeft = 0;
    }
    //goForward();
      motor1.run(FORWARD);
      motor2.run (FORWARD);
      motor3.run(FORWARD);
      motor4.run (FORWARD);
  }
}
