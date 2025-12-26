from math import sqrt

def main() -> None:
    print("Podaj: a b c")
    a, b, c = map(float, input().split(' '))
    
    delta = (b * b) - (4.0 * a * c)
    
    if a == 0.0:
        print("Funkcja nie jest kwadratowa")
    elif delta == 0.0:
        x = (-b) / (2.0 * a)
        print(f"x = {x}")
    elif delta > 0.0:
        x1 = (-b + sqrt(delta)) / (2.0 * a)
        x2 = (-b - sqrt(delta)) / (2.0 * a)
        print(f"x1 = {x1}")
        print(f"x2 = {x2}")
    else:
        print("Delta mniejsza od zera")
        

if __name__ == "__main__":
    main()