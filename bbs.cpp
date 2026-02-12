import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BCM)

# Настройка пинов
BUTTON_PIN = 17  # пин кнопки
LED_PIN = 24     # пин светодиода

GPIO.setup(BUTTON_PIN, GPIO.IN, pull_up_down=GPIO.PUD_UP)  # подтяжка к питанию
GPIO.setup(LED_PIN, GPIO.OUT)

led_state = False  # начальное состояние - выключен
last_button_state = GPIO.HIGH  # предыдущее состояние кнопки

GPIO.output(LED_PIN, led_state)

try:
    print("Программа запущена")
    print("Нажмите кнопку чтобы включить светодиод")
    print("Нажмите ещё раз чтобы выключить")
    print("Ctrl+C для выхода")
    print("-" * 30)

    while True:
        # Читаем текущее состояние кнопки
        current_button_state = GPIO.input(BUTTON_PIN)

        # Проверяем нажатие (переход из HIGH в LOW)
        if last_button_state == GPIO.HIGH and current_button_state == GPIO.LOW:
            # Меняем состояние светодиода на противоположное
            led_state = not led_state
            GPIO.output(LED_PIN, led_state)

            if led_state:
                print("💡 Светодиод ВКЛ")
            else:
                print("⚫ Светодиод ВЫКЛ")

            # Защита от дребезга контактов
            time.sleep(0.2)

        # Запоминаем текущее состояние для следующей итерации
        last_button_state = current_button_state

        # Небольшая задержка
        time.sleep(0.01)

except KeyboardInterrupt:
    print("\nПрограмма остановлена")

finally:
    GPIO.cleanup()
