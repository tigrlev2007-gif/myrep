#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import RPi.GPIO as GPIO

class R2R_DAC:
    def init(self, pins, v_min=0.0, v_max=3.3):
        self.pins = pins
        self.v_min = v_min
        self.v_max = v_max
        
        GPIO.setmode(GPIO.BCM)
        for pin in pins:
            GPIO.setup(pin, GPIO.OUT)
            GPIO.output(pin, 0)
    
    def set(self, voltage):
        """Установить напряжение"""
        # Считаем число для ЦАП
        value = int((voltage - self.v_min) / (self.v_max - self.v_min) * 255)
        value = max(0, min(255, value))
        
        # Выставляем биты
        for i, pin in enumerate(self.pins):
            GPIO.output(pin, (value >> (7-i)) & 1)
    
    def off(self):
        """Выключить (0 В)"""
        for pin in self.pins:
            GPIO.output(pin, 0)
        GPIO.cleanup()

# ============ ПРОСТОЕ ИСПОЛЬЗОВАНИЕ ============

# Создаем ЦАП
dac = R2R_DAC(
    pins=[17, 18, 22, 23, 24, 25, 26, 27],  # пины
    v_min=0.0,                                # минимум
    v_max=3.3                                 # максимум
)

try:
    # Устанавливаем напряжение (меняй это число)
    dac.set(2.5)  # ← СЮДА ПИШИ СВОЕ НАПРЯЖЕНИЕ
    
    print("Напряжение установлено!")
    print("Работает... (нажми Ctrl+C для выхода)")
    
    # Бесконечный цикл, чтобы программа не закрылась
    while True:
        pass
        
except KeyboardInterrupt:
    print("\nВыключаем...")
finally:
    dac.off()
