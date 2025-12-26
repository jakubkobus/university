import sys, lib

def main() -> None:
    if len(sys.argv) != 3:
        print("Nieprawidlowe uzycie")
        sys.exit(1)
        
    if sys.argv[1] == "pn":
        print(lib.countPrimes(int(sys.argv[2])))
    elif sys.argv[1] == "pr":
        print(lib.nthPrime(int(sys.argv[2])))
    elif sys.argv[1] == "ip":
        print(lib.isPrime(int(sys.argv[2])))
    else:
        print("Nieprawidlowe uzycie")
        sys.exit(1)

if __name__ == "__main__": main()