#
# Raspberry Pi 5
#
import gpiod
import time

chip = gpiod.Chip('gpiochip4')
led_pin = 21

led_line = chip.get_line(led_pin)
led_line.request(consumer="LED", type=gpiod.LINE_REQ_DIR_OUT)

try:
   while True:
        led_line.set_value(1)
        time.sleep(1)
        led_line.set_value(0)
        time.sleep(1)  # Sleep for one second
finally:
    led_line.release()