#include <LiquidCrystal.h>  // Include the LCD library

// Initialize the LCD: RS, E, D4, D5, D6, D7 pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int ledPin = 9;    // LED for visual feedback
int buzzerPin = 10; // Buzzer for sound feedback
int heartRatePin = A0; // Heart rate sensor connected to A0
int threshold = 1018; // Set a threshold value for detecting stress (adjust as needed)
int heartRateValue = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);  // Start serial communication for debugging
  
  // LCD initialization
  lcd.begin(16, 2);  // Initialize the LCD with 16 columns and 2 rows
  lcd.print("Heart Rate:");  // Initial message
}

void loop() {
  heartRateValue = analogRead(heartRatePin);  // Read the heart rate sensor value

  // Print heart rate value to the Serial Monitor for debugging
  Serial.print("Heart Rate Value: ");
  Serial.println(heartRateValue);

  // Update the LCD with the current heart rate value
  lcd.setCursor(0, 1);  // Move to the second row
  lcd.print("Value: ");
  lcd.print(heartRateValue);  // Display the heart rate value on the LCD

  // If heart rate exceeds the threshold, trigger the breathing exercise
  if (heartRateValue > threshold) {
    // Inhale phase (4 seconds)
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Inhale...");
    digitalWrite(ledPin, HIGH);    // Turn LED on (inhale)
    tone(buzzerPin, 440);          // Play sound at 440 Hz
    delay(4000);                   // Wait for 4 seconds
    
    // Exhale phase (6 seconds)
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Exhale...");
    digitalWrite(ledPin, LOW);     // Turn LED off (exhale)
    noTone(buzzerPin);             // Stop sound
    delay(6000);                   // Wait for 6 seconds

  }

  delay(2000);  // Wait 2 seconds before the next reading
}




