def main() -> None:
    print("Podaj: n p");
    n, p = map(int, input().split(' '))
    t, m = n, 0;
    
    while t >= 1:
        m = m * p + (t % p)
        t //= p
        
    if m == n: print("TAK")
    else: print("NIE")

if __name__ == "__main__":
    main()