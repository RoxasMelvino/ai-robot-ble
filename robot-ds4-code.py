import evdev

raw_vals = { "ABS_X" : 0.00, "ABS_Y" : 0.00, "ABS_RX": 0.00 }
js_max = 255
js_center = js_max / 2
deadzone_thresh = 0.06

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
            raw_vals[button_name] = event.value
        elif (button_name == "ABS_Y"):
            raw_vals[button_name] = event.value
        elif (button_name == "ABS_RX"):
            raw_vals[button_name] = event.value
    
        # we need the center to be 0, otherwise the motors will move by themselves
        x_percent = round((raw_vals["ABS_X"] - js_center) / (js_max - js_center), 2)
        y_percent = round((raw_vals["ABS_Y"] - js_center) / (js_max - js_center), 2) * -1
        w_percent = round((raw_vals["ABS_RX"] - js_center) / (js_max - js_center), 2)
        
        if (abs(x_percent) < deadzone_thresh) : x_percent = 0.00
        if (abs(y_percent) < deadzone_thresh) : y_percent = 0.00
        if (abs(w_percent) < deadzone_thresh) : w_percent = 0.00
        
        action_space = f"{x_percent},{y_percent},{w_percent}\n"
        print(action_space)

# The values of joysticks and triggers range from 0 to 255, but we mainly care about the joysticks for now.
# the center needs to be 0, otherwise the motors wil move on their own 





 






        
        





