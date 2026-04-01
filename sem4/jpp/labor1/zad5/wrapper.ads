with Interfaces; use Interfaces;

package Wrapper is
  type C_Bool is new Boolean;
  pragma Convention (C, C_Bool);

  type Solution is record
    X            : Unsigned_64;
    Y            : Unsigned_64;
    Has_Solution : C_Bool;
  end record;
  pragma Convention (C, Solution);


  function C_GCD (A, B : Unsigned_64) return Unsigned_64;
  pragma Import (C, C_GCD, "c_GCD");

  function C_SmallestPrimeFactor (N : Unsigned_64) return Unsigned_64;
  pragma Import (C, C_SmallestPrimeFactor, "c_smallestPrimeFactor");

  function C_Totient (N : Unsigned_64) return Unsigned_64;
  pragma Import (C, C_Totient, "c_totient");

  function C_SolveDiophantine (A, B, C_Val : Unsigned_64) return Solution;
  pragma Import (C, C_SolveDiophantine, "c_solveDiophantine");


  function Ada_GCD (A, B : Unsigned_64) return Unsigned_64;
  pragma Import (C, Ada_GCD, "ada_GCD");

  function Ada_SmallestPrimeFactor (N : Unsigned_64) return Unsigned_64;
  pragma Import (C, Ada_SmallestPrimeFactor, "ada_smallestPrimeFactor");

  function Ada_Totient (N : Unsigned_64) return Unsigned_64;
  pragma Import (C, Ada_Totient, "ada_totient");

  function Ada_SolveDiophantine (A, B, C_Val : Unsigned_64) return Solution;
  pragma Import (C, Ada_SolveDiophantine, "ada_solveDiophantine");


  function Rust_GCD (A, B : Unsigned_64) return Unsigned_64;
  pragma Import (C, Rust_GCD, "rust_GCD");

  function Rust_SmallestPrimeFactor (N : Unsigned_64) return Unsigned_64;
  pragma Import (C, Rust_SmallestPrimeFactor, "rust_smallestPrimeFactor");

  function Rust_Totient (N : Unsigned_64) return Unsigned_64;
  pragma Import (C, Rust_Totient, "rust_totient");

  function Rust_SolveDiophantine (A, B, C_Val : Unsigned_64) return Solution;
  pragma Import (C, Rust_SolveDiophantine, "rust_solveDiophantine");
end Wrapper;
