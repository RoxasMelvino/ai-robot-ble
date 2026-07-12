#include "CustomFunctions.h"

LiquidCrystal lcd(12, 11, 5, 4, 3, 2); 

void lcdInit(int numCols, int numRows, int cursorCol, int cursorRow) {
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Ready to move");
} 