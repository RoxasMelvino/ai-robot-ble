#ifndef __CUSTOM_FUNCTIONS_H__
#define __CUSTOM_FUNCTIONS_H__

#include <Arduino.h>
#include <LiquidCrystal.h>

extern LiquidCrystal lcd;

void lcdInit(int numCols = 16, int numRows = 2, int cursorCol = 0, int cursorRow = 0);
void lcdPrintVals(float x, float y, float w);
void drive(float dir, float speed, int motorPwmPin);

#endif  // __CUSTOM_FUNCTIONS_H__