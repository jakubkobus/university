use std::ops::{Add, AddAssign, Div, DivAssign, Mul, MulAssign, Sub, SubAssign};

#[derive(Debug, Clone, Copy, PartialEq, Eq, PartialOrd, Ord)]
pub struct Ring<const N: i64> {
  value: i64,
}

impl<const N: i64> Ring<N> {
  pub fn new(v: i64) -> Self {
    Self {
      value: Self::normalize(v),
    }
  }

  pub fn get(&self) -> i64 {
    self.value
  }

  fn normalize(v: i64) -> i64 {
    let mut result = v % N;
    if result < 0 {
      result += N;
    }
    result
  }

  #[allow(non_snake_case)]
  fn extendedGCD(a: i64, b: i64) -> (i64, i64, i64) {
    if b == 0 {
      return (a, 1, 0);
    }

    let (d, x1, y1) = Self::extendedGCD(b, a % b);
    let x = y1;
    let y = x1 - y1 * (a / b);

    (d, x, y)
  }

  fn mod_inverse(a: i64, m: i64) -> i64 {
    let (g, x, _) = Self::extendedGCD(a, m);
    if g != 1 {
      panic!("Non-existent inverse element error: {}^(-1)", a);
    }

    ((x % m) + m) % m
  }
}

impl<const N: i64> From<i64> for Ring<N> {
  fn from(v: i64) -> Self {
    Self::new(v)
  }
}

impl<const N: i64> AddAssign for Ring<N> {
  fn add_assign(&mut self, rhs: Self) {
    self.value = Self::normalize(self.value + rhs.value);
  }
}

impl<const N: i64> SubAssign for Ring<N> {
  fn sub_assign(&mut self, rhs: Self) {
    self.value = Self::normalize(self.value - rhs.value);
  }
}

impl<const N: i64> MulAssign for Ring<N> {
  fn mul_assign(&mut self, rhs: Self) {
    self.value = Self::normalize(self.value * rhs.value);
  }
}

impl<const N: i64> DivAssign for Ring<N> {
  fn div_assign(&mut self, rhs: Self) {
    if rhs.value == 0 {
      panic!("Zero division error");
    }
    self.value = Self::normalize(self.value * Self::mod_inverse(rhs.value, N));
  }
}

impl<const N: i64> Add for Ring<N> {
  type Output = Self;

  fn add(self, rhs: Self) -> Self::Output {
    let mut res = self;
    res.add_assign(rhs);
    res
  }
}

impl<const N: i64> Add<i64> for Ring<N> {
  type Output = Self;

  fn add(self, rhs: i64) -> Self::Output {
    let mut res = self;
    res.add_assign(Ring::new(rhs));
    res
  }
}

impl<const N: i64> Sub for Ring<N> {
  type Output = Self;

  fn sub(self, rhs: Self) -> Self::Output {
    let mut res = self;
    res.sub_assign(rhs);
    res
  }
}

impl<const N: i64> Sub<i64> for Ring<N> {
  type Output = Self;

  fn sub(self, rhs: i64) -> Self::Output {
    let mut res = self;
    res.sub_assign(Ring::new(rhs));
    res
  }
}

impl<const N: i64> Mul for Ring<N> {
  type Output = Self;

  fn mul(self, rhs: Self) -> Self::Output {
    let mut res = self;
    res.mul_assign(rhs);
    res
  }
}

impl<const N: i64> Mul<i64> for Ring<N> {
  type Output = Self;

  fn mul(self, rhs: i64) -> Self::Output {
    let mut res = self;
    res.mul_assign(Ring::new(rhs));
    res
  }
}

impl<const N: i64> Div for Ring<N> {
  type Output = Self;

  fn div(self, rhs: Self) -> Self::Output {
    let mut res = self;
    res.div_assign(rhs);
    res
  }
}

impl<const N: i64> Div<i64> for Ring<N> {
  type Output = Self;

  fn div(self, rhs: i64) -> Self::Output {
    let mut res = self;
    res.div_assign(Ring::new(rhs));
    res
  }
}
