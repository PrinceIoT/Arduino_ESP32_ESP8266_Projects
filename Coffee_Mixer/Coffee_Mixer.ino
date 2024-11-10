#include <HX711.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Define pins for HX711 modules
#define WATER_LOADCELL_DOUT 2
#define WATER_LOADCELL_CLK 3
#define COFFEE_LOADCELL_DOUT 4
#define COFFEE_LOADCELL_CLK 5

// Define button pins
#define RATIO_SELECTION_PIN A0
#define WATER_VESSEL_PIN A1
#define COFFEE_VESSEL_PIN A2
#define PLAY_PIN A3

// Define ratios
#define RATIO_MIN 15
#define RATIO_MAX 18

HX711 waterLoadCell;
HX711 coffeeLoadCell;

LiquidCrystal_I2C lcd(0x27, 16, 2);

int selectedRatio = RATIO_MIN;
float waterWeight = 0;
float coffeeWeight = 0;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.backlight();
  
  pinMode(RATIO_SELECTION_PIN, INPUT);
  pinMode(WATER_VESSEL_PIN, INPUT);
  pinMode(COFFEE_VESSEL_PIN, INPUT);
  pinMode(PLAY_PIN, INPUT);
  
  waterLoadCell.begin(WATER_LOADCELL_DOUT, WATER_LOADCELL_CLK);
  coffeeLoadCell.begin(COFFEE_LOADCELL_DOUT, COFFEE_LOADCELL_CLK);
  
  // Calibrate load cells if needed
  waterLoadCell.set_scale();
  coffeeLoadCell.set_scale();
}

void loop() {
  lcd.clear();
  lcd.print("Select Ratio: ");
  lcd.setCursor(0, 1);
  lcd.print("1:" + String(selectedRatio));
  
  while (digitalRead(PLAY_PIN) == HIGH) {
    // Ratio Selection
    int ratioValue = analogRead(RATIO_SELECTION_PIN);
    selectedRatio = map(ratioValue, 0, 1023, RATIO_MIN, RATIO_MAX);
    delay(100); // Debounce delay
  }
  
  waitForButtonRelease(PLAY_PIN);
  
  // Water Vessel Selection
  lcd.clear();
  lcd.print("Place Water Vessel");
  lcd.setCursor(0, 1);
  lcd.print("Press Play");
  
  waitForButtonPress(PLAY_PIN);
  waterWeight = getWeight(WATER_LOADCELL_DOUT, WATER_LOADCELL_CLK, "Water Vessel");
  waitForButtonRelease(PLAY_PIN);
  
  // Coffee Vessel Selection
  lcd.clear();
  lcd.print("Place Coffee Vessel");
  lcd.setCursor(0, 1);
  lcd.print("Press Play");
  
  waitForButtonPress(PLAY_PIN);
  coffeeWeight = getWeight(COFFEE_LOADCELL_DOUT, COFFEE_LOADCELL_CLK, "Coffee Vessel");
  waitForButtonRelease(PLAY_PIN);
  
  // Calculate Coffee Weight
  float targetCoffeeWeight = waterWeight / selectedRatio;
  
  // Coffee Addition
  lcd.clear();
  lcd.print("Add Coffee");
  lcd.setCursor(0, 1);
  lcd.print("Target: " + String(targetCoffeeWeight) + "g");
  
  while (coffeeWeight < targetCoffeeWeight) {
    coffeeWeight = getWeight(COFFEE_LOADCELL_DOUT, COFFEE_LOADCELL_CLK, "Coffee Vessel");
    lcd.clear();
    lcd.print("Add Coffee: " + String(targetCoffeeWeight - coffeeWeight) + "g");
    delay(500);
  }
  
  // Golden Ratio Achieved
  lcd.clear();
  lcd.print("Golden Ratio!");
  tone(8, 3000, 500); // Beep to indicate golden ratio achieved
  delay(1000);
}

float getWeight(int doutPin, int clkPin, String itemName) {
  HX711 loadCell;
  loadCell.begin(doutPin, clkPin);
  loadCell.set_scale();
  
  lcd.clear();
  lcd.print(itemName);
  
  float weight = 0;
  for (int i = 0; i < 10; ++i) {
    weight += loadCell.get_units(1);
    delay(50);
  }
  weight /= 10.0;
  
  lcd.setCursor(0, 1);
  lcd.print("Weight: " + String(weight) + "g");
  
  return weight;
}

void waitForButtonPress(int buttonPin) {
  while (digitalRead(buttonPin) == LOW) {
    delay(100);
  }
  delay(500); // Debounce delay
}

void waitForButtonRelease(int buttonPin) {
  while (digitalRead(buttonPin) == HIGH) {
    delay(100);
  }
  delay(500); // Debounce delay
}
