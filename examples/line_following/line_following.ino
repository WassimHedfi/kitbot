//Line Following code

// Define IR sensor pins
#define LEFT_IR A1
#define RIGHT_IR A0

// Define motor control pins (H-Bridge L298N)
#define LEFT_MOTOR_IN1 8
#define LEFT_MOTOR_IN2 7
#define RIGHT_MOTOR_IN1 5
#define RIGHT_MOTOR_IN2 6

void setup() {
  // Initialize IR sensor pins as input
  pinMode(LEFT_IR, INPUT);
  pinMode(RIGHT_IR, INPUT);

  // Initialize motor control pins as output
  pinMode(LEFT_MOTOR_IN1, OUTPUT);
  pinMode(LEFT_MOTOR_IN2, OUTPUT);
  pinMode(RIGHT_MOTOR_IN1, OUTPUT);
  pinMode(RIGHT_MOTOR_IN2, OUTPUT);

  // Set motors to stopped state
  stopMotors();
}

void loop() {
  // Read IR sensor values
  int leftSensor = digitalRead(LEFT_IR);
  int rightSensor = digitalRead(RIGHT_IR);

  // Line following logic
  if (leftSensor == LOW && rightSensor == LOW) {
    // Both sensors on the line: move forward
    moveForward();
  } else if (leftSensor == LOW && rightSensor == HIGH) {
    // Left sensor on the line, right sensor off: turn left
    turnLeft();
  } else if (leftSensor == HIGH && rightSensor == LOW) {
    // Right sensor on the line, left sensor off: turn right
    turnRight();
  } else {
    // Both sensors off the line: stop
    stopMotors();
  }

  // Small delay to stabilize the readings
  delay(50);
}

void moveForward() {
  digitalWrite(LEFT_MOTOR_IN1, HIGH);
  digitalWrite(LEFT_MOTOR_IN2, LOW);
  digitalWrite(RIGHT_MOTOR_IN1, HIGH);
  digitalWrite(RIGHT_MOTOR_IN2, LOW);
}

void turnLeft() {
  digitalWrite(LEFT_MOTOR_IN1, LOW);
  digitalWrite(LEFT_MOTOR_IN2, LOW);  // Left motor stops
  digitalWrite(RIGHT_MOTOR_IN1, HIGH);
  digitalWrite(RIGHT_MOTOR_IN2, LOW); // Right motor moves forward
}

void turnRight() {
  digitalWrite(LEFT_MOTOR_IN1, HIGH);
  digitalWrite(LEFT_MOTOR_IN2, LOW);  // Left motor moves forward
  digitalWrite(RIGHT_MOTOR_IN1, LOW);
  digitalWrite(RIGHT_MOTOR_IN2, LOW); // Right motor stops
}

void stopMotors() {
  digitalWrite(LEFT_MOTOR_IN1, LOW);
  digitalWrite(LEFT_MOTOR_IN2, LOW);
  digitalWrite(RIGHT_MOTOR_IN1, LOW);
  digitalWrite(RIGHT_MOTOR_IN2, LOW);
}
