#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Initialize LCD: Address 0x27, 16 columns, 2 rows
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Define LED pins
#define GREEN_LED 13
#define RED_LED 4
#define BLUE_LED 12

// Define Button pins
#define RED_BUTTON 2
#define BLUE_BUTTON 3

void setup() {
  // Initialize LEDs as output
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);

  // Initialize buttons as input with pullup resistors
  pinMode(RED_BUTTON, INPUT_PULLUP);
  pinMode(BLUE_BUTTON, INPUT_PULLUP);

  // Start the LCD
  lcd.init();
  lcd.backlight();

  // Set default LED state
  digitalWrite(GREEN_LED, HIGH);
  digitalWrite(RED_LED, LOW);
  digitalWrite(BLUE_LED, LOW);

  // Display default message
  lcd.setCursor(0, 0);
  lcd.print("Status: Green ON");
}

void loop() {
  // Read button states
  bool redButtonPressed = digitalRead(RED_BUTTON) == LOW;
  bool blueButtonPressed = digitalRead(BLUE_BUTTON) == LOW;

  // Update LED states and LCD based on button press
  if (redButtonPressed) {
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(RED_LED, HIGH);
    digitalWrite(BLUE_LED, LOW);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Status: Red ON");
  } else if (blueButtonPressed) {
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(RED_LED, LOW);
    digitalWrite(BLUE_LED, HIGH);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Status: Blue ON");
  } else {
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(RED_LED, LOW);
    digitalWrite(BLUE_LED, LOW);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Status: Green ON");
  }

  // Add a small delay to debounce button presses
  delay(100);
}
