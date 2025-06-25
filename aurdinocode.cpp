#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Initialize the LCD at I2C address 0x27, 16 columns and 2 rows
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int piezoPin = A0;        // Piezo sensor connected to analog pin A0
int stepCount = 0;              // Step counter
int threshold = 100;            // Threshold for detecting steps
bool stepDetected = false;      // Flag to avoid multiple counts per step

void setup() {
  // Start the LCD
  lcd.begin(16, 2);
  lcd.backlight();

  // Scroll welcome message
  String message = "Foot Step Power Generation. by The SwiftCharge";
  for (int i = 0; i < message.length() - 15; i++) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(message.substring(i, i + 16));
    delay(300);
  }

  delay(500);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Steps: 0");
  lcd.setCursor(0, 1);
  lcd.print("Volt: 0.00V");

  Serial.begin(9600);  // Start serial communication
}

void loop() {
  int sensorValue = analogRead(piezoPin);
  float voltage = (sensorValue * (5.0 / 1023.0)) - 0.41;  // Voltage calculation

  // Step detection logic
  if (sensorValue > threshold && !stepDetected) {
    stepCount++;
    stepDetected = true;

    lcd.setCursor(0, 0);
    lcd.print("Steps: ");
    lcd.print(stepCount);
    lcd.print("   ");  // Clear remaining digits

    Serial.print("Step Detected. Count: ");
    Serial.println(stepCount);
  }

  // Reset step detection if signal drops
  if (sensorValue < threshold - 20) {
    stepDetected = false;
  }

  // Update voltage on LCD
  lcd.setCursor(0, 1);
  lcd.print("Volt: ");
  lcd.print(voltage, 2);
  lcd.print("V  ");  // Clear remaining chars

  delay(50);
}
