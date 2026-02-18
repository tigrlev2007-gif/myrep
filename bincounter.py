import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BCM)

BUTTON_UP = 10
BUTTON_DOWN = 9
LED_PINS = [24, 22, 23, 27]

for pin in LED_PINS:
    GPIO.setup(pin, GPIO.OUT)
    GPIO.output(pin, GPIO.LOW)

GPIO.setup(BUTTON_UP, GPIO.IN, pull_up_down=GPIO.PUD_UP)
GPIO.setup(BUTTON_DOWN, GPIO.IN, pull_up_down=GPIO.PUD_UP)

counter = 0
last_up = GPIO.HIGH
last_down = GPIO.HIGH

try:
    while True:
        up_state = GPIO.input(BUTTON_UP)
        down_state = GPIO.input(BUTTON_DOWN)

        if last_up == GPIO.HIGH and up_state == GPIO.LOW:
            if counter < 15:
                counter += 1
            time.sleep(0.2)

        if last_down == GPIO.HIGH and down_state == GPIO.LOW:
            if counter > 0:
                counter -= 1
            time.sleep(0.2)

        GPIO.output(LED_PINS[0], (counter >> 0) & 1)
        GPIO.output(LED_PINS[1], (counter >> 1) & 1)
        GPIO.output(LED_PINS[2], (counter >> 2) & 1)
        GPIO.output(LED_PINS[3], (counter >> 3) & 1)

        last_up = up_state
        last_down = down_state
        time.sleep(0.01)

except KeyboardInterrupt:
    GPIO.cleanup()
