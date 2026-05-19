/*
 *  LeetCode 367
 */

class Solution {
public:
  bool isPerfectSquare(int num) {
    if(num < 0)
      return false;

    if(
      num == 0 ||
      num == 1 ||
      num == 4 ||
      num == 9
    ) return true;

    long long higher = 16;
    short        exp =  4;
    while(higher < num) {
      higher <<= 1;
      exp++;
    }

    long long
      left = exp,
      mid,
      right = num / exp;

    while(left <= right) {
      mid = left + ((right - left) >> 1);

      if(mid * mid == num)
        return true;
      else if(mid * mid < num)
        left = mid + 1;
      else
        right = mid - 1;
    }

    return false;
  }
};
