#ifndef __CUSTOM_FUNCTIONS_H__
#define __CUSTOM_FUNCTIONS_H__

#include <LiquidCrystal.h>

extern LiquidCrystal lcd; 

void lcdInit(int numCols = 16, int numRows = 2, int cursorCol = 0, int cursorRow = 0); 

#endif // __CUSTOM_FUNCTIONS_H__