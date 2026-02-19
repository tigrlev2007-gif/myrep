import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BCM)

LED_PINS = [16, 20, 21, 25, 26, 17, 27, 22]
DYNAMIC_RANGE = 3.183

for pin in LED_PINS:
    GPIO.setup(pin, GPIO.OUT)
    GPIO.output(pin, GPIO.LOW)

def voltage_to_binary(voltage):
    if voltage < 0 or voltage > DYNAMIC_RANGE:
        print(f"Напряжение выходит за диапазон (0 - {DYNAMIC_RANGE} В)")
        return None

    number = int((voltage / DYNAMIC_RANGE) * 255)
    bits = [(number >> i) & 1 for i in range(7, -1, -1)]

    print(f"Напряжение: {voltage} В")
    print(f"Число: {number}")
    print(f"Биты: {bits}")

    return bits

def set_leds(bits):
    if bits:
        GPIO.output(LED_PINS, bits)

try:
    while True:
        try:
            voltage = float(input("Введите напряжение в Вольтах: "))
            bits = voltage_to_binary(voltage)
            set_leds(bits)
            time.sleep(0.5)
        except ValueError:
            print("Ошибка: введите число")

except KeyboardInterrupt:
    GPIO.cleanup()
