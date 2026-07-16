#include "CustomFunctions.h"

LiquidCrystal lcd(12, 11, 5, 4, 3, 2); 

void lcdInit(int numCols, int numRows, int cursorCol, int cursorRow) {
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Ready to Connect");
} 

void lcdPrintVals(float x, float y, float w) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("X    Y    W");
  lcd.setCursor(0, 1); 
  lcd.print(x);
  lcd.print(" ");
  lcd.print(y);
  lcd.print(" ");
  lcd.print(w);
} 

void drive(float dir, float speed, int motorPwmPin) {
  float motorSpeed = dir * speed; 
  analogWrite(motorPwmPin, motorSpeed); 
}