def primeFactors(n: int) -> list[int]:
    t, result = 3 ,[]
    
    while n % 2 == 0:
        result.append(2)
        n //= 2
    
    while n > 1:
        if t * t > n:
            result.append(n)
            n = 1
        else:
            while n % t == 0:
                result.append(t)
                n //= t

            t += 2
    
    return result

def totient(n: int) -> int:
    if n == 1: return 1

    factors = primeFactors(n)
    
    for i in range(len(factors)):
        if i == 0:
            n -= n // factors[i]
        elif factors[i] != factors[i - 1]:
            n -= n // factors[i]
    
    return n