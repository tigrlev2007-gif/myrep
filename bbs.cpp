def get_triangle_voltage(freq=1, amp=1.65, offset=1.65):
    """Возвращает текущее напряжение треугольной формы"""
    t = time.time()
    period = 1.0 / freq
    t_mod = (t % period) / period
    
    if t_mod < 0.5:
        val = 4 * t_mod - 1
    else:
        val = 3 - 4 * t_mod
    
    return offset + amp * val

# В цикле программы:
while True:
    voltage = get_triangle_voltage(freq=10, amp=1.5, offset=1.65)
    dac.set_voltage(voltage)
    time.sleep(0.001)stop()
