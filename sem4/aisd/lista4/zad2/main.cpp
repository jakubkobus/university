#include <stdio.h>
#include <vector>
#include <numeric>
#include <random>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <omp.h>

#include "../zad1/include/BST.hpp"
#include "../zad1/include/Stats.hpp"
#include "include/Aggregator.hpp"

#define START  10000
#define STOP   100000
#define STEP   10000
#define TESTS  20

int main() {
  std::ofstream fileA("results/resultA.csv");
  std::ofstream fileB("results/resultB.csv");

  std::string header = "N,Avg_Cmp_Ins,Max_Cmp_Ins,Avg_Ptr_Ins,Max_Ptr_Ins,Avg_H_Ins,Max_H_Ins,"
                        "Avg_Cmp_Del,Max_Cmp_Del,Avg_Ptr_Del,Max_Ptr_Del,Avg_H_Del,Max_H_Del\n";
  fileA << header;
  fileB << header;

  for(int n = START; n <= STOP; n += STEP) {
    printf("Processing N = %d ...\n", n);

    Aggregator insertAggA, deleteAggA;
    Aggregator insertAggB, deleteAggB;

    #pragma omp parallel for schedule(dynamic)
    for (int test = 0; test < TESTS; test++) {
      std::mt19937 localRNG(std::random_device{}() ^ omp_get_thread_num());

      Aggregator localInsertAggA, localDeleteAggA;
      Aggregator localInsertAggB, localDeleteAggB;

      std::vector<int> ascSequence(n);
      std::iota(ascSequence.begin(), ascSequence.end(), 1);

      std::vector<int> randInsertSequence = ascSequence;
      std::shuffle(randInsertSequence.begin(), randInsertSequence.end(), localRNG);

      std::vector<int> randDeleteSequenceA = ascSequence;
      std::shuffle(randDeleteSequenceA.begin(), randDeleteSequenceA.end(), localRNG);

      std::vector<int> randDeleteSequenceB = ascSequence;
      std::shuffle(randDeleteSequenceB.begin(), randDeleteSequenceB.end(), localRNG);

      Stats s;

      BST treeA;

      for(int i = 0; i < n; i++) {
        s.reset();
        treeA.insertNode(ascSequence[i], s);
        localInsertAggA.update(s.cmp, s.ptr, treeA.height());
      }

      for(int i = 0; i < n; i++) {
        s.reset();
        treeA.deleteKey(randDeleteSequenceA[i], s);
        localDeleteAggA.update(s.cmp, s.ptr, treeA.height());
      }

      BST treeB;

      for (int i = 0; i < n; ++i) {
        s.reset();
        treeB.insertNode(randInsertSequence[i], s);
        localInsertAggB.update(s.cmp, s.ptr, treeB.height());
      }

      for (int i = 0; i < n; ++i) {
        s.reset();
        treeB.deleteKey(randDeleteSequenceB[i], s);
        localDeleteAggB.update(s.cmp, s.ptr, treeB.height());
      }

      #pragma omp critical
      {
        insertAggA.merge(localInsertAggA);
        deleteAggA.merge(localDeleteAggA);
        insertAggB.merge(localInsertAggB);
        deleteAggB.merge(localDeleteAggB);
      }
    }

    fileA << std::fixed << std::setprecision(2)
          << n << ","
          << insertAggA.avgCmp()    << "," << insertAggA.maxCmp    << ","
          << insertAggA.avgPtr()    << "," << insertAggA.maxPtr    << ","
          << insertAggA.avgHeight() << "," << insertAggA.maxHeight << ","
          << deleteAggA.avgCmp()    << "," << deleteAggA.maxCmp    << ","
          << deleteAggA.avgPtr()    << "," << deleteAggA.maxPtr    << ","
          << deleteAggA.avgHeight() << "," << deleteAggA.maxHeight << '\n';

    fileB << std::fixed << std::setprecision(2)
          << n << ","
          << insertAggB.avgCmp()    << "," << insertAggB.maxCmp    << ","
          << insertAggB.avgPtr()    << "," << insertAggB.maxPtr    << ","
          << insertAggB.avgHeight() << "," << insertAggB.maxHeight << ","
          << deleteAggB.avgCmp()    << "," << deleteAggB.maxCmp    << ","
          << deleteAggB.avgPtr()    << "," << deleteAggB.maxPtr    << ","
          << deleteAggB.avgHeight() << "," << deleteAggB.maxHeight << '\n';
  }

  fileA.close();
  fileB.close();

  printf("Results saved to results/result{A, B}.csv\n");
  return 0;
}
