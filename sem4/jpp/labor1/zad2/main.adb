with Interfaces;  use Interfaces;
with Ada.Text_IO; use Ada.Text_IO;
with My_Lib;

procedure Main is
  A, B, C : Unsigned_64;
  Sol     : My_Lib.Solution;
begin
  Put_Line ("1. GCD (48, 18) =" & My_Lib.GCD (48, 18)'Img);
  Put_Line
   ("2. SmallestPrimeFactor (15) =" & My_Lib.SmallestPrimeFactor (15)'Img);
  Put_Line ("3. Totient (12) =" & My_Lib.Totient (12)'Img);

  A := 21;
  B := 3;
  C := 15;
  Sol := My_Lib.SolveDiophantine (A, B, C);

  Put ("4.");
  if Sol.HasSolution then
    Put_Line
     (A'Img
      & "x -"
      & B'Img
      & "y ="
      & C'Img
      & " -> x ="
      & Sol.x'Img
      & ", y ="
      & Sol.y'Img);
  else
    Put_Line
     (" No Solution for SolveDiophantine (A ="
      & A'Img
      & ", B ="
      & B'Img
      & ", C ="
      & C'Img
      & ")");
  end if;

end Main;
