use std::panic;

mod ring;

use ring::Ring;

fn main() {
  let result1 = panic::catch_unwind(|| {
    println!("--- Z7 (Ring<7>) ---");
    println!("[IN] a = 10, b = -4");

    let a: Ring<7> = Ring::new(10);
    let b: Ring<7> = Ring::new(-4);

    println!("a = {}\nb = {}", a.get(), b.get());
    println!("a == b -> {}", if a == b { "true" } else { "false" });

    println!("a + b = {}", (a + b).get());
    println!("a * 5 = {}", (a * 5).get());
    println!("a / 2 = {}", (a / 2).get());
    println!("a ^ 2 = {}", (a * a).get());

    println!("\n--- Z6 (Ring<6>) ---");
    println!("[IN] x = 5, y = 2");

    let x: Ring<6> = Ring::new(5);
    let y: Ring<6> = Ring::new(2);

    println!("x = {}\ny = {}", x.get(), y.get());
    println!("x * y = {}", (x * y).get());

    println!("\nException handling:");
    println!("\nDividing x / y ...");

    let _ = x / y;
  });

  handle_panic(result1);

  let result2 = panic::catch_unwind(|| {
    println!("\nDividing by zero...");
    let _ = Ring::<7>::new(5) / Ring::<7>::new(0);
  });

  handle_panic(result2);
}

fn handle_panic(result: std::thread::Result<()>) {
  if let Err(err) = result {
    let msg = if let Some(s) = err.downcast_ref::<&str>() {
      *s
    } else if let Some(s) = err.downcast_ref::<String>() {
      s.as_str()
    } else {
      "Unknown panic"
    };
    eprintln!("[WARN] Exception catched: {}", msg);
  }
}
