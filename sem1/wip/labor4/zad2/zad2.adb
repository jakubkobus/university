with Ada.Text_IO;       use Ada.Text_IO;
with Ada.Command_Line;  use Ada.Command_Line;
with Ada.Strings.Fixed; use Ada.Strings.Fixed;

with Lib;

procedure Zad2 is
  function img(number : in Natural) return String is
  begin
    return Trim(number'Image, Ada.Strings.Left);
  end img;


  n : Natural;
begin
  n := Integer'Value(Argument(2));

  if Argument(1) = "pn" then
    Put_Line(img(Lib.countPrimes(n)));
  elsif Argument(1) = "pr" then
    Put_Line(img(Lib.nthPrime(n)));
  elsif Argument(1) = "ip" then
    if Lib.isPrime(Integer(n)) then
      Put_Line("true");
    else
      Put_Line("false");
    end if;
  else
    Put_Line("Nieprawidlowe uzycie");
    return;
  end if;

end Zad2;