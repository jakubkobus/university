#ifndef STATS_HPP
#define STATS_HPP

struct Stats {
  long long cmp = 0;
  long long ptr = 0;

  void reset() {
    cmp = 0;
    ptr = 0;
  }
};

#endif // STATS_HPP
