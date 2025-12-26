from math import isqrt

def isPrime(n: int) -> bool:
    if n <= 1:
        return False
    if n in [2, 3, 5]:
        return True
    if n % 2 == 0 or n % 3 == 0 or n % 5 == 0:
        return False

    isqrtn, i = isqrt(n), 5
    while i <= isqrtn:
        if n % i == 0 or n % (i + 2) == 0:
            return False
        i += 6
        
    return True

def main() -> None:
    n = int(input("Podaj liczbe: "))
    print("TAK" if isPrime(n) else "NIE")

if __name__ == "__main__": main()