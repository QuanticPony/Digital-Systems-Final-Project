from BigRedButton import *
import keyboard

with open("BigRedButton/mac.txt", 'r') as mac_file:
    mac_address = mac_file.readline()

port = 1
  
def say_hello():
    print("Hello\n")

def say_goodbye():
    print("Goodbye\n")

big_red_button = BigRedButton(port, mac_address)
big_red_button.set_triggered_function(say_hello, "#big_red_button_press#")
big_red_button.set_triggered_function(say_goodbye, "#big_red_button_unpress#")
big_red_button.set_triggered_function(big_red_button.connect, '#sleeping_paralysis#')
big_red_button.run(debug=True)