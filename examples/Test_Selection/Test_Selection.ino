#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>

// LCD Initialization (address 0x27, 16 columns, 2 rows)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Button pins
#define RED_BUTTON 2
#define BLUE_BUTTON 3

// LEDs
#define GREEN_LED 13
#define RED_LED 4


// Motor and sensor pins
#define TRIG_PIN A3
#define ECHO_PIN A2

#define LEFT_IR A1
#define RIGHT_IR A0

#define BUZZER 9

#define SERIAL_RX_PIN 10
#define SERIAL_TX_PIN 11

#define MOTOR_1_INPUT_1     5
#define MOTOR_1_INPUT_2     6
#define MOTOR_2_INPUT_1     8
#define MOTOR_2_INPUT_2     7


#define SERIAL_RX_PIN         10
#define SERIAL_TX_PIN         11

// Software serial instance
SoftwareSerial bluetoothSerial(SERIAL_RX_PIN, SERIAL_TX_PIN); // RX_PIN, TX_PIN
char incomingData = 'r';

// Application Codes
#define OBSTACLE_AVOIDANCE 0
#define LINE_FOLLOWING 1
#define REMOTE_CONTROL 2
#define DISTANCE_BUZZER_LCD 3
#define SELECT_MENU 4

int scenario = SELECT_MENU;  // Default application
int select = OBSTACLE_AVOIDANCE;
bool exitApp = false;

/* ---------------------------------------------------------- */
void setup() {


  bluetoothSerial.begin(38400); // This is the serial port we'll communicate with the Bluetooth module through

  // Motor pins
  pinMode(MOTOR_1_INPUT_1, OUTPUT);
  pinMode(MOTOR_1_INPUT_2, OUTPUT);
  pinMode(MOTOR_2_INPUT_1, OUTPUT);
  pinMode(MOTOR_2_INPUT_2, OUTPUT);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  pinMode(RED_BUTTON, INPUT_PULLUP);
  pinMode(BLUE_BUTTON, INPUT_PULLUP);

  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);

  // Initialize IR sensor pins as input
  pinMode(LEFT_IR, INPUT);
  pinMode(RIGHT_IR, INPUT);

  // Initialize LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("  Select a Test");
  lcd.setCursor(0, 1);
  lcd.print("    Scenario");
  delay(3000); // Display welcome message for 3 seconds
}

void loop() {
  // Button state
  bool redButtonPressed = digitalRead(RED_BUTTON) == LOW;
  bool blueButtonPressed = digitalRead(BLUE_BUTTON) == LOW;
  if (redButtonPressed) {
    select = (select + 1) % 4;
    displayMenu();
    delay(100);  // Debounce
  } else if (blueButtonPressed) {
    // Start selected application
    scenario = select;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Running App...");
    lcd.setCursor(0, 1);
    lcd.print("Press R+B = EXIT");

    delay(3000);  // Show running message
    exitApp = false;
  }

  switch (scenario) {
    case SELECT_MENU :
      displayMenu();
      break;

    case LINE_FOLLOWING :
      lineFollowing();
      break;

    case REMOTE_CONTROL :
      remoteControl();
      break;

    case DISTANCE_BUZZER_LCD :
      ultrasonic();
      break;

    case OBSTACLE_AVOIDANCE :
      obstacleAvoidance();
      break;
  }

}

/* ---------------------------------------------------------- */


void displayMenu() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Red -> | Blue:OK");
  switch (select) {
    case OBSTACLE_AVOIDANCE:
      lcd.setCursor(0, 1);
      lcd.print("1:Obstacle Avoid");
      break;
    case LINE_FOLLOWING:
      lcd.setCursor(0, 1);
      lcd.print("2:Line Following");
      break;
    case REMOTE_CONTROL:
      lcd.setCursor(0, 1);
      lcd.print("3:Remote Control");
      break;
    case DISTANCE_BUZZER_LCD:
      lcd.setCursor(0, 1);
      lcd.print("4:Distance Alert");
      break;
  }
}


void reinitialize() {
  select = OBSTACLE_AVOIDANCE ;
  scenario = SELECT_MENU;
  exitApp = true;
  stopBot();
}



void remoteControl() {
  while (!exitApp) {
    if (digitalRead(RED_BUTTON) == LOW && digitalRead(BLUE_BUTTON) == LOW) {
      reinitialize();
      break;
    }
    else {
      scanBluetooth(); // Check if there's any incoming data through Bluetooth

      switch (incomingData) { // Choose appropriate action
        case 'S':
          stopBot();
          break;

        case 'F':
          forward();

          break;

        case 'L':
          sharpleft();
          break;

        case 'R':
          sharpright();
          break;

        case 'B':
          reverse();
          break;

        default:
          stopBot();
          break;
      }
    }
  }
}
void forward() {
  digitalWrite(MOTOR_1_INPUT_1, LOW);
  digitalWrite(MOTOR_1_INPUT_2, HIGH);
  digitalWrite(MOTOR_2_INPUT_1, LOW);
  digitalWrite(MOTOR_2_INPUT_2, HIGH);
}

