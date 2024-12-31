//remote control code

#include <SoftwareSerial.h>

// Bluetooth module pins
#define SERIAL_RX_PIN 10  // Connected to the Blutooth module's TX
#define SERIAL_TX_PIN 11  // Connected to the Blutooth module's RX

// Motor control pins (H-Bridge L298N)
#define LEFT_MOTOR_IN1 8
#define LEFT_MOTOR_IN2 7
#define RIGHT_MOTOR_IN1 5
#define RIGHT_MOTOR_IN2 6

// Commands for controlling the robot
#define CMD_FORWARD 'F'
#define CMD_BACKWARD 'B'
#define CMD_LEFT 'L'
#define CMD_RIGHT 'R'
#define CMD_STOP 'S'

// Software serial instance
SoftwareSerial bluetoothSerial(SERIAL_RX_PIN, SERIAL_TX_PIN);  // RX_PIN, TX_PIN

void setup() {
#ifdef DEBUG_ENABLE
  Serial.begin(9600);
#endif

  bluetoothSerial.begin(9600);  // This is the serial port we'll communicate with the bluetooth module through
  DEBUG_MACRO("--- Bluetooth RC robot started ---");
  // Initialize motor control pins as outputs
  pinMode(LEFT_MOTOR_IN1, OUTPUT);
  pinMode(LEFT_MOTOR_IN2, OUTPUT);
  pinMode(RIGHT_MOTOR_IN1, OUTPUT);
  pinMode(RIGHT_MOTOR_IN2, OUTPUT);

  // Start Bluetooth communication at 38400 baud
  bluetooth.begin(38400);

  // Stop motors initially
  stopMotors();

  Serial.println("KitBot Bluetooth Remote Control Ready");
}

void loop() {
  // Check if data is available from Bluetooth
  if (bluetooth.available()) {
    char command = bluetooth.read();  // Read the incoming command

    // Debug: Print received command
    Serial.print("Received Command: ");
    Serial.println(command);

    // Execute the appropriate action based on the command
    switch (command) {
      case CMD_FORWARD:
        moveForward();
        DEBUG_MACRO("FORWARD");
        break;

      case CMD_BACKWARD:
        moveBackward();
        DEBUG_MACRO("REVERSE");
        break;

      case CMD_LEFT:
        turnLeft();
        DEBUG_MACRO("LEFT");
        break;

      case CMD_RIGHT:
        turnRight();
        DEBUG_MACRO("RIGHT");
        break;

      case CMD_STOP:
        stopMotors();
        DEBUG_MACRO("STOPPING");
        break;

      default:
        Serial.println("Invalid Command");
        break;
    }
  }
}

// Function to move forward
void moveForward() {
  digitalWrite(LEFT_MOTOR_IN1, HIGH);
  digitalWrite(LEFT_MOTOR_IN2, LOW);
  digitalWrite(RIGHT_MOTOR_IN1, HIGH);
  digitalWrite(RIGHT_MOTOR_IN2, LOW);
}

// Function to move backward
void moveBackward() {
  digitalWrite(LEFT_MOTOR_IN1, LOW);
  digitalWrite(LEFT_MOTOR_IN2, HIGH);
  digitalWrite(RIGHT_MOTOR_IN1, LOW);
  digitalWrite(RIGHT_MOTOR_IN2, HIGH);
}

// Function to turn left
void turnLeft() {
  digitalWrite(LEFT_MOTOR_IN1, LOW);
  digitalWrite(LEFT_MOTOR_IN2, HIGH);
  digitalWrite(RIGHT_MOTOR_IN1, HIGH);
  digitalWrite(RIGHT_MOTOR_IN2, LOW);
}

// Function to turn right
void turnRight() {
  digitalWrite(LEFT_MOTOR_IN1, HIGH);
  digitalWrite(LEFT_MOTOR_IN2, LOW);
  digitalWrite(RIGHT_MOTOR_IN1, LOW);
  digitalWrite(RIGHT_MOTOR_IN2, HIGH);
}

// Function to stop the motors
void stopMotors() {
  digitalWrite(LEFT_MOTOR_IN1, LOW);
  digitalWrite(LEFT_MOTOR_IN2, LOW);
  digitalWrite(RIGHT_MOTOR_IN1, LOW);
  digitalWrite(RIGHT_MOTOR_IN2, LOW);
}
