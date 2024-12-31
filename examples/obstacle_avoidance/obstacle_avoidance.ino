//Obstacle Avoidance code

// Ultrasonic sensor pins
#define TRIG_PIN A3
#define ECHO_PIN A2

// Motor control pins (H-Bridge L298N)
#define LEFT_MOTOR_IN1 8
#define LEFT_MOTOR_IN2 7
#define RIGHT_MOTOR_IN1 5
#define RIGHT_MOTOR_IN2 6

// Define safe distance threshold in cm
#define SAFE_DISTANCE 20

void setup() {
  // Initialize ultrasonic sensor pins
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // Initialize motor control pins as output
  pinMode(LEFT_MOTOR_IN1, OUTPUT);
  pinMode(LEFT_MOTOR_IN2, OUTPUT);
  pinMode(RIGHT_MOTOR_IN1, OUTPUT);
  pinMode(RIGHT_MOTOR_IN2, OUTPUT);

  // Start serial communication for debugging
  Serial.begin(9600);

  // Set motors to stopped state
  stopMotors();
}

void loop() {
  // Measure the distance to the nearest obstacle
  int distance = measureDistance();

  // Obstacle avoidance logic
  if (distance < SAFE_DISTANCE) {
    // Obstacle detected: stop and turn
    stopMotors();
    delay(500);  // Pause before turning
    turnRight();
    delay(500); // Turn duration
  } else {
    // No obstacle: move forward
    moveForward();
  }

  // Small delay for stability
  delay(100);
}

int measureDistance() {
  // Send a 10us pulse to the TRIG pin
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Read the echo pin duration (in microseconds)
  long duration = pulseIn(ECHO_PIN, HIGH);

  // Convert duration to distance (in cm)
  int distance = duration * 0.034 / 2;

  // Print distance for debugging
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  return distance;
}

void moveForward() {
  digitalWrite(LEFT_MOTOR_IN1, HIGH);
  digitalWrite(LEFT_MOTOR_IN2, LOW);
  digitalWrite(RIGHT_MOTOR_IN1, HIGH);
  digitalWrite(RIGHT_MOTOR_IN2, LOW);
}

void turnRight() {
  digitalWrite(LEFT_MOTOR_IN1, HIGH);
  digitalWrite(LEFT_MOTOR_IN2, LOW);
  digitalWrite(RIGHT_MOTOR_IN1, LOW);
  digitalWrite(RIGHT_MOTOR_IN2, HIGH);
}

void stopMotors() {
  digitalWrite(LEFT_MOTOR_IN1, LOW);
  digitalWrite(LEFT_MOTOR_IN2, LOW);
  digitalWrite(RIGHT_MOTOR_IN1, LOW);
  digitalWrite(RIGHT_MOTOR_IN2, LOW);
}
