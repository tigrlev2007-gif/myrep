
import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BCM)

LIGHT_SENSOR_PIN = 6
LED_PIN = 24

GPIO.setup(LED_PIN, GPIO.OUT)
GPIO.output(LED_PIN, GPIO.LOW)

def read_light():
    GPIO.setup(LIGHT_SENSOR_PIN, GPIO.OUT)
    GPIO.output(LIGHT_SENSOR_PIN, GPIO.LOW)
    time.sleep(0.1)

    GPIO.setup(LIGHT_SENSOR_PIN, GPIO.IN)
    start = time.time()

    while GPIO.input(LIGHT_SENSOR_PIN) == GPIO.LOW:
        pass

    return time.time() - start

try:
    while True:
        light_level = read_light()

        if light_level > 0.01:
            GPIO.output(LED_PIN, GPIO.HIGH)
        else:
            GPIO.output(LED_PIN, GPIO.LOW)

        time.sleep(0.5)

except KeyboardInterrupt:
    GPIO.cleanup()
