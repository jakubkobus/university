#include <stdio.h>
#include <chrono>

#include "solution.hpp"

int main() {
    const size_t K = 1000000;

    Solution solution;

    auto start = std::chrono::high_resolution_clock::now();
    int count = 0;

    for (size_t i = 1; i <= K; i++)
        if (solution.isPerfectSquare(i))
            count++;

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    printf("Czas: %ld ms (znaleziono %d idealnych kwadratow)\n", duration.count(), count);
    return 0;
}
