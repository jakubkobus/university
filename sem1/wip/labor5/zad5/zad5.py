from math import cos
from typing import Callable

def myFun(x: float) -> float:
    return cos(x / 2)

def findZero(f: Callable[[float], float], a: float, b: float, eps: float) -> float:
    mid = 0.0

    while (b - a) / 2 > eps:
        mid = (a + b) / 2

        if f(mid) == 0.0:
            return mid
        elif f(a) * f(mid) < 0:
            b = mid
        else:
            a = mid

    return (a + b) / 2

def main() -> None:
    epsilon = [ 1e-1, 1e-2, 1e-3, 1e-4, 1e-5, 1e-6, 1e-7, 1e-8 ]
    a, b = 2.0, 4.0

    for i in range(len(epsilon)):
        x0 = findZero(myFun, a, b, epsilon[i])
        print(f"x0 = {x0:.{len(epsilon) + 1}f} : epsilon = {epsilon[i]:.{i + 1}f}")

if __name__ == "__main__": main()
