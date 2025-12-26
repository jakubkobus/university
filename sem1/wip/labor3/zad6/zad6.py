"""
    Wylicza trojkat pascala do min(k, n - k) kolumny
    w n wierszu i kolumnie k jest wyliczony dwumian
"""

def binomialCoefficient(n: int, k: int) -> int:
    k = min(k, n - k)
    if k == 0: return 1
    
    arr = [1] * (k + 1)
    min_ = None
    
    for i in range(1, n + 1):
        if i <= k:
            min_ = i - 1
            arr[i] = 1
        else:
            min_ = k
        
        for j in range(min_, 0, -1):
            arr[j] += arr[j - 1]
    
    return arr[k]

def main() -> None:
    print("Podaj: n k")
    n, k = map(int, input().split(' '))
    
    print(f"Dwumian({n}, {k}) = {binomialCoefficient(n, k)}")

if __name__ == "__main__": main()
