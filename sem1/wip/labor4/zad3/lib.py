from math import isqrt

def computeSieve(n: int) -> list[bool]:
    sieve = [True] * (n + 1)
    
    for i in range(2, n + 1):
        if sieve[i]:
            j = i + i
            while j <= n:
                sieve[j] = False
                j += i
    
    return sieve

def countPrimes(n: int) -> int:
    sieve = computeSieve(n)
    numberOfPrimes = 0
    
    for i in range(2, n + 1):
        if sieve[i]:
            numberOfPrimes += 1
    
    return numberOfPrimes

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