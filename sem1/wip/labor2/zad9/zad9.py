def main():
    n = int(input("Podaj liczbe: "))
    
    result = []
    print(f"{n}=", end="")
    
    while n % 2 == 0:
        result.append(2)
        n //= 2
        
    t = 3
    while n > 1:
        if t * t > n:
            result.append(n)
            n = 1
        else:
            while n % t == 0:
                result.append(t)
                n //= t
            
            t += 2

    n, t = result[0], 1
    
    for i in range(1, len(result)):
        if result[i] == n: t += 1
        else:
            if t == 1: print(f"{n}*", end="")
            else: print(f"{n}^{t}*", end="")
            
            n, t = result[i], 1

    if t == 1: print(n)
    else: print(f"{n}^{t}")

if __name__ == "__main__": main()