void reverse() {
  digitalWrite(MOTOR_1_INPUT_1, HIGH);
  digitalWrite(MOTOR_1_INPUT_2, LOW);
  digitalWrite(MOTOR_2_INPUT_1, HIGH);
  digitalWrite(MOTOR_2_INPUT_2, LOW);
}

void sharpleft() {
  digitalWrite(MOTOR_1_INPUT_1, LOW);
  digitalWrite(MOTOR_1_INPUT_2, HIGH);
  digitalWrite(MOTOR_2_INPUT_1, HIGH);
  digitalWrite(MOTOR_2_INPUT_2, LOW);
}

void left() {
  digitalWrite(MOTOR_1_INPUT_1, LOW);
  digitalWrite(MOTOR_1_INPUT_2, HIGH);
  digitalWrite(MOTOR_2_INPUT_1, LOW);
  digitalWrite(MOTOR_2_INPUT_2, LOW);
}

void sharpright() {
  digitalWrite(MOTOR_1_INPUT_1, HIGH);
  digitalWrite(MOTOR_1_INPUT_2, LOW);
  digitalWrite(MOTOR_2_INPUT_1, LOW);
  digitalWrite(MOTOR_2_INPUT_2, HIGH);
}

void right() {
  digitalWrite(MOTOR_1_INPUT_1, LOW);
  digitalWrite(MOTOR_1_INPUT_2, LOW);
  digitalWrite(MOTOR_2_INPUT_1, LOW);
  digitalWrite(MOTOR_2_INPUT_2, HIGH);
}

void stopBot() {
  digitalWrite(MOTOR_1_INPUT_1, LOW);
  digitalWrite(MOTOR_1_INPUT_2, LOW);
  digitalWrite(MOTOR_2_INPUT_1, LOW);
  digitalWrite(MOTOR_2_INPUT_2, LOW);
}

void scanBluetooth() {
  // There's data in the serial buffer (available() returns the number of bytes available)
  if (bluetoothSerial.available() > 0)
    incomingData = bluetoothSerial.read(); // Read a byte
  else
    Serial.println(incomingData);
}

void ultrasonic() {
  while (!exitApp) {
    if (digitalRead(RED_BUTTON) == LOW && digitalRead(BLUE_BUTTON) == LOW) {
      reinitialize();
      break;
    } else {
      // Get distance from the ultrasonic sensor
      long duration = getUltrasonicDuration();
      int distance = durationToDistance(duration);

      // Display distance on the LCD
      lcd.setCursor(0, 0);
      lcd.print("Distance: ");
      lcd.print(distance);
      lcd.print(" cm ");

      // Check if the distance is too close
      if (distance <= 15) {
        lcd.setCursor(0, 1);
        lcd.print("TOO CLOSE!     ");
        digitalWrite(RED_LED, HIGH);   // Turn on the red LED
        digitalWrite(GREEN_LED, LOW);   // Turn off the green LED
        analogWrite(BUZZER, 180);  // Turn on the buzzer
        delay(200); // Sound the buzzer briefly
        analogWrite(BUZZER, 0);   // Turn off the buzzer
        delay(200); // Wait briefly
      } else {
        lcd.setCursor(0, 1);
        lcd.print("Safe Distance  ");
        digitalWrite(RED_LED, LOW);   // Turn off the red LED
        digitalWrite(GREEN_LED, HIGH); // Turn on the green LED
        analogWrite(BUZZER, 0);  // Ensure buzzer is off
      }

      delay(300); // Update every 300ms
    }
  }
}


long getUltrasonicDuration() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  return pulseIn(ECHO_PIN, HIGH);
}

// Function to convert duration to distance in cm
int durationToDistance(long duration) {
  int distance = duration * 0.034 / 2;
  if (distance > 200) distance = 200; // Cap distance to max 200 cm
  return distance;
}


void lineFollowing() {

  while (!exitApp) {
    if (digitalRead(RED_BUTTON) == LOW && digitalRead(BLUE_BUTTON) == LOW) {
      reinitialize();
      break;
    } else {
      // Read IR sensor values
      int leftSensor = digitalRead(LEFT_IR);
      int rightSensor = digitalRead(RIGHT_IR);

      // Line following logic
      if (leftSensor == LOW && rightSensor == LOW) {
        // Both sensors on the line: move forward
        forward();
      } else if (leftSensor == LOW && rightSensor == HIGH) {
        // Left sensor on the line, right sensor off: turn left
        left();
      } else if (leftSensor == HIGH && rightSensor == LOW) {
        // Right sensor on the line, left sensor off: turn right
        right();
      } else {
        // Both sensors off the line: stop
        stopBot();
      }

      // Small delay to stabilize the readings
      delay(50);
    }
  }
}



void obstacleAvoidance() {
  while (!exitApp) {
    if (digitalRead(RED_BUTTON) == LOW && digitalRead(BLUE_BUTTON) == LOW) {
      reinitialize();
      break;
    } else {
       long duration = getUltrasonicDuration();
      int distance = durationToDistance(duration);

      // Obstacle avoidance logic
      if (distance < 30) {
        // Obstacle detected: stop and turn
        stopBot();
        delay(500);  // Pause before turning
        right();
        delay(500); // Turn duration
      } else {
        // No obstacle: move forward
        forward();
      }

      // Small delay for stability
      delay(100);
    }
  }
}
