# Bluetooth Low Energy
The AI robot will be controlled by a Bluetooth Low Energy controller, which will be our phones (the central device) at the time being. 

# BLE Controller - Arduino ESP 32 (App Store)
We're using the app labeled above to connect to the Arduino board (peripheral device). It's fast, works like a gaming controller, and contains all the features we need for now. Each button can map to values, which will be used to write characteristic data. 

**NOTE**: This app, however, is only able to write data to one characteristic, and it is restricted to one data type, string (or character), instead of sending an actual number. It was either this or typing integers to write data. Many apps were used but fell to the same lackluster features just mentioned. The problem is that this forces the peripheral device to dump all of the data sent by the central into one characteristic as a string, which also forces the code to parse it. 
