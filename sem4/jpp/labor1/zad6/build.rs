use std::env;

fn main() {
  println!("cargo:rustc-link-search=native=../zad1");
  println!("cargo:rustc-link-search=native=../zad2");
  println!("cargo:rustc-link-search=native=../zad3/target/release");

  let is_dynamic = env::var("CARGO_FEATURE_DYNAMIC").is_ok();

  let mode = if is_dynamic { "dylib" } else { "static" };

  println!("cargo:rustc-link-lib={}=my_lib_c", mode);
  println!("cargo:rustc-link-lib={}=my_lib_ada", mode);
  println!("cargo:rustc-link-lib={}=my_lib_rust", mode);

  println!("cargo:rustc-link-lib=dylib=gnat");
  println!("cargo:rustc-link-lib=dylib=m");
  println!("cargo:rustc-link-lib=dylib=dl");
  println!("cargo:rustc-link-lib=dylib=pthread");
}
