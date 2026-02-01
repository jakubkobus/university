#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <cstdlib>
#include <ctime>

#define LENGTH 1000000

int main() {
  std::srand(time(nullptr));
  std::mt19937 gen(std::random_device{}());
  std::uniform_int_distribution<> dis(0, 1);


  char buffer[LENGTH];

  for(size_t i = 0; i < LENGTH; i++) 
    buffer[i] = (std::rand() % 2) + 48;

  std::ofstream randFile("results/rand.txt");
  if(randFile.is_open()) {
    randFile.write(buffer, LENGTH);
    randFile.close();
  }

  for(size_t i = 0; i < LENGTH; i++)
    buffer[i] = dis(gen) + 48;

  std::ofstream mtFile("results/mersenne_twister.txt");
  if(mtFile.is_open()) {
    mtFile.write(buffer, LENGTH);
    mtFile.close();
  }

  return 0;
}