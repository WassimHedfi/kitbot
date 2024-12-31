//ultrasonic distance with buzzer and lcd
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Initialize LCD: Address 0x27, 16 columns, 2 rows
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Define Ultrasonic Sensor pins
#define TRIG_PIN A3
#define ECHO_PIN A2

// Define LED and Buzzer pins
#define RED_LED 4
#define GREEN_LED 13
#define BUZZER 9

// Define safe distance (in cm)
#define SAFE_DISTANCE 15

void setup() {
  // Initialize LEDs and buzzer as output
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  // Initialize ultrasonic sensor pins
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // Start the LCD
  lcd.init();
  lcd.backlight();

  // Default state
  digitalWrite(GREEN_LED, HIGH);
  digitalWrite(RED_LED, LOW);
  digitalWrite(BUZZER, LOW);

  // Display initial message
  lcd.setCursor(0, 0);
  lcd.print("Distance:");
}

void loop() {
  // Measure distance
  long duration, distance;

  // Send a 10-microsecond pulse to trigger pin
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Read the echo pin and calculate distance
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = duration * 0.034 / 2; // Convert to cm

  // Display the distance on the LCD
  lcd.setCursor(0, 1);
  lcd.print(" ");
  lcd.setCursor(0, 1);
  lcd.print(distance);
  lcd.print(" cm ");

  // React to the measured distance
  if (distance < SAFE_DISTANCE) {
    // If the distance is below the safe limit
    digitalWrite(RED_LED, HIGH);
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(BUZZER, HIGH);

    lcd.setCursor(12, 1);
    lcd.print("ALERT");
  } else {
    // If the distance is safe
    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(BUZZER, LOW);

    lcd.setCursor(12, 1);
    lcd.print("SAFE ");
  }

  // Small delay to avoid excessive measurement
  delay(200);
}
