import RPi.GPIO as GPIO

class R2R_DAC:
    def init(self, gpio_bits, dynamic_range, verbose=False):
        self.gpio_bits = gpio_bits
        self.dynamic_range = dynamic_range
        self.verbose = verbose
        
        GPIO.setmode(GPIO.BCM)
        for pin in self.gpio_bits:
            GPIO.setup(pin, GPIO.OUT)
            GPIO.output(pin, GPIO.LOW)
        
        if self.verbose:
            print(f"ЦАП инициализирован. Пины: {gpio_bits}")
            print(f"Динамический диапазон: {dynamic_range} В")
    
    def deinit(self):
        GPIO.output(self.gpio_bits, GPIO.LOW)
        GPIO.cleanup()
        if self.verbose:
            print("GPIO очищены")
    
    def set_number(self, number):
        if number < 0 or number > 255:
            if self.verbose:
                print(f"Ошибка: число {number} вне диапазона 0-255")
            return
        
        bits = [(number >> i) & 1 for i in range(7, -1, -1)]
        GPIO.output(self.gpio_bits, bits)
        
        if self.verbose:
            print(f"Число: {number}, биты: {bits}")
    
    def set_voltage(self, voltage):
        if voltage < 0 or voltage > self.dynamic_range:
            print(f"Напряжение {voltage} В вне диапазона (0 - {self.dynamic_range:.2f} В)")
            return
        
        number = int((voltage / self.dynamic_range) * 255)
        self.set_number(number)

if name == "main":
    dac = None
    try:
        dac = R2R_DAC([16, 20, 21, 25, 26, 17, 27, 22], 3.183, True)
        
        while True:
            try:
                voltage = float(input("Введите напряжение в Вольтах: "))
                dac.set_voltage(voltage)
            except ValueError:
                print("Вы ввели не число. Попробуйте ещё раз\n")
    
    except KeyboardInterrupt:
        print("\nПрограмма прервана пользователем")
    
    finally:
        if dac:
            dac.deinit()
