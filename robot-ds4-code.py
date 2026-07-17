import evdev
import serial
import time

ser = serial.Serial('/dev/ttyACM0', 115200, timeout=1)
time.sleep(2)
print(ser.name)

# The values of joysticks and triggers range from 0 to 255, but we mainly care about the left and right joysticks for now.
js_max = 255
js_center = js_max / 2
js_raw_x = js_center
js_raw_y = js_center
js_raw_w = js_center
deadzone_thresh = 0.10

#search for devices
devices = [evdev.InputDevice(path) for path in evdev.list_devices()] 
for device in devices: 
    print(device.name)
    if (device.name == "Wireless Controller"):
        ds4ControllerPath = device.path
        
ds4Controller = evdev.InputDevice(ds4ControllerPath)

for event in ds4Controller.read_loop():
    if event.type == evdev.ecodes.EV_ABS:
        button_name = evdev.ecodes.ABS[event.code]
        if (button_name == "ABS_X"):
            js_raw_x = event.value
        elif (button_name == "ABS_Y"):
            js_raw_y = event.value
        elif (button_name == "ABS_RX"): # right joystick
            js_raw_w = event.value
            
    if event.type == evdev.ecodes.EV_SYN :
        # we need the center to be 0, otherwise the motors will move by themselves
        x_percent = round((js_raw_x - js_center) / (js_max - js_center), 2)
        y_percent = round((js_raw_y - js_center) / (js_max - js_center), 2) * -1
        w_percent = round((js_raw_w - js_center) / (js_max - js_center), 2)
        
        if (abs(x_percent) < deadzone_thresh) : x_percent = 0.00
        if (abs(y_percent) < deadzone_thresh) : y_percent = 0.00
        if (abs(w_percent) < deadzone_thresh) : w_percent = 0.00
        
        action_space = f"{x_percent},{y_percent},{w_percent}\n"
        # print(action_space)
        ser.write(action_space.encode())
        ser.flush()
        if ser.in_waiting > 0 :
            print("Arduino Serial", ser.readline().decode('utf-8'))
        
ser.close()







 






        
        





