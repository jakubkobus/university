from typing import List
import sys

INT_MAX = (1 << 31) - 1 # 2^31 - 1

def getCoins(filename: str) -> List[int] | None:
    try:
        with open(filename, 'r') as f:
            return [int(l.strip()) for l in f.readlines()][1:] 
    except FileNotFoundError:
        print(f"File '{filename}' does not exist")
        return None

def solveChangeProblem(coins: List[int], r: int) -> None:
    C = [INT_MAX] * (r + 1)
    D = [-1]      * (r + 1)
    C[0] = 0
    
    for i in range(1, r + 1):
        for j in range(len(coins)):
            if coins[j] <= i and \
               C[i - coins[j]] != INT_MAX and \
               C[i] > C[i - coins[j]] + 1:
                   
                C[i] = C[i - coins[j]] + 1
                D[i] = coins[j]
    
    if C[r] == INT_MAX:
        print(f"{r} ==> No solution!")
    else:
        print(f"{r} ==> {C[r]}")
        res = [0] * len(coins)
        left = r
        
        while left > 0:
            coin = D[left]
            for i in range(len(coins)):
                if coins[i] == coin:
                    res[i] += 1
                    break
            
            left -= coin
            
        for i in range(len(coins)):
            if res[i] > 0:
                print(f"\t{res[i]} x {coins[i]}")

def main() -> None:
    if len(sys.argv) < 3:
        print("Unknown usage: <filename:str> <amount:int> ... <amount:int>")
        return
    
    coins = getCoins(sys.argv[1])
    
    if coins == None:
        return
    
    for i in range(2, len(sys.argv)):
        if sys.argv[i].isnumeric():
            solveChangeProblem(coins, int(sys.argv[i]))
        else:
            print(f"'{sys.argv[i]}' is not an integer")

if __name__ == "__main__": main()