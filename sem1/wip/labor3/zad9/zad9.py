from math import isqrt

def nthPrime(n: int) -> int:
    if n < 1: return 0
    
    primes = [2] * n
    candidate = 3
    iterator = 1
    i, s = None, None
    isPrime = None
    
    while iterator < n:
        s = isqrt(candidate)
        isPrime = True
        i = 1
        
        while isPrime and primes[i] <= s and i < iterator:
            if candidate % primes[i] == 0: isPrime = False
            else: i += 1
        
        if isPrime:
            primes[iterator] = candidate
            iterator += 1
        
        candidate += 2
    
    return primes[n - 1]

def main() -> None:
    n = int(input("Podaj n: "))
    print(f"{n} liczba pierwsza = {nthPrime(n)}")

if __name__ == "__main__": main()