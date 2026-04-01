with Interfaces; use Interfaces;

package My_Lib is
  type Solution is record
    X           : Unsigned_64;
    Y           : Unsigned_64;
    HasSolution : Boolean;
  end record;

  function GCD (A, B : Unsigned_64) return Unsigned_64;
  function SmallestPrimeFactor (N : Unsigned_64) return Unsigned_64;
  function Totient (N : Unsigned_64) return Unsigned_64;
  function SolveDiophantine (A, B, C : Unsigned_64) return Solution;

  pragma Export (C, GCD, "ada_GCD");
  pragma Export (C, SmallestPrimeFactor, "ada_smallestPrimeFactor");
  pragma Export (C, Totient, "ada_totient");
  pragma Export (C, SolveDiophantine, "ada_solveDiophantine");
end My_Lib;
