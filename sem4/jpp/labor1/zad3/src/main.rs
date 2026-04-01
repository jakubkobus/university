use my_lib_rust::{rust_GCD, rust_smallestPrimeFactor, rust_solveDiophantine, rust_totient};

fn main() {
  println!("1. GCD(48, 18) = {}", rust_GCD(48, 18));

  println!(
    "2. smallestPrimeFactor(15) = {}",
    rust_smallestPrimeFactor(15)
  );

  println!("3. totient(12) = {}", rust_totient(12));

  let a = 21;
  let b = 3;
  let c = 15;

  let sol = rust_solveDiophantine(a, b, c);

  match sol.hasSolution {
    true => {
      println!("4. {}x - {}y = {} -> x = {}, y = {}", a, b, c, sol.x, sol.y);
    }

    false => {
      println!(
        "4. No solution for solveDiophantine(a = {}, b = {}, c = {})",
        a, b, c
      );
    }
  }
}
