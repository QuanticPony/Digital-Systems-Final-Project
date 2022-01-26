from time import sleep
from BigRedButton.BigRedButton import *
import keyboard
import webbrowser as wb

with open("BigRedButton/mac.txt", 'r') as mac_file:
    mac_address = mac_file.readline()

port = 1

class privacy_ensurer:
    def __init__(self, n):
        self.default_counter = n
        self.counter = 0

    def __call__(self):
        if self.counter == 0:
            self.counter = self.default_counter

        if self.counter > 1:
            keyboard.press_and_release('win+d')
        else:
            self.privacy_release()

        self.counter -= 1
    
    @staticmethod
    def privacy_release():
        try:
            wb.open("https://www.youtube.com/watch?v=dQw4w9WgXcQ", autoraise=True)
            sleep(0.7)
            keyboard.press_and_release('space')
        except Exception as err:
            pass





big_red_button = BigRedButton(port, mac_address)
big_red_button.set_triggered_function(privacy_ensurer(3), "#big_red_button_press#")
big_red_button.set_triggered_function(big_red_button.connect, '#sleeping_paralysis#')
big_red_button.run()