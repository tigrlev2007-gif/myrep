import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BCM)

BUTTON_PIN = 17
LED_PIN = 24

GPIO.setup(BUTTON_PIN, GPIO.IN, pull_up_down=GPIO.PUD_UP)
GPIO.setup(LED_PIN, GPIO.OUT)
GPIO.output(LED_PIN, GPIO.LOW)

try:
    while True:
        if GPIO.input(BUTTON_PIN) == GPIO.LOW:
            GPIO.output(LED_PIN, GPIO.HIGH)
        else:
            GPIO.output(LED_PIN, GPIO.LOW)
        time.sleep(0.05)

except KeyboardInterrupt:
    GPIO.cleanup()
