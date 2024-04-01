import random
import math
# import matplotlib.pyplot as plt
# =FLOOR.MATH($B4/POWER(C$177,LEN(C4)/2))

START_BASE = 2
END_BASE = 11

def approx_sqrt(num, base):
    print(f"Half-Length {len(str(num)) / 2}")
    print(f"Num is {num} (Base {base})")
    return int(str(num), base) / math.pow(base, len(str(num)) / 2)
def actual_sqrt(num, base):
    num = int(str(num), base)
    print(f"Num is {num}")
    return math.sqrt(num)

def compare_accuracy(approx_func, actual_func, value, base):
    approximated_value = approx_func(value, base)
    print(f"Approximated Value: {approximated_value}")
    actual_value = actual_func(value, base)
    print(f"Actual Value: {actual_value}")
    if actual_value == 0:
        return 100 if approximated_value != 0 else 0
    else:
        accuracy_percentage = min(abs(approximated_value - actual_value) / actual_value * 100, 100)
        return accuracy_percentage

if __name__ == "__main__":
    print(100 - compare_accuracy(approx_sqrt, actual_sqrt, 1, 1.5))
