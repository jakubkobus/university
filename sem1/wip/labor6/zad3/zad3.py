import sys
from typing import List

def nextPermutation(lst: List[int], min_: int, max_: int) -> bool:
    for i in range(len(lst) - 1, -1, -1):
        if lst[i] < max_:
            lst[i] += 1
            for j in range(i + 1, len(lst)):
                lst[j] = min_
            return True
    return False

def isValid(lst: List[int]) -> bool:
    row   = [0] * (1 + len(lst))
    dgnl1 = [0] * (2 * len(lst))
    dgnl2 = [0] * (2 * len(lst))
    
    for i in range(len(lst)):
        row[lst[i]] += 1
        dgnl1[i - lst[i] + len(lst)] += 1
        dgnl2[i + lst[i]] += 1
        
        if row[lst[i]] > 1 or \
           dgnl1[i - lst[i] + len(lst)] > 1 or \
           dgnl2[i + lst[i]] > 1:
            return False
    
    return True

def main() -> None:
    if len(sys.argv) != 2:
        print("Unknown usage")
        return
    
    n = int(sys.argv[1])
    lst = [1] * n

    validSolutions = 0
    
    while True:
        if isValid(lst):
            print(*lst)
            validSolutions += 1
        
        if not nextPermutation(lst, 1, n):
            break

    print(f'Number of solutions: {validSolutions}')

if __name__ == "__main__": main()