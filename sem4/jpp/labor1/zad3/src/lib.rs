#[repr(C)]
#[allow(non_snake_case)]
pub struct Solution {
  pub x: u64,
  pub y: u64,
  pub hasSolution: bool,
}

#[no_mangle]
pub extern "C" fn rust_GCD(mut a: u64, mut b: u64) -> u64 {
  while b != 0 {
    let temp = b;
    b = a % b;
    a = temp;
  }
  a
}

#[no_mangle]
pub extern "C" fn rust_smallestPrimeFactor(n: u64) -> u64 {
  if n <= 1 {
    return 0;
  }
  if n % 2 == 0 {
    return 2;
  }

  let mut i = 3;
  while i * i <= n {
    if n % i == 0 {
      return i;
    }
    i += 2;
  }

  n
}

#[no_mangle]
pub extern "C" fn rust_totient(mut n: u64) -> u64 {
  if n == 0 {
    return 0;
  }

  let mut result = n;
  let mut p = 2;

  while p * p <= n {
    if n % p == 0 {
      while n % p == 0 {
        n /= p;
      }
      result -= result / p;
    }
    p += 1;
  }

  if n > 1 {
    result -= result / n;
  }

  result
}

#[allow(non_snake_case)]
fn extendedGCD(a: i64, b: i64) -> (i64, i64, i64) {
  if a == 0 {
    return (b, 0, 1);
  }

  let (g, x1, y1) = extendedGCD(b % a, a);

  let x = y1 - (b / a) * x1;
  let y = x1;

  (g, x, y)
}

#[no_mangle]
pub extern "C" fn rust_solveDiophantine(a_in: u64, b_in: u64, c_in: u64) -> Solution {
  let mut sol = Solution {
    x: 0,
    y: 0,
    hasSolution: false,
  };

  let a = a_in as i64;
  let b = b_in as i64;
  let c = c_in as i64;

  if a == 0 && b == 0 {
    if c == 0 {
      sol.hasSolution = true;
    }
    return sol;
  }

  if a == 0 {
    return sol;
  }

  let (g, x0, y0) = extendedGCD(a, b);

  if c % g != 0 {
    return sol;
  }

  let a_prime = a / g;
  let b_prime = b / g;
  let c_prime = c / g;

  let x_base = x0 * c_prime;
  let y_temp = y0 * c_prime;
  let y_base = -y_temp;

  let mut k_x = -x_base / b_prime;
  while x_base + k_x * b_prime < 0 {
    k_x += 1;
  }

  let mut k_y = -y_base / a_prime;
  while y_base + k_y * a_prime < 0 {
    k_y += 1;
  }

  let k = if k_x > k_y { k_x } else { k_y };

  sol.x = (x_base + k * b_prime) as u64;
  sol.y = (y_base + k * a_prime) as u64;
  sol.hasSolution = true;

  sol
}
