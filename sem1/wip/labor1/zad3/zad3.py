def main() -> None:
    print("Podaj: a b")
    a, b = map(int, input().split(' '))
    
    while b != 0:       
        a, b = b, a % b
        
    if a < 0: a *= -1
    
    print(f"NWD = {a}")

if __name__ == "__main__":
    main()