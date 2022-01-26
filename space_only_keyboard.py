from BigRedButton.BigRedButton import *
import keyboard

with open("BigRedButton/mac.txt", 'r') as mac_file:
    mac_address = mac_file.readline()

port = 1
  
def press_space():
    keyboard.press('space')

def release_space():
    keyboard.release('space')

big_red_button = BigRedButton(port, mac_address)
big_red_button.set_triggered_function(press_space, "#big_red_button_press#")
big_red_button.set_triggered_function(release_space, "#big_red_button_unpress#")
big_red_button.set_triggered_function(big_red_button.connect, '#sleeping_paralysis#')
big_red_button.run(debug=True)