import sys, lib

def main() -> None:
    if len(sys.argv) < 2:
        print("Nieprawidlowe uzycie")
        sys.exit(1)
        
    for i in range(1, len(sys.argv)):
        print(f"totient({sys.argv[i]}) = {lib.totient(int(sys.argv[i]))}")

if __name__ == "__main__": main()