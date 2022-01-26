# Files description:
## BigRedButton.ino
Esp32 board source code for a button with a led and a touch input for battery managment.

## BigRedButton.py 
Python Bluetooth interface with the esp32 board. Board's MAC address is needed for conexion.
```py
BigRedButton(port, mac_address, proto=socket.BTPROTO_RFCOMM, timeout=None)
```
Supports auto-reconnect. And custmizable callback functions for following events:
```py
"#big_red_button_press#" # When button is pressed
"#big_red_button_unpress#" # When button is unpressed 
"#sleeping_paralysis#" # When deep-sleep is activated
```

## test_interface.py
Simple example of BigRedButton.py use.