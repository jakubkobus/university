with Ada.Numerics.Elementary_Functions; use Ada.Numerics.Elementary_Functions;

package body Lib is
  function Log2i(n : Natural) return Natural is
    Ln2 : constant Float := Log(2.0);
  begin
    return Natural(Log(Float(n)) / Ln2);
  end Log2i;

  procedure primeFactors(factors : in out FactorsArray; size : in out Natural) is
    t : Natural := 3;
    n : Natural := size;
  begin
    size := 0;

    while n mod 2 = 0 loop
      factors(size) := 2;
      n := n / 2;
      size := size + 1;
    end loop;

    while n > 1 loop
      if t * t > n then
        factors(size) := n;
        n := 1;
        size := size + 1;
      else 
        while n mod t = 0 loop
          factors(size) := t;
          n := n / t;
          size := size + 1;
        end loop;

        t := t + 2;
      end if;
    end loop;
  end primeFactors;

  function totient(n : in Natural) return Natural is
    factors : FactorsArray(0 .. Log2i(n) - 1);
    size : Natural := n;
    result : Natural := n;
  begin
    primeFactors(factors, size);

    for i in 0 .. size - 1 loop
      if i = 0 then
        result := result - result / factors(i);
      elsif factors(i) /= factors(i - 1) then
        result := result - result / factors(i);
      end if;
    end loop;

    return result;
  end totient;

end Lib;