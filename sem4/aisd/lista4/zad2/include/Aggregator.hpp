#ifndef AGGREGATOR_HPP
#define AGGREGATOR_HPP

struct Aggregator {
  long long totalCmp = 0;
  long long maxCmp = 0;

  long long totalPtr = 0;
  long long maxPtr = 0;

  long long totalHeight = 0;
  long long maxHeight = 0;

  long long count = 0;

  void update(int cmp, int ptr, int height) {
    totalCmp += cmp;
    if(cmp > maxCmp)
      maxCmp = cmp;

    totalPtr += ptr;
    if(ptr > maxPtr)
      maxPtr = ptr;

    totalHeight += height;
    if(height > maxHeight)
      maxHeight = height;

    count++;
  }

  void merge(const Aggregator &other) {
      totalCmp += other.totalCmp;
      if(other.maxCmp > maxCmp)
        maxCmp = other.maxCmp;

      totalPtr += other.totalPtr;
      if(other.maxPtr > maxPtr)
        maxPtr = other.maxPtr;

      totalHeight += other.totalHeight;
      if(other.maxHeight > maxHeight)
        maxHeight = other.maxHeight;

      count += other.count;
  }

  double avgCmp() const {
    return count > 0 ? static_cast<double>(totalCmp) / count : 0;
  }

  double avgPtr() const {
    return count > 0 ? static_cast<double>(totalPtr) / count : 0;
  }

  double avgHeight() const {
    return count > 0 ? static_cast<double>(totalHeight) / count : 0;
  }
};

#endif // AGGREGATOR_HPP
