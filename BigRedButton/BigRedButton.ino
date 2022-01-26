#include "BluetoothSerial.h"
#include "esp_bt_main.h"
#include "esp_bt_device.h"

BluetoothSerial SerialBT;

#define to_sleep_timer_value 3000 //Times 10 milliseconds
int to_sleep_timer;

// Start Red Button
// Button struct definition
struct buton_struct
{
  uint8_t PIN;
  uint8_t PIN_LED;
  int default_cooldown;
  int cooldown;
  bool was_pressed;
};

volatile buton_struct big_red_button = {33, 32, 50, 0, false};
void IRAM_ATTR button_press();
void IRAM_ATTR button_unpress();

// Red Button callback functions
void IRAM_ATTR button_press()
{
  if (big_red_button.cooldown == 0)
  {
    SerialBT.println("#big_red_button_press#");
    //    Serial.println("#big_red_button_press#");
    big_red_button.cooldown = big_red_button.default_cooldown;
    big_red_button.was_pressed = true;

    attachInterrupt(big_red_button.PIN, button_unpress, RISING);
  }
}

void IRAM_ATTR button_unpress()
{
  if (big_red_button.cooldown < (big_red_button.default_cooldown - 5)) {
    SerialBT.println("#big_red_button_unpress#");
    //    Serial.println("#big_red_button_unpress#");
    big_red_button.cooldown += 10;
    big_red_button.was_pressed = false;
    attachInterrupt(big_red_button.PIN, button_press, FALLING);
  }
}

// Red Button setup
void setup_big_red_button()
{
  pinMode(big_red_button.PIN, INPUT_PULLUP);
  pinMode(big_red_button.PIN_LED, OUTPUT);
  delay(10);
  attachInterrupt(big_red_button.PIN, button_press, FALLING);
}
// End Red Button


// Board setup
void setup()
{
  Serial.begin(115200);
  SerialBT.begin("Red Button"); //Bluetooth device name

  setup_big_red_button();
  digitalWrite(big_red_button.PIN_LED, LOW);
  to_sleep_timer = to_sleep_timer_value;
}

// Reboot callback
void callback() {
  SerialBT.begin("Red Button"); //Bluetooth device name
  to_sleep_timer = to_sleep_timer_value;
}

// Depp sleep manager
void deep_sleep() {
  #define Threshold 40
  touchAttachInterrupt(T7, callback, Threshold);

  esp_sleep_enable_touchpad_wakeup();
  //  Serial.println("me he dormido");
  SerialBT.println("#sleeping_paralysis#");
  SerialBT.disconnect();
  SerialBT.end();
  esp_deep_sleep_start();
}

// Main loop
void loop()
{
  if (big_red_button.cooldown > 0)
  {
    to_sleep_timer = to_sleep_timer_value;
    big_red_button.cooldown--;
    if (big_red_button.cooldown % 10 == 0)
      digitalWrite(big_red_button.PIN_LED, !digitalRead(big_red_button.PIN_LED));
  }

  if (big_red_button.cooldown == 0)
  {
    if (digitalRead(big_red_button.PIN) && big_red_button.was_pressed)
    {
      button_unpress();
    }
    if (digitalRead(big_red_button.PIN_LED)) {
      digitalWrite(big_red_button.PIN_LED, LOW);
    }
  }

  delay(10);
  to_sleep_timer--;
  if (to_sleep_timer == 0) {
    deep_sleep();
  }
}
