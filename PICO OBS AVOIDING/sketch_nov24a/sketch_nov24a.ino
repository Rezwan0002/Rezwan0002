#include <Servo.h>

// Servo motor setup
Servo servo; // Servo object
int servoPin = 16;

// Ultrasonic sensor pins
const int trigPin = 18;
const int echoPin = 19;

// Motor driver pins (L298N)
const int ENA = 17;  // Enable pin A
const int IN1 = 11;  // Input pin 1
const int IN2 = 10;  // Input pin 2
const int IN3 = 7;  // Input pin 3
const int IN4 = 6;  // Input pin 4
const int ENB = 15;  // Enable pin B

// Variables
int speed = 10000; // Speed of the robot

// Function prototypes
void forward();
void backward();
void left();
void right();
void stop();
float getDistance();
void servoLeft();
void servoRight();
void servoStart();

void setup() {
  // Initialize servo
  servo.attach(servoPin);
  servoStart(); // Center the servo

  // Set up motor pins
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  // Set up ultrasonic sensor pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Start serial communication for debugging
  Serial.begin(9600);
}

void loop() {
  float dis = getDistance();

  if (dis < 15) {
    stop();
    delay(200);

    // Reverse briefly
    backward();
    delay(300);
    stop();
    delay(300);

    // Scan to the left
    servoLeft();
    delay(300);
    float leftDis = getDistance();
    Serial.println("Left Distance: " + String(leftDis));

    // Center the servo
    servoStart();
    delay(300);

    // Scan to the right
    servoRight();
    delay(300);
    float rightDis = getDistance();
    Serial.println("Right Distance: " + String(rightDis));

    // Center the servo back
    servoStart();
    delay(500);

    // Decision-making
    if (leftDis > rightDis) {
      Serial.println("Decision: Turn Left");
      left();
      delay(250);
    } else {
      Serial.println("Decision: Turn Right");
      right();
      delay(250);
    }

    stop();
    delay(500);
  } else {
    forward();
    delay(100);
  }
}

// Motor functions
void forward() {
  analogWrite(ENA, speed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  analogWrite(ENB, speed);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  Serial.println("Moving Forward");
}

void backward() {
  analogWrite(ENA, speed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  analogWrite(ENB, speed);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  Serial.println("Moving Backward");
}

void left() {
  analogWrite(ENA, speed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  analogWrite(ENB, speed);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  Serial.println("Turning Left");
}

void right() {
  analogWrite(ENA, speed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  analogWrite(ENB, speed);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  Serial.println("Turning Right");
}

void stop() {
  analogWrite(ENA, 0);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);

  analogWrite(ENB, 0);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);

  Serial.println("Stopped");
}

// Ultrasonic sensor function
float getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  float distance = duration * 0.034 / 2;

  Serial.println("Measured Distance: " + String(distance) + " cm");
  return distance;
}

// Servo functions
void servoLeft() {
  servo.write(180); // Move servo to the left
  Serial.println("Servo moved left");
}

void servoRight() {
  servo.write(0); // Move servo to the right
  Serial.println("Servo moved right");
}

void servoStart() {
  servo.write(90); // Center the servo
  Serial.println("Servo centered");
}

