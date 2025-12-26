with Ada.Text_IO;                       use Ada.Text_IO;
with Ada.Strings.Fixed;                 use Ada.Strings.Fixed;
with Ada.Integer_Text_IO;               use Ada.Integer_Text_IO;
with Ada.Numerics.Elementary_Functions; use Ada.Numerics.Elementary_Functions;


procedure Zad8 is
  function nthPrime(n : Natural) return Natural is
    function iSqrt(n : in Natural) return Natural is
    begin
      return Natural(Integer(Sqrt(Float(n))));
    end iSqrt;
    
    primes : array(0 .. n - 1) of Natural;
    candidate : Natural := 3;
    iterator : Natural := 1;
    i, s : Natural;
    isPrime : Boolean;
  begin
    if n < 1 then return 0; end if;

    primes(0) := 2;

    while iterator < n loop
      s := iSqrt(candidate);
      isPrime := True;
      i := 1;

      while isPrime and primes(i) <= s and i < iterator loop
        if candidate mod primes(i) = 0 then isPrime := False;
        else i := i + 1; end if;
      end loop;

      if isPrime then
        primes(iterator) := candidate;
        iterator := iterator + 1;
      end if;

      candidate := candidate + 2;
    end loop;

    return primes(n - 1);
  end nthPrime;

  function img(number : in Natural) return String is
  begin
    return Trim(number'Image, Ada.Strings.Left);
  end img;

  n : Natural;
begin
  Put("Podaj n: ");
  Get(n);

  Put_Line(img(n) & "liczba pierwsza = " & img(nthPrime(n)));
end Zad8;