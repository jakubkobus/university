from typing import List, Tuple

GUESS_SIZE = 4
GUESS_MIN = 1
GUESS_MAX = 6

def compare(correct: List[int], guess: List[int]) -> Tuple[int, int]:
  hits, misplaced = 0, 0
  correctLeft, guessLeft = [], []
  used = [0] * GUESS_SIZE
  countLeft = 0

  for i in range(GUESS_SIZE):
    if correct[i] == guess[i]:
      hits += 1
    else:
      correctLeft.append(correct[i])
      guessLeft.append(guess[i])
      countLeft += 1
  
  for i in range(countLeft):
    for j in range(countLeft):
      if not used[j] and guessLeft[i] == correctLeft[j]:
        misplaced += 1
        used[j] = 1
        break
  
  return (hits, misplaced)

def main(): 
    combinations = [
        [i, j, k, l]
        for i in range(GUESS_MIN, GUESS_MAX + 1)
        for j in range(GUESS_MIN, GUESS_MAX + 1)
        for k in range(GUESS_MIN, GUESS_MAX + 1)
        for l in range(GUESS_MIN, GUESS_MAX + 1)
    ]
    
    guess = [GUESS_MIN] * GUESS_SIZE
    hits = 0
    attempt = 0
    
    while hits != 4:
        attempt += 1
        print(f"{attempt}: {' '.join(map(str, guess))} ?")
        
        hits      = int(input("Na swoim miejscu: "))
        misplaced = int(input("Nie na swoim miejscu: "))
        
        combinations = [
            comb for comb in combinations
            if compare(comb, guess) == (hits, misplaced)
        ]
        
        if len(combinations) > 0:
            guess = combinations[0] 
        else:
            print("Oszukujesz!")
            break
    else:
        print(f"Wygralem.")

if __name__ == "__main__": main()
