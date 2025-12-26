import sys
from typing import List

def USTAW(i: int, position: List[int], n: int, bije_wiersz: List[bool], bije_przek1: List[bool], bije_przek2: List[bool], solutions: List[int]) -> None:
    for j in range(n):
        if not (bije_wiersz[j] or bije_przek1[i + j] or bije_przek2[i - j + n]):
            position[i] = j
            bije_wiersz[j] = bije_przek1[i + j] = bije_przek2[i - j + n] = True

            if i < n - 1:
                USTAW(i + 1, position, n, bije_wiersz, bije_przek1, bije_przek2, solutions)
            else:
                print(" ".join(str(x + 1) for x in position))
                solutions[0] += 1

            position[i] = 0
            bije_wiersz[j] = bije_przek1[i + j] = bije_przek2[i - j + n] = False

def HETMAN(n: int) -> None:
    position = [0] * n
    bije_wiersz = [False] * n
    bije_przek1 = [False] * (2 * n)
    bije_przek2 = [False] * (2 * n)

    solutions = [0]
    USTAW(0, position, n, bije_wiersz, bije_przek1, bije_przek2, solutions)
    print(f"Number of solutions: {solutions[0]}")

def main() -> None:
    if len(sys.argv) != 2:
        print("Unknown usage")
        sys.exit(1)

    n = int(sys.argv[1])
    HETMAN(n)

if __name__ == "__main__": main()