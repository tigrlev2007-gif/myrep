#!/usr/bin/env python3
import RPi.GPIO as GPIO
import math
import time

class DAC:
    def init(self, pins, vmax=3.3):
        self.pins = pins
        self.vmax = vmax
        
        GPIO.setmode(GPIO.BCM)
        for p in pins:
            GPIO.setup(p, GPIO.OUT)
            GPIO.output(p, 0)
    
    def out(self, v):
        v = max(0, min(self.vmax, v))
        num = int((v / self.vmax) * 255)
        
        for i, p in enumerate(self.pins):
            GPIO.output(p, (num >> (7-i)) & 1)
    
    def stop(self):
        for p in self.pins:
            GPIO.output(p, 0)
        GPIO.cleanup()

# Пины и настройки
dac = DAC([16,20,21,25,26,17,27,22], 3.3)

try:
    print("Синус 50 Гц на осциллограф")
    t0 = time.time()
    
    while True:
        t = time.time() - t0
        v = 1.65 + 1.5 * math.sin(2 * math.pi * 50 * t)  # 50 Гц
        dac.out(v)
        time.sleep(0.0005)  # 2 кГц
        
except KeyboardInterrupt:
    dac.stop()
