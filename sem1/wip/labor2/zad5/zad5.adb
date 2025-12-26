with Ada.Text_IO;                       use Ada.Text_IO;
with Ada.Integer_Text_IO;               use Ada.Integer_Text_IO;
with Ada.Numerics.Elementary_Functions; use Ada.Numerics.Elementary_Functions;

procedure Zad5 is
  function isPrime(n : in Integer) return Boolean is
    function iSqrt(n : in Natural) return Natural is
    begin
      return Natural(Integer(Sqrt(Float(n))));
    end iSqrt;

    isqrtn, i : Integer;
  begin
    if n <= 1 then
      return False;
    elsif n = 2 or n = 3 or n = 5 then
      return True;
    elsif n mod 2 = 0 or n mod 3 = 0 or n mod 5 = 0 then
      return False;
    end if;

    isqrtn := isqrt(n);
    i := 5;
    while i <= isqrtn loop
      if n mod i = 0 or n mod (i + 2) = 0 then
        return false;
      end if;

      i := i + 6;
    end loop;

    return True;
  end isPrime;


  n : Integer;
begin
  Put("Podaj liczbe: ");
  Get(n);

  if isPrime(n) then
    Put_Line("TAK");
  else
    Put_Line("NIE");
  end if;
end Zad5;