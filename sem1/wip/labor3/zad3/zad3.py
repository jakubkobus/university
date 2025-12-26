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

def main() -> None:
    n = input("Podaj liczbe: ")
    
    if n.isdigit() and int(n) > 1:
        try:
            primes = countPrimes(int(n))
            print(f"Ilosc liczb pierwszych w zakresie 2 .. {n} = {primes}")
        except MemoryError:
            print("Przekroczono limit pamieci")
    else:
        print("Dozwolone wartosci w zakresie 2 .. +x")
    

if __name__ == "__main__": main()