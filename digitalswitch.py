import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BCM)

BUTTON_PIN = 17
LED_PIN = 24

GPIO.setup(BUTTON_PIN, GPIO.IN, pull_up_down=GPIO.PUD_UP)
GPIO.setup(LED_PIN, GPIO.OUT)

led_state = False
last_button = GPIO.HIGH

try:
    while True:
        current_button = GPIO.input(BUTTON_PIN)

        if last_button == GPIO.HIGH and current_button == GPIO.LOW:
            led_state = not led_state
            GPIO.output(LED_PIN, led_state)
            time.sleep(0.2)

        last_button = current_button
        time.sleep(0.01)

except KeyboardInterrupt:
    GPIO.cleanup()
