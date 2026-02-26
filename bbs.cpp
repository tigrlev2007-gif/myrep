import RPi.GPIO as GPIO

class R2R_DAC:
    def init(self, gpio_bits, dynamic_range):
        self.gpio_bits = gpio_bits
        self.dynamic_range = dynamic_range
        
        GPIO.setmode(GPIO.BCM)
        for pin in self.gpio_bits:
            GPIO.setup(pin, GPIO.OUT)
            GPIO.output(pin, GPIO.LOW)
    
    def deinit(self):
        GPIO.output(self.gpio_bits, 0)
        GPIO.cleanup()
    
    def voltage_to_number(self, voltage):
        if not (0.0 <= voltage <= self.dynamic_range):
            print(f"Напряжение выходит за динамический диапазон ЦАП (0.00 - {self.dynamic_range:.2f} В)")
            print("Устанавливаем 0.0 В")
            return 0
        return int(voltage / self.dynamic_range * 255)
    
    def number_to_dac(self, number):
        bits = [(number >> i) & 1 for i in range(7, -1, -1)]
        GPIO.output(self.gpio_bits, bits)
        print(f"Число на вход ЦАП: {number}, биты: {bits}")
    
    def set_voltage(self, voltage):
        number = self.voltage_to_number(voltage)
        self.number_to_dac(number)

if name == "main":
    dac = None
    try:
        dac = R2R_DAC([16, 20, 21, 25, 26, 17, 27, 22], 3.3)
        
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
