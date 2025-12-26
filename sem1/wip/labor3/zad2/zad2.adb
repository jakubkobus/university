with Ada.Text_IO;         use Ada.Text_IO;
with Ada.Integer_Text_IO; use Ada.Integer_Text_IO;

procedure Zad2 is
  type SieveArray is array(Positive range<>) of Boolean;

  procedure computeSieve(sieve : in out SieveArray; n : in Positive) is
    j : Positive;
  begin
    for i in 2 .. n loop
      sieve(i) := True;
    end loop;

    for i in 2 .. n loop
      if sieve(i) then
        j := i + i;
        while j <= n loop
          sieve(j) := False;
          j := j + i;
        end loop;
      end if;
    end loop;
  end computeSieve;

  function countPrimes(n : in Positive) return Natural is
    sieve : SieveArray(1 .. n);
    numberOfPrimes : Natural := 0;
  begin
    computeSieve(sieve, n);

    for i in 2 .. n loop
      if sieve(i) then
        numberOfPrimes := numberOfPrimes + 1;
      end if;
    end loop;

    return numberOfPrimes;
  end countPrimes;
  
  n : Positive;
  numberOfPrimes : Natural;
begin
  Put("Podaj liczbe: ");
  begin
    Get(n);
    if n > 1 then
      numberOfPrimes := countPrimes(n);
      Put("Ilosc liczb pierwszych w zakresie 2 .." & n'Image);
      Put_Line(" =" & numberOfPrimes'Image);
    else
      Put_Line("Dozwolone wartosci w zakresie 2 .. (2^32 - 1)");
    end if;
  exception
    when Data_Error =>
      Put_Line("Dozwolone wartosci w zakresie 2 .. (2^32 - 1)");
    when Constraint_Error =>
      Put_Line("Dozwolone wartosci w zakresie 2 .. (2^32 - 1)");
    when Storage_Error => -- Dopiero 2^22 nie przekracza limitu pamieci
      Put_Line("Przekroczono limit pamieci");
  end;
end Zad2;