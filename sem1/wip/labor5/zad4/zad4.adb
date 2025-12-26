with Ada.Text_IO;                            use Ada.Text_IO;
with Ada.Numerics;                           use Ada.Numerics;
with Ada.Long_Float_Text_IO;                 use Ada.Long_Float_Text_IO;
with Ada.Numerics.Long_Elementary_Functions; use Ada.Numerics.Long_Elementary_Functions;

procedure Zad4 is
  type Function_t is access function(x : Long_Float) return Long_Float;

  function myFun(x : Long_Float) return Long_Float is
  begin
    return Cos(x / 2.0);
  end myFun;

  function findZero(f : Function_t; a, b, eps : in Long_Float) return Long_Float is
    mid   : Long_Float;
    a_cpy : Long_Float := a;
    b_cpy : Long_Float := b;
  begin
    while ((b_cpy - a_cpy) / 2.0) > eps loop
      mid := (a_cpy + b_cpy) / 2.0;

      if f(mid) = 0.0 then
        return mid;
      elsif f(a) * f(mid) < 0.0 then
        b_cpy := mid;
      else
        a_cpy := mid;
      end if;
    end loop;

    return (a_cpy + b_cpy) / 2.0;
  end findZero;


  epsilon : constant array(1 .. 8) of Long_Float := ( 1.0e-1, 1.0e-2, 1.0e-3, 1.0e-4, 1.0e-5, 1.0e-6, 1.0e-7, 1.0e-8 );
  a       : Long_Float := 2.0;
  b       : Long_Float := 4.0;
begin
  for i in epsilon'Range loop
    Put("x0 =");
    Put(findZero(myFun'Access, a, b, epsilon(i)), Aft => epsilon'Last + 1, Exp => 0);
    Put(" : epsilon =");
    Put(epsilon(i), Aft => i, Exp => 0);
    New_Line;
  end loop;
end Zad4;
