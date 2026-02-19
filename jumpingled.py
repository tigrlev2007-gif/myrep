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
            print(f"Инициализирован ЦАП с пинами {gpio_bits}, диапазон {dynamic_range}В")

    def deinit(self):
        GPIO.output(self.gpio_bits, GPIO.LOW)
        GPIO.cleanup()
        if self.verbose:
            print("GPIO очищены")

    def set_number(self, number):
        if number < 0 or number > 255:
            if self.verbose:
                print(f"Число {number} выходит за пределы 0-255")
            return

        bits = [(number >> i) & 1 for i in range(7, -1, -1)]
        GPIO.output(self.gpio_bits, bits)

        if self.verbose:
            print(f"Число на вход ЦАП: {number}, биты: {bits}")

    def set_voltage(self, voltage):
        max_voltage = self.dynamic_range
        min_voltage = 0.0

        if voltage < min_voltage or voltage > max_voltage:
            print(f"Напряжение выходит за динамический диапазон ЦАП ({min_voltage:.2f} - {max_voltage:.2f} В)")
            return

        number = int((voltage / max_voltage) * 255)
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
                print("Вы ввели не число. Попробуйте еще раз")

    except KeyboardInterrupt:
        print("\nПрограмма прервана пользователем")

    finally:
        if dac:
            dac.deinit()
