with Ada.Text_IO;                       use Ada.Text_IO;
with Ada.Float_Text_IO;                 use Ada.Float_Text_IO;
with Ada.Numerics.Elementary_Functions; use Ada.Numerics.Elementary_Functions;

procedure Zad5 is
    a, b, c, dlta, x1, x2 : Float;
begin
  Put_Line("Podaj: a b c");
  Get(a);
  Get(b);
  Get(c);

  dlta := (b * b) - (4.0 * a * c);

  if a = 0.0 then
    Put_Line("Funkcja nie jest kwadratowa");
  elsif dlta = 0.0 then
    x1 := (-b) / (2.0 * a);
    Put_Line("x = " & x1'Image);
  elsif dlta > 0.0 then
    x1 := (-b + Sqrt(dlta)) / (2.0 * a);
    x2 := (-b - Sqrt(dlta)) / (2.0 * a);
    Put_Line("x1 = " & x1'Image);
    Put_Line("x2 = " & x2'Image);
  else
    Put_Line("Delta mniejsza od zera");
  end if;
end Zad5;
