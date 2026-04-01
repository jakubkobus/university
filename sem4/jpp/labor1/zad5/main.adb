with Ada.Text_IO; use Ada.Text_IO;
with Interfaces;  use Interfaces;
with Wrapper;     use Wrapper;

procedure Main is
  package U64_IO is new Ada.Text_IO.Modular_IO (Unsigned_64);

  procedure Print (Val : Unsigned_64) is
  begin
    U64_IO.Put (Val, Width => 0);
  end Print;

  function To_String (B : Wrapper.C_Bool) return String is
  begin
    if B = False then
      return "false";
    else
      return "true";
    end if;
  end To_String;

  A, B, C : Unsigned_64;
  Sol     : Wrapper.Solution;
begin
  A := 48;
  B := 18;
  Put ("NWD(");
  Print (A);
  Put (", ");
  Print (B);
  Put_Line (")");
  Put ("C    -> ");
  Print (Wrapper.C_GCD (A, B));
  New_Line;
  Put ("Ada  -> ");
  Print (Wrapper.Ada_GCD (A, B));
  New_Line;
  Put ("Rust -> ");
  Print (Wrapper.Rust_GCD (A, B));
  New_Line;
  New_Line;

  A := 15;
  Put ("smallestPrimeFactor(");
  Print (A);
  Put_Line (")");
  Put ("C    -> ");
  Print (Wrapper.C_SmallestPrimeFactor (A));
  New_Line;
  Put ("Ada  -> ");
  Print (Wrapper.Ada_SmallestPrimeFactor (A));
  New_Line;
  Put ("Rust -> ");
  Print (Wrapper.Rust_SmallestPrimeFactor (A));
  New_Line;
  New_Line;

  A := 12;
  Put ("totient(");
  Print (A);
  Put_Line (")");
  Put ("C    -> ");
  Print (Wrapper.C_Totient (A));
  New_Line;
  Put ("Ada  -> ");
  Print (Wrapper.Ada_Totient (A));
  New_Line;
  Put ("Rust -> ");
  Print (Wrapper.Rust_Totient (A));
  New_Line;
  New_Line;

  A := 21;
  B := 3;
  C := 15;
  Put ("solveDiophantine(");
  Print (A);
  Put (", ");
  Print (B);
  Put (", ");
  Print (C);
  Put_Line (")");

  Sol := Wrapper.C_SolveDiophantine (A, B, C);
  Put ("C    -> x = ");
  Print (Sol.X);
  Put (", y = ");
  Print (Sol.Y);
  Put_Line (", hasSolution -> " & To_String (Sol.Has_Solution));

  Sol := Wrapper.Ada_SolveDiophantine (A, B, C);
  Put ("Ada  -> x = ");
  Print (Sol.X);
  Put (", y = ");
  Print (Sol.Y);
  Put_Line (", hasSolution -> " & To_String (Sol.Has_Solution));

  Sol := Wrapper.Rust_SolveDiophantine (A, B, C);
  Put ("Rust -> x = ");
  Print (Sol.X);
  Put (", y = ");
  Print (Sol.Y);
  Put_Line (", hasSolution -> " & To_String (Sol.Has_Solution));
end Main;
