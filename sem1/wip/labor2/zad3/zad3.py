def NWD(a: int, b: int) -> int:
    while b != 0:       
        a, b = b, a % b
        
    return abs(a)

def main() -> None:
    print("Podaj: a b")
    a, b = map(int, input().split(' '))
    
    print(f"NWD = {NWD(a, b)}")

if __name__ == "__main__": main()