#!/usr/bin/env python3
import RPi.GPIO as GPIO

class DAC:
    def init(self, pin):
        self.pin = pin
        GPIO.setmode(GPIO.BCM)
        GPIO.setup(pin, GPIO.OUT)
        self.pwm = GPIO.PWM(pin, 1000)
        self.pwm.start(0)
    
    def out(self, volts):
        duty = (volts / 3.3) * 100
        self.pwm.ChangeDutyCycle(duty)
        print(f"{volts}V на пине {self.pin}")
    
    def stop(self):
        self.pwm.stop()
        GPIO.cleanup()

# Используем
dac = DAC(18)  # ← пин OUT
dac.out(2.0)   # ← 2 вольта

try:
    input("Нажми Enter для выхода...")
finally:
    dac.stop()
