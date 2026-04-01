#[repr(C)]
#[allow(non_snake_case)]
pub struct Solution {
  pub x: u64,
  pub y: u64,
  pub hasSolution: bool,
}

extern "C" {
  fn adainit();
  fn adafinal();

  fn c_GCD(a: u64, b: u64) -> u64;
  fn c_smallestPrimeFactor(n: u64) -> u64;
  fn c_totient(n: u64) -> u64;
  fn c_solveDiophantine(a: u64, b: u64, c: u64) -> Solution;

  fn ada_GCD(a: u64, b: u64) -> u64;
  fn ada_smallestPrimeFactor(n: u64) -> u64;
  fn ada_totient(n: u64) -> u64;
  fn ada_solveDiophantine(a: u64, b: u64, c: u64) -> Solution;

  fn rust_GCD(a: u64, b: u64) -> u64;
  fn rust_smallestPrimeFactor(n: u64) -> u64;
  fn rust_totient(n: u64) -> u64;
  fn rust_solveDiophantine(a: u64, b: u64, c: u64) -> Solution;
}

fn main() {
  unsafe {
    adainit();

    let a = 48;
    let b = 18;
    println!("NWD({}, {})", a, b);
    println!("C    -> {}", c_GCD(a, b));
    println!("Ada  -> {}", ada_GCD(a, b));
    println!("Rust -> {}\n", rust_GCD(a, b));

    let n = 15;
    println!("smallestPrimeFactor({})", n);
    println!("C    -> {}", c_smallestPrimeFactor(n));
    println!("Ada  -> {}", ada_smallestPrimeFactor(n));
    println!("Rust -> {}\n", rust_smallestPrimeFactor(n));

    let m = 12;
    println!("totient({})", m);
    println!("C    -> {}", c_totient(m));
    println!("Ada  -> {}", ada_totient(m));
    println!("Rust -> {}\n", rust_totient(m));

    let (da, db, dc) = (21, 3, 15);
    println!("solveDiophantine({}, {}, {})", da, db, dc);

    let sol_c = c_solveDiophantine(da, db, dc);
    println!(
      "C    -> x = {}, y = {}, hasSolution = {}",
      sol_c.x, sol_c.y, sol_c.hasSolution
    );

    let sol_ada = ada_solveDiophantine(da, db, dc);
    println!(
      "Ada  -> x = {}, y = {}, hasSolution = {}",
      sol_ada.x, sol_ada.y, sol_ada.hasSolution
    );

    let sol_rust = rust_solveDiophantine(da, db, dc);
    println!(
      "Rust -> x = {}, y = {}, hasSolution = {}",
      sol_rust.x, sol_rust.y, sol_rust.hasSolution
    );

    adafinal();
  }
}